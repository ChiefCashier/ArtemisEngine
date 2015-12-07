#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib") //Winsock Library

//#define SERVER "127.0.0.1"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
//#define PORT 8888   //The port on which to listen for incoming data

#include <stdio.h>
#include <winsock2.h>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <mutex>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <vector>

#include "NetworkComponent.h"

class Network
{
public:

	Network();//Should I make a singleton?
	~Network();

	void InitServer();
	void InitClient();

	void Send(std::string msgToServer);

	void SetOthersIP(char* ip);
	void SetUsedPort(unsigned short port);

	bool IsReceived(){ return received; };
	bool Connection(){ return connection; }
	char* Return(){ return buf; };


	std::thread* makeThread()
	{
		std::thread* receiveThread = new std::thread(&Network::Receive, this, sock);
		return receiveThread;
	};

	std::vector<NetworkComponent*> GetListOfRequests()
	{
		return requestList; 
	};

	void EmptyListOfRequests()
	{
		requestList.clear();
	};

	bool IsServer(){ return isServer; };

private:

	void Receive(int socket);

	void Send(std::string msgToServer, bool server);

	std::vector<NetworkComponent*> requestList;

	WSADATA wsa;
	SOCKET sock;


	struct sockaddr_in server, si_other;


	int slen, recv_len;
	int msg = 0;


	char message[BUFLEN];
	char buf[BUFLEN];
	char* serverIP;


	unsigned short portNum;


	bool isServer;
	bool received;
	bool connection;
};

