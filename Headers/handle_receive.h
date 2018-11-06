#ifndef HANDLE_RECEIVE
#define HANDLE_RECEIVE

#include<boost/asio.hpp>
#include "chat_proto.h"

using boost::asio::ip::udp;

chat_proto handle_receive(udp::socket&, udp::endpoint *);

#endif
