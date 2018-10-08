chat_proto.so : chat_proto.o chat_client_online.o
		g++ -shared -o chat_proto.so chat_proto.o chat_client_online.o -lm -fPIC

chat_client_online.o : chat_client_online.cpp ./Headers/chat_client_online.h
		g++ -o chat_client_online.o -c chat_client_online.cpp  -lboost_system -lpthread -fPIC

chat_proto.o : chat_client_online.o
		g++ -c chat_proto.cpp chat_client_online.o -lboost_system -lpthread -lboost_serialization  -fPIC -o chat_proto.o

clean : rm chat_proto.o chat_client_online.o chat_proto.so
