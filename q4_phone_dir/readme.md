# Manual for using the code files

## Question 4: UDP Server-Client application modelling Phone Directory Service

### Features
- Language used: **C++14**
- Libraries used: 
	- **netinet/in.h** - For using the IPv4 macros
	- **sys/socket.h** - For using socket functions
	- **sys/types.h**
	- **unistd.h** - for sleep and other functions
	- **pthread** - for C threads
- This is a **UDP** client-server that simulates a Phone Directory Service
- Client sends Name (or Phone Number) of a person and server replies with the Phone Number (or Name) respectively. 
- Supports Name queries and Number queries
- Supports real-time local-db update
- Uses **PORT 7070** for communication
- Uses **2 threads** for efficient execution
	- One for asynchronously answering queries by the clients
	- One to enter data to the local database
- Uses the **STL map** data structure as the local database
---

### Prerequisites
- Linux Ubuntu Operating System
- G++ [Compiler](https://gcc.gnu.org/)
- PORT 7070 open in the system
- pthread library
---

### File Description
- **q4_server.cpp**
	- This is the main file that is to be run to get the server started
- **q4_client.cpp**
	- This is the client side code to be run to connect to the server
- **q4.png**
	- This is a sample output of the code
---

### Running the code
- Run the **q4_server.cpp** in Terminal 1 as:
	- `$ g++ q4_server.cpp -o s -lpthread`
	- `$ ./s`
	- This will start the server on PORT 7070
	
- Run the **q4_client.cpp** in Terminal 2 as:
	- `$ g++ q4_client.cpp -o c`
	- `$ ./c`
	- This will connect the client to the server
	
- Once the client is connected to the server:
	- Operations on Client side:
		- Enter a Name or Phone Number in the client terminal
		- That gets printed in the server terminal
		- Server checks this number in the **map** database and replies with appropriate data, if found
		- If client sends a mixed AlphaNumeric query (Ex: John12), then server rejects such queries
		- Enter `*` in the client terminal to stop the conversation
	- Operations on Server side:
		- Takes in queries from the client on a separate thread for concurrent query execution
		- Takes in input from user on server side (server terminal) as {name : number} data to be input in the local database
		- Rejects invalid queries from the client
		- Enter `-1 -1` in the server terminal to stop the conversation and the thread execution

---
### Sample Output
![](https://github.com/bmsohwinc/cn_assignment/blob/master/q4_phone_dir/q4.png)
