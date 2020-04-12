/*

	Opening the PORT 13 in ubuntu system:
	1. https://unix.stackexchange.com/questions/370928/how-do-i-launch-the-daytime-service

	Checking if a PORT is open and running:
	1. https://serverfault.com/questions/309052/check-if-port-is-open-or-closed-on-a-linux-server

	Daytime Protocol:
	1. https://en.wikipedia.org/wiki/Daytime_Protocol

*/


import java.net.*;
import java.io.*;

public class dayTimeClient {

	public static void main(String[] args) {

		// Set my IP and PORT
		String ip = "127.0.0.1";
		int port = 13;

		try (Socket socket = new Socket(ip, port)) {

			// To read the data from the Daytime Server
			InputStream input = socket.getInputStream();
			InputStreamReader reader = new InputStreamReader(input);

			// To construct the string, char by char
			int character;
			StringBuilder data = new StringBuilder();

			while((character = reader.read()) != -1) {
				data.append((char) character);
			}

			// Print the data
			System.out.println(data);
		}

		// Report exceptions
		catch (UnknownHostException ex) {
			System.out.println("Server not found: " + ex.getMessage());
		}
		catch (IOException ex) {
			System.out.println("IO Error: " + ex.getMessage());
		}
	}
}

