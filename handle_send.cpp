#include<iostream>
#include<thread>
#include<boost/asio.hpp>
#include<string.h>
#include "./Headers/handle_send.h"

using std::thread;
using std::cout;
using boost::asio::ip::udp;

size_t handle_send(udp::socket &socket, udp::endpoint receiver_endpoint, char *msg)
{
	char buffer[1024];
	strcpy(buffer,msg);
	return socket.send_to(boost::asio::buffer(buffer), receiver_endpoint);
}
