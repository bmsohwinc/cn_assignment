/*

	Opening the PORT 13 in ubuntu system:
	1. https://unix.stackexchange.com/questions/370928/how-do-i-launch-the-daytime-service

	Checking if a PORT is open and running:
	1. https://serverfault.com/questions/309052/check-if-port-is-open-or-closed-on-a-linux-server

	Daytime Protocol:
	1. https://en.wikipedia.org/wiki/Daytime_Protocol

*/

#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <chrono>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 13
#define BFSZ 1024

using namespace std;

// simple function to output error messages
void display_error(char *err_msg) {
	perror(err_msg);
	exit(1);
}

// the main guy
int main(int argc, char const *argv[]) {

	// check for correct input
	if (argc < 2) {
		printf("Wrong input format. Usage:\n$ ./client [server-ip-address]\n");
		return -1;
	}
	
	// creating socket
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0) {
		display_error((char *)"Socket creation failed!\n");
	}

	// create address object
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);

	// add the server IP to the address object
	if (inet_pton(AF_INET, argv[1], &server_address.sin_addr) < 0) {
		display_error((char *)"Address binding failed! Invalid address\n");
	}

	// connect to the server
	if (connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
		display_error((char *)"Connection failed\n");
	}

	// talk with the server
	printf("[ I ] Connection Successful!\n");

	// create read buffer
	char buffer[BFSZ];

	// read the messages
	memset(buffer, 0, BFSZ);
	read(client_socket, buffer, BFSZ);

	// print them
	printf("\n[ I ] DayTime Server says: %s\n", buffer);

	return 0;
}