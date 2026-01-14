#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

/*INADDR_ANY is a constant that means "Listen on everything." * 
If your computer has Wi-Fi, Ethernet, and a Local Loopback (127.0.0.1), 
your server will be reachable from all of them.
Technically: INADDR_ANY is usually defined as 0.0.0.0.*/

/*htons(): to ensure port numbers and other short values are correctly interpreted 
by all devices on a network, regardless of their native byte order.*/




int main() {

    // 1. Create the socket (IPv4, TCP)

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    

    // 2. Setup the address structure (Port 8080)

    struct sockaddr_in address;

    address.sin_family = AF_INET;

    address.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces

    address.sin_port = htons(8080);       // Host To Network Short


	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}


    // // 3. Bind the socket to the port

    // bind(server_fd, (struct sockaddr *)&address, sizeof(address));



    // 4. Start listening

    listen(server_fd, 3);

    std::cout << "Server listening on port 8080..." << std::endl;



    // 5. Accept a connection

    int addrlen = sizeof(address);

    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    

    // 6. Read data from the client

    char buffer[1024] = {0};

    read(new_socket, buffer, 1024);

    std::cout << "Message received: " << buffer << std::endl;



    close(new_socket);

    close(server_fd);

    return 0;

}


//In your Configuration File later in the project, you will have a line that says listen 127.0.0.1:8080. Your parser will have to split that:
// Convert 127.0.0.1 into the s_addr (using a function like inet_addr()).
// Convert 8080 into the sin_port (using htons()).