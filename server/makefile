
server : chat_client_online.o
		g++ -g server.cpp -o server chat_client_online.o -lboost_system -lboost_serialization -lpthread -lchat_proto

chat_client_online.o : ../chat_client_online.cpp ../Headers/chat_client_online.h
		g++ -o chat_client_online.o -c ../chat_client_online.cpp  -lboost_system -lpthread -fPIC
		
clean : 
	rm chat_client_online.o server
