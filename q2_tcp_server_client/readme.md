# Manual for using the code files

## Question 2: Simple TCP Server-Client application

### Features
- Language used: **C++14**
- Libraries used: 
	- **netinet/in.h** - For using the IPv4 macros
	- **sys/socket.h** - For using socket functions
	- **sys/types.h**
	- **unistd.h** - for sleep and other functions
- This is a simple **TCP** client-server **chat application**
- Client sends the messages and server prints them in the console
- Supports multi-word messages
- Uses **PORT 7070** for communication
---

### Prerequisites
- Linux Ubuntu Operating System
- G++ [Compiler](https://gcc.gnu.org/)
- PORT 7070 open in the system
---

### File Description
- **q2_server.cpp**
	- This is the main file that is to be run to get the server started
- **q2_client.cpp**
	- This is the client side code to be run to connect to the server
- **q2.png**
	- This is a sample output of the code
---

### Running the code
- Run the **q2_server.cpp** in Terminal 1 as:
	- `$ g++ q2_server.cpp -o s`
	- `$ ./s`
	- This will start the server on PORT 7070
	
- Run the **q2_client.cpp** in Terminal 2 as:
	- `$ g++ q2_client.cpp -o c`
	- `$ ./c 127.0.0.1`
	- This will connect the client to the server
	
- Once the client is connected to the server:
	- Enter any message in the client terminal
	- That gets printed in the server terminal
	- Server automatically sends back an ACK, which is displayed in the client terminal
	- Enter `*` in the client terminal to stop the conversation