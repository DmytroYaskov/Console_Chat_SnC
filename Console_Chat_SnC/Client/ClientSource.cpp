#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 4096

#include <Winsock2.h>
#include <Windows.h>
#include <Stdio.h>
#include <iostream>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

SOCKET ConnectSocket = INVALID_SOCKET;

int main(int argc, char **argv) {

	//initialize Winsock

	int iResult;

	WSADATA wsaData;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed; %d\n", iResult);
		return 1;
	}
	else {
		printf("WSAStartup inicialization: success");
	}

	//Creating socket

	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	cout << "ZeroMemory created" << endl;

	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	else {
		printf("getaddrinfo socket: succes");
	}

	//Call the socket function 
	ptr = result;

	ConnectSocket = socket(ptr->ai_family,
		ptr->ai_socktype,
		ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): &ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup;
		return 1;
	}
	else {
		printf("Socket ", INVALID_SOCKET, " success");
	}

	//connect to server
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server !\n");
		WSACleanup();
		return 1;
	}

	//sending message to server

	int recvbuflen = DEFAULT_BUFLEN;

	char *sendbuf;
	cout << "input message :" << endl;
	cin >> sendbuf;
	char recvbuf[DEFAULT_BUFLEN];

	//1.send

	iResult = send(ConnectSocket,
				   sendbuf,
				   (int)strlen(sendbuf),
				   0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	printf("Bytes Sent: %ld\n", iResult);

	//2.shutdown send

	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	//3.receive data

	do {
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());
	} while (iResult > 0);
}