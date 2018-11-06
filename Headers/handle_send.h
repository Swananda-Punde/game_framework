#ifndef HANDLE_SEND
#define HANDLE_SEND

#include<boost/asio.hpp>
#include<iostream>

using boost::asio::ip::udp;

size_t handle_send(udp::socket&, udp::endpoint, char *);

#endif
