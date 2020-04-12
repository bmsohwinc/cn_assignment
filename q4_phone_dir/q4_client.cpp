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

	// creating socket
	int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (client_socket < 0) {
		display_error((char *)"Socket creation failed!\n");
	}

	// create address object
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// create read buffer
	char buffer[BFSZ];
	int len = sizeof(server_address);

	// talk to the server
	while(1) {

		// clear previous buffer
		memset(buffer, 0, BFSZ);

		// get multi-word input from user
		printf("[ I ] Enter Name/Numer to search in the server's phone dir (`*` to exit): ");
		cin.getline(buffer, BFSZ);

		// send message to server
		sendto(client_socket, (char *) buffer, BFSZ, MSG_CONFIRM, (struct sockaddr *) &server_address, len);

		if (buffer[0] == '*') {
			printf("[ Q ] Quitting...\n");

			// close the socket
			close(client_socket);
			break;
		}

		// read the ACK
		memset(buffer, 0, BFSZ);
		recvfrom(client_socket, (char *)buffer, BFSZ, MSG_WAITALL, (struct sockaddr * ) &server_address, (socklen_t *) &len);
		printf("[ I ] Server says: %s\n", buffer);
	}

	return 0;
}