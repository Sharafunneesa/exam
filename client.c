/******* SOCKET PROGRAMMING FOR CLIENT ***********/

//including all header files 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// defining prot number as 9999 
#define PORT 9999

/* driver code */
int main()
{

        //declairing all the needed sockets, structure and variables 
	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[256];

        //creating the client socket and checking it created or not(init is local comm domain) 
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	else
	{
	        printf("[+]Client Socket is created.\n");
        }
        
	bzero(&serverAddr, sizeof(serverAddr));
	
	// using memset we are filling the client socket with null value 
	memset(&serverAddr, '\0', sizeof(serverAddr));
	
	// ip address from internet (version 4)
	serverAddr.sin_family = AF_INET;
	
	// port we are assigning
	serverAddr.sin_port = htons(PORT);
	
	//assiging the ip address
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        //connecting the clinet socket with server 
	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	
	// printing the usage message
	if(ret != 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	

	printf("[+]Connected to Server.\n");
        
       
	while(1)
	{
	        //using bzero clear the buffer
		bzero(buffer, sizeof(buffer));
		
		printf("To server: ");
		
		int n=0;
		
		//writing the message to buffer
		while ((buffer[n++] = getchar()) != '\n');
		write(clientSocket, buffer, sizeof(buffer));
		
		//reading the message from buffer
		read(clientSocket, buffer,sizeof(buffer));
		printf("server \t %s", buffer);
               
               //condition to convert the lower case to upper cases received from client
		
		int i=0;
		for(i=0;buffer[i]!='\0';i++)
		{
		     //cheking the given character is in between a to z
		     if (buffer[i] >= 'a' && buffer[i] <= 'z')
		     {
			    buffer[i]-=32;
		     }
		
		     else if(buffer[i] >= 'A' && buffer[i] <= 'Z')
		     {
		            buffer[i]+=32;
		     }
		}
		
               printf("\tThe String Echoed from client : %s", buffer);

		//recieving the message send by the server and printing
		if(recv(clientSocket, buffer, 1024, 0) < 0)
		{
			printf("[-]Error in receiving data.\n");
		}
		else
		{
			printf("Server : \t%s\n", buffer);
		} 
	}
}



