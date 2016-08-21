#define DEFAULT_PORT "27015"

#include <Winsock2.h>
#include <Windows.h>
#include <Stdio.h>
#include <iostream>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main() {

	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	cout << "ZeroMemory created" << endl;

	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);

}