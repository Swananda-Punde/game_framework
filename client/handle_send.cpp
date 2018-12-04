#include<iostream>
#include<thread>
#include<boost/asio.hpp>
#include<string.h>
#include<boost/archive/text_oarchive.hpp>
#include "../Headers/handle_send.h"
#include "../Headers/chat_proto.h"

using std::thread;
using std::cout;
using std::string;
using boost::asio::ip::udp;
using namespace boost::archive;

size_t handle_send(udp::socket &socket, udp::endpoint receiver_endpoint, char *msg)
{
	char buffer[1024];
	chat_proto temp(socket.local_endpoint().address().to_string(),msg);
	
	std::stringstream ss;
	text_oarchive oa(ss);
	
	oa << temp;
	//strcpy(buffer,msg);
	return socket.send_to(boost::asio::buffer(ss.str(),ss.str().length()), receiver_endpoint);
}
