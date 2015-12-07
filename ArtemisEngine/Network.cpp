#include "Network.h"


Network::Network()
{
	serverIP = "127.0.0.1";
	portNum = 8888;
	connection = false;
}

Network::~Network()
{

}

void Network::InitServer()
{
	int slen, recv_len;


	slen = sizeof(si_other);

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	else
	{
		printf("Winsock success!\n");

	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(portNum);

	if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Bind created!\n");

	}
	received = false;
	isServer = true;
}

void Network::InitClient()
{
	slen = sizeof(si_other);

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Winsock success!\n");

	}
	printf("Initialised.\n");

	//create socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(portNum);
	si_other.sin_addr.S_un.S_addr = inet_addr(serverIP);
	received = false;
	isServer = false;
}

void Network::SetOthersIP(char* ip)
{
	serverIP = ip;
}
void Network::SetUsedPort(unsigned short port)
{
	portNum = port;
}

void Network::Receive(int socket)
{
	int slen = sizeof(si_other);

	while (true)
	{
		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		if (!received)
			memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call
		
		if (msg > 0 || isServer)
		{
			if (recv_len = recvfrom(socket, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
			{
				printf("recvfrom() failed with error code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			}
			else
			{
				//printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
				//printf("Data: %s\n", buf);
				std::string check;
				std::string temp(buf);
			

				if (temp.compare("init") == 0)
				{
					printf("Connection made!");
					connection = true;
					Send("YKOK");
				}
				else if (temp.compare("YKOK") == 0)
				{
					printf("Connection made!");
					connection = true;
				}
				else
				{
					NetworkComponent* tempNC = new NetworkComponent(0);
					tempNC->Reform(buf);
					requestList.push_back(tempNC);
					received = true;
				}
				msg--;
				//puts(buf);
				
			}
		}
		// ja tähän loppui msg if
	}
}
void Network::Send(std::string msgToServer)
{
	Send(msgToServer, isServer);
}

void Network::Send(std::string msgToServer, bool server)//char* msgToServer
{
	for (int i = 0; i < msgToServer.size(); i++)
		message[i] = msgToServer[i];
	message[msgToServer.size()] = '\0';
	if (!server)
	{
		//send the message
		if (sendto(sock, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		else
		{
			msg++;
			//Sleep(2000);
		}
	}
	else
	{
		slen = sizeof(si_other);
		if (sendto(sock, message, strlen(message), 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		else
		{	
			msg++;
			printf("Data send!\n");
		}
	}
	memset(message, '\0', BUFLEN);
}