#include <cstdlib>
#include <deque>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using boost::asio::ip::tcp;

typedef std::deque<std::string> chat_message_queue;

class line_client
{
public:
    line_client(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator)
        : io_service_(io_service), socket_(io_service)
    {
        tcp::endpoint endpoint = *endpoint_iterator;

        socket_.async_connect(
            endpoint,
            boost::bind(&line_client::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator));
    }

    void write(std::string message)
    {
        io_service_.post(boost::bind(&line_client::do_write, this, message));
    }

    void close()
    {
        io_service_.post(boost::bind(&line_client::do_close, this));
    }

private:
    void handle_connect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iterator)
    {
        using boost::asio::async_read_until;
        using boost::asio::buffer;

        if (error) {
            std::cerr << "connection error: " << error << std::endl;

            if (endpoint_iterator == tcp::resolver::iterator())
            {
                std::cerr << "not connecting any longer" << std::endl;
                return;
            }

            socket_.close();

            tcp::endpoint endpoint = *endpoint_iterator;

            socket_.async_connect(
                endpoint,
                boost::bind(&line_client::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator));

            return;
        }

        async_read_until(
            socket_,
            buffer_,
            '\n',
            boost::bind(&line_client::handle_read,
                        this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }

    void handle_read(const boost::system::error_code& error, size_t size)
    {
        using boost::asio::async_read_until;
        using boost::asio::buffer;

        if (error) {
            do_close();
            return;
        }

        std::cout << &buffer_;

        async_read_until(
            socket_,
            buffer_,
            '\n',
            boost::bind(&line_client::handle_read,
                        this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }

    void do_write(std::string message)
    {
        using boost::asio::async_write;
        using boost::asio::buffer;

        bool write_in_progress = !write_msgs_.empty();

        write_msgs_.push_back(message);

        if (write_in_progress) {
            return;
        }

        async_write(
            socket_,
            buffer(write_msgs_.front().data(), write_msgs_.front().length()),
            boost::bind(&line_client::handle_write, this, boost::asio::placeholders::error));
    }

    void handle_write(const boost::system::error_code& error)
    {
        using boost::asio::async_write;
        using boost::asio::buffer;

        if (error) {
            do_close();
            return;
        }

        write_msgs_.pop_front();

        if (!write_msgs_.empty())
        {
            async_write(
                socket_,
                buffer(write_msgs_.front().data(), write_msgs_.front().length()),
                boost::bind(&line_client::handle_write, this, boost::asio::placeholders::error));
        }
    }

    void do_close() {
        std::cerr << "closing socket" << std::endl;
        socket_.close();
    }

private:
    boost::asio::io_service& io_service_;
    tcp::socket socket_;
    boost::asio::streambuf buffer_;
    chat_message_queue write_msgs_;
};

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: line_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], argv[2]);
        tcp::resolver::iterator iterator = resolver.resolve(query);

        line_client client(io_service, iterator);

        boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

        char line[4096];

        while (std::cin.getline(line, 4096))
        {
            using namespace std; // For strlen and memcpy.
            std::string message(line);
            client.write(message + "\n");
        }

        client.close();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

