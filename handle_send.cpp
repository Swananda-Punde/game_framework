#include<iostream>
#include<thread>
#include<boost/asio.hpp>
#include "./Headers/handle_send.h"

using std::thread;
using std::cout;
using boost::asio::ip::udp;

size_t handle_send(udp::socket socket, udp::endpoint receiver_endpoint, char msg[])
{
	
	return socket.send_to(boost::asio::buufer(msg), receiver_endpoint);
}
