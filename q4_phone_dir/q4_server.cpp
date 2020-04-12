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

// the local phone directory database
map <string, string> phone_dir;


// simple function to output error messages
void display_error(char *err_msg) {
	perror(err_msg);
	exit(1);
}

void *clientReader(void *args) {

	// get the server socket FD
	int server_socket = *((int *) args);

	// create read buffer
	char buffer[BFSZ];

	// create client address object
	struct sockaddr_in client_address;
	memset(&client_address, 0, sizeof(client_address));
	int len = sizeof(client_address);

	// respond to queries
	while(1) {

		// clear previous buffer
		memset(buffer, 0, BFSZ);

		// read message
		recvfrom(server_socket, (char *)buffer, BFSZ, MSG_WAITALL, (struct sockaddr * ) &client_address, (socklen_t *) &len);
		
		if (buffer[0] == '*') {
			printf("[ Q ] Quitting...\n");

			// close the socket
			close(server_socket);
			break;
		}

		// check for consistent data (Only alphabets or Only Digits)
		int n = strlen(buffer), dc = 0;
		for (int i=0;i<n;i++) {
			if (buffer[i] >= '0' and buffer[i] <= '9') {
				dc++;
			}
		}

		if (dc == n) {
			printf("[ N ] Client has asked name of number: %s\n", buffer);

			string num(buffer);

			int f = 0;
			for (auto i : phone_dir) {
				if (i.second == num) {
					f = 1;
					// get the name
					memset(buffer, 0, BFSZ);
					strcpy(buffer, (i.first).c_str());
					break;
				}
			}

			if (f == 0) {
				memset(buffer, 0, BFSZ);
				strcpy(buffer, "Number not found in the directory!");
			}

			// reply the message to the client
			sendto(server_socket, buffer, BFSZ, MSG_CONFIRM, (struct sockaddr *) &client_address, len);	
		}
		else if (dc == 0) {
			printf("[ N ] Client has asked number for name: %s\n", buffer);

			string name(buffer);
			transform(name.begin(), name.end(), name.begin(), ::tolower);
			int f = 0;
			for (auto i : phone_dir) {
				if (i.first == name) {
					f = 1;
					// get the name
					memset(buffer, 0, BFSZ);
					strcpy(buffer, (i.second).c_str());
					break;
				}
			}

			if (f == 0) {
				memset(buffer, 0, BFSZ);
				strcpy(buffer, "Name not found in the directory!");
			}

			// reply the message to the client
			sendto(server_socket, buffer, BFSZ, MSG_CONFIRM, (struct sockaddr *) &client_address, len);

		}
		else {
			printf("[ E ] Invalid query format! String should not contain both Alphabets and Digits\n");
			memset(buffer, 0, BFSZ);
			strcpy(buffer, "Invalid Query format. Please enter only Alphabets or only Digits");
			sendto(server_socket, buffer, BFSZ, MSG_CONFIRM, (struct sockaddr *) &client_address, len);	
		}
	}

}

// the main guy
int main(int argc, char const *argv[]) {
	
	// creating socket
	int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
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

	printf("[ I ] Connections are allowed now...\n");

	// create a read thread to answer client queries
	pthread_t pid;
	pthread_create(&pid, NULL, &clientReader, (void*) &server_socket);


	printf("[ * ] Enter a { name : number } entry to store in the database (Ex: John 1234567890) [Enter * -1 to exit]\n");
	
	// loop to enter phone dir data any time
	while(1) {
		string name, num;
		cin >> name >> num;

		transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (name == "*" or num == "-1") {			
			close(server_socket);
			printf("[ Q ] Quitting...\n");
			break;
		}

		phone_dir[name] = num;
	}

	// terminate the thread
	pthread_join(pid, NULL);

	return 0;
}