#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <chrono>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BFSZ 1024
#define MX_RQSTS 10
#define PORT 7070

using namespace std;

// simple function to output error messages
void display_error(char *err_msg) {
	perror(err_msg);
	exit(1);
}

// the main guy
int main(int argc, char const *argv[]) {
	
	// creating socket
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		display_error((char *)"Socket creation failed!\n");
	}

	// set socket options to reuse the PORT
	int opt = 1;
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
		display_error((char *)"Set sock opt failed!\n");
	}

	// create address object and set parameters
	struct sockaddr_in server_address;
	int adrln = sizeof(server_address);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(PORT);

	// bind the socket to the PORT
	if (bind(server_socket, (struct sockaddr * ) &server_address, sizeof(server_address)) < 0) {
		display_error((char *)"Bind Socket failed!\n");
	}

	// listen on the PORT
	if (listen(server_socket, MX_RQSTS) < 0) {
		display_error((char *)"Listen failed!\n");
	}

	printf("[ I ] Waiting for a connection...\n");

	// accept the incoming connection
	int client_socket = accept(server_socket, (struct sockaddr * ) &server_address, (socklen_t *) &adrln);
	if (client_socket < 0) {
		display_error((char *)"Accept failed!\n");
	}

	printf("[ I ] Connection Successful!\n");

	// create read buffer
	char buffer[BFSZ];

	// talk to the client
	while(1) {

		// clear previous buffer
		memset(buffer, 0, BFSZ);

		// read the client's message
		memset(buffer, 0, BFSZ);
		read(client_socket, buffer, BFSZ);
		printf("[ I ] Client says: %s\n", buffer);

		if (buffer[0] == '*') {
			printf("[ Q ] Quitting...\n");

			// close the socket
			close(server_socket);
			close(client_socket);
			break;
		}

		// send ACK to client
		memset(buffer, 0, BFSZ);
		strcpy(buffer, "Message Received!");
		send(client_socket, buffer, BFSZ, 0);		
	}


	return 0;
}