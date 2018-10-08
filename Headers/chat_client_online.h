#ifndef CHAT_CLIENT_ONLINE//chat_client_online
#define CHAT_CLIENT_ONLINE//chat_client_online

#include<boost/asio.hpp>
#include<stdlib.h>
#include<iostream>

using std::string;
using boost::asio::ip::udp;

class chat_client_online{
	private :
		string client_name, ip;
		udp::endpoint endpoint;

		void set_name();
	public :
		chat_client_online();
		chat_client_online(udp::endpoint&);
		string get_client_name();
		udp::endpoint get_endpoint();
		bool operator== (chat_client_online &cc);
};

#endif
