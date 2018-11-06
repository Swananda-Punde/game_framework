#include<iostream>
#include<boost/asio.hpp>
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include<sstream>
#include<string>
#include"./Headers/chat_proto.h"
#include"./Headers/handle_receive.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using boost::asio::ip::udp;
using namespace boost::archive;

chat_proto handle_receive(udp::socket &socket, udp::endpoint *sender_endpoint)
{
	chat_proto temp;
	char buffer[1024];
	size_t len = socket.receive_from(boost::asio::buffer(buffer), (*sender_endpoint));

	std::istringstream ss(buffer);
	text_iarchive ia(ss);

	ia >> temp;

	return temp;
}
