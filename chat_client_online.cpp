#include<boost/asio.hpp>
#include<stdlib.h>
#include<iostream>
#include"./Headers/chat_client_online.h"

using std::string;
using boost::asio::ip::udp;

void chat_client_online::set_name() {
	client_name = std::to_string(rand());
}

chat_client_online::chat_client_online():client_name(""),ip(""),endpoint() {
	
}
chat_client_online::chat_client_online(udp::endpoint &ep):endpoint(ep) {
	ip = endpoint.address().to_string();
	set_name();
}
string chat_client_online::get_client_name() {
	return client_name;
}
udp::endpoint chat_client_online::get_endpoint() {
	return endpoint;
}
bool chat_client_online::operator== (chat_client_online &cc) {
	if(cc.endpoint == this->endpoint)
		return true;
	return false;
}
