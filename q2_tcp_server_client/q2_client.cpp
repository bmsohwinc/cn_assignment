/*

	Taking multi-word input from user:
	1. https://stackoverflow.com/questions/5838711/stdcin-input-with-spaces
	

*/

#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <chrono>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 7070
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

	printf("[ I ] Connection Successful!\n");

	// create read buffer
	char buffer[BFSZ];

	// talk to the server
	while(1) {

		// clear previous buffer
		memset(buffer, 0, BFSZ);

		// get multi-word input from user
		printf("[ I ] Enter your message to server (`*` to exit): ");
		cin.getline(buffer, BFSZ);

		// send message to server
		send(client_socket, buffer, BFSZ, 0);

		if (buffer[0] == '*') {
			printf("[ Q ] Quitting...\n");

			// close the socket
			close(client_socket);
			break;
		}

		// read the ACK
		memset(buffer, 0, BFSZ);
		read(client_socket, buffer, BFSZ);
		printf("[ I ] Server says: %s\n", buffer);
	}

	return 0;
}