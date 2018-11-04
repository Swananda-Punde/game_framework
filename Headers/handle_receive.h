#ifndef HANDLE_RECEIVE
#define HANDLE_RECEIVE

#include<boost/asio.hpp>
#include "chat_proto.h"

chat_proto handle_receive(udp::socket, udp::socket *);

#endif
