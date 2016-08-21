#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 4096

#include <Winsock2.h>
#include <Windows.h>
#include <Stdio.h>
#include <iostream>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

SOCKET* Connections;
SOCKET ClientSocket;
int ClientCount = 0;

void SendMessageToClient(int ID) {
	char* buffer = new char[4096];
	for (;;Sleep(75));
	{
		memset(buffer, 0, sizeof(buffer));
		if (recv(Connections[ID], buffer, 4096, NULL))
		{
			printf(buffer, "\n");
			for (int i = 0; i <= ClientCount; i++)
			{
				send(Connections[i], buffer, strlen(buffer), NULL);
			}
		}
	}
	delete buffer;
}

int main() {

	int iResult;

	WSADATA wsaData;

	//initialization winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	else
	{
		cout << "Initialization : success" << endl;
	}

	//creating server
	struct addrinfo *result = NULL, *ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	//https://msdn.microsoft.com/ru-ru/library/windows/desktop/bb530742(v=vs.85).aspx
	//creating server socket

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
	}
	else
	{
		cout << "Getaddrinfo socket : success" << endl;
	}

	SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(result->ai_family,
		result->ai_socktype,
		result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
	{
		printf("Error at socket(); %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	else
	{
		cout << "Creation socket : sucess" << endl;
	}

	//setting socket
	ClientSocket = INVALID_SOCKET;

	iResult = bind(ListenSocket,
		result->ai_addr,
		(int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else
	{
		cout << "Bind socket : sucñess" << endl;
	}

	freeaddrinfo(result);

	//listenin socket
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else
	{
		cout << "Listening : sucñess" << endl;
	}

	cout << "Server started!" << endl;

	//Confirming client connectivity
	char m_connect[] = "Connect...;;;5";
	for (;;Sleep(75)) {
		if (ClientSocket = accept(ListenSocket, NULL, NULL));
		{
			printf("Client conection");
			Connections[ClientCount] = ClientCount;
			send(Connections[ClientCount], m_connect, strlen(m_connect), NULL);
			ClientCount++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendMessageToClient, (LPVOID)(ClientCount - 1), NULL, NULL);
		}
	}
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	cout << "Server stoped" << endl;

	system("pause");
	return 0;
}