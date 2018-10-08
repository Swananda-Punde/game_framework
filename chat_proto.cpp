#include<iostream>
#include<list>
#include<boost/asio.hpp>
#include<boost/archive/text_oarchive.hpp>
#include"./Headers/chat_client_online.h"
#include "./Headers/chat_proto.h"

using std::string;
using boost::asio::ip::udp;
using boost::asio::io_service;
using std::list;
using namespace boost::archive;

list<chat_client_online> *client_list;
udp::socket *socket_ptr;

void configure_chat(io_service io_service, int port_no, list<chat_client_online> *ptr)
{
	client_list = ptr;
	socket_ptr = new udp::socket(io_service, udp::endpoint(udp::v4(), port_no));
}

bool send_chat(chat_proto obj)
{
	std::stringstream ss;
	text_oarchive oa(ss);
	try
	{
		oa << obj;

		list<chat_client_online> &ref = (*client_list);
		list<chat_client_online> :: iterator itr;
		for(itr = ref.begin(); itr != ref.end(); itr++)
		{
			udp::endpoint send_endpoint = (*itr).get_endpoint();
			//(*socket).send_to(boost::asio::buffer(ss.str(),ss.str().length()),send_endpoint);
			(*socket_ptr).send_to(boost::asio::buffer(ss.str(),ss.str().length()),send_endpoint);
		}
		return true;
	}
	catch(...)//auto e)
	{
		return false;
	}
}
