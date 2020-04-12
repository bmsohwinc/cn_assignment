# Manual for using the code files

## Question 1: Simple DayTime Client application

### Features
- Language used: **C++14**
- Libraries used: 
	- **netinet/in.h** - For using the IPv4 macros
	- **sys/socket.h** - For using socket functions
	- **sys/types.h**
	- **unistd.h** - for sleep and other functions
- This is a simple client for Day Time Server
- Prints the current date and time to the console
- Connects over **PORT 13** to get the data from the system's server
---

### Prerequisites
- Linux Ubuntu Operating System
- G++ [Compiler](https://gcc.gnu.org/)
- PORT 13 running in the system
- If JAVA code is to be run, 
	- [open-jdk 11](https://openjdk.java.net/projects/jdk/11/)
---

### Enabling PORT 13 (if disabled)
- Follow [this](https://unix.stackexchange.com/questions/370928/how-do-i-launch-the-daytime-service) link to enable port 13 using xinetd
- Follow [this](https://serverfault.com/questions/309052/check-if-port-is-open-or-closed-on-a-linux-server) link to check if the port is up and running
---

### File Description
- **day_time_client.cpp**
	- This is the main file that is to be run to get the desired output
- **dayTimeClient.java**
	- This is also another file doing the same task, but in JAVA
- **q1.png**
	- This is a sample output of the code
---

### Running the code
- To compile and run the **C++ code**
	- `$ g++ day_time_client.cpp -o dtc`
	- `$ ./dtc 127.0.0.1`

- To compile and run the **JAVA code**
	- `$ javac dayTimeClient.java`
	- `$ java dayTimeClient`
---
