#define DEFAULT_PORT "27015"

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

	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
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
	ptr=result;

	ConnectSocket = socket(ptr->ai_family,
						   ptr->ai_socktype,
						   ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): &ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup;
		return 1;
	}
}