#include<iostream>
#include<string>
#include<boost/asio.hpp>
#include<list>
#include<sstream>
#include<iterator>
#include<boost/archive/text_oarchive.hpp>
#include"../Headers/chat_client_online.h"
#include"../Headers/chat_proto.h"


using std::cout;
using std::cin;
using std::string;
using std::endl;
using boost::asio::ip::udp;
using std::list;
using namespace boost::archive;

extern udp::socket *socket_ptr;

void configure_chat(list<chat_client_online> *);
bool send_chat(chat_proto);

class server {

	private : 
		boost::asio::io_service io_service;
		list<chat_client_online> client_list;

		bool add_client(chat_client_online &cc) {
			
			list<chat_client_online> :: iterator itr;
			for(itr = client_list.begin(); itr != client_list.end(); itr++)
			{
				cout <<(*itr).get_endpoint().address().to_string()<<endl;
				if((*itr) == cc)
					return false;
			}
			client_list.push_front(cc);
			return true;
				
		}
	public :
		server(boost::asio::io_service &io_service, int port)
		{
			char buffer[1024];
			chat_proto temp;
			chat_client_online *cc;
			udp::socket socket(io_service, udp::endpoint(udp::v4(), port));
			
			socket_ptr = &socket;
			
			configure_chat(&client_list);
			
			while(true)
			{
				buffer[0] = '\0';
				udp::endpoint client_endpoint;
				size_t length = socket.receive_from(boost::asio::buffer(buffer,1024),client_endpoint);
				
				cc = new chat_client_online(client_endpoint);
				add_client((*cc));
				
				std::istringstream ss(buffer);
				text_iarchive ia(ss);
				ia >> temp;
				
				temp.set_from(client_endpoint.address().to_string());
				//cout << "\nReceved from Client : "<< temp.get_msg()<<" : "<<client_endpoint.address().to_string() << endl;
				send_chat(temp);
			}
		}

};//server class ends

int main(int argc, char *argv[])
{
	if(argc < 2 )
	{
		cout << "required arguments : ./server <port>"<<endl;
		return 0;
	}
	boost::asio::io_service io_service;
	server server(io_service, atoi(argv[1]));
}


