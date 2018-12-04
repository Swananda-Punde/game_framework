#include<iostream>
#include<boost/asio.hpp>
#include "../Headers/chat_proto.h"
#include "../Headers/handle_send.h"
#include "../Headers/handle_receive.h"
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include<sstream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using boost::asio::ip::udp;
using namespace boost::archive;

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		cout << "Required arguments : ./clent <ip address> <port>" << endl;
		return 0;
	}
	try
	{
		boost::asio::io_service io_service;
		udp::resolver resolver(io_service);

		udp::endpoint receiver_endpoint = *resolver.resolve(udp::v4(), argv[1], argv[2]).begin();

		udp::socket socket(io_service);
		socket.open(udp::v4());

		chat_proto temp;

		for(int i= 0; ;i++)
		{
			char buffer[1024];
			
			cout << "Enter Message To send : ";
			cin >> buffer;
			if(strcmp(buffer,"exit") == 0)
				break;
			handle_send(socket, receiver_endpoint, buffer);
			/*socket.send_to(boost::asio::buffer(buffer), receiver_endpoint);*/

			udp::endpoint sender_endpoint;
		/*
			temp = handle_receive(socket, &sender_endpoint);
			cout<< "\nReceived from : "<<temp.get_from()<< " : "<<temp.get_msg()<<endl;
		*/
		}
	}
	catch(std::exception &e) 
	{
		cout<<"\nError Occuured \n"<<e.what()<<endl;
	}
}
