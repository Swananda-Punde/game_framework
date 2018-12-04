
client : handle_send.o handle_receive.o ../Headers/chat_proto.h
	g++ client.cpp -o client handle_send.o handle_receive.o -lboost_system -lboost_serialization -lpthread

handle_send.o : ../Headers/handle_send.h
	g++ ../handle_send.cpp -o handle_send.o -lboost_system -c -lpthread

handle_receive.o : ../Headers/handle_receive.h
	g++ ../handle_receive.cpp -o handle_receive.o -c -lboost_system -lpthread

clean : 
	rm handle_send.o handle_receive.o
