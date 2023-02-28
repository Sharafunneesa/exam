/************ SOCKET PROGRAMMING FOR SERVER **********/

// including all header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// defining the port number is 9999
#define PORT 9999

//driving code
int main()
{
        // declairing the variables
        int arrpid[10],i;
        int sockfd, ret;
	int newSocket;
	// declairing the structure used in it
	struct sockaddr_in serverAddr;
        struct sockaddr_in newAddr;

	socklen_t addr_size;
        
        // take a buffer with 256 bytes
	char buffer[256];
	pid_t childpid;
        
        //creating the client socket and checking it created or not(init is local comm domain)
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Server Socket is created.\n");
       
        //using memset we are filling the client socket with null value
	memset(&serverAddr, '\0', sizeof(serverAddr));
	
	
	// ip address from internet (version 4)
	serverAddr.sin_family = AF_INET;
	// port we are assigning
	serverAddr.sin_port = htons(PORT);
	//assiging the ip address
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        // using bind binding the client into server
	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0)
	{
		printf("Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	//listen for the client using listen command for multiple client
	if(listen(sockfd, 10) == 0)
	{
		printf("[+]Listening....\n");
	}

	else
	{
		printf("[-]Error in binding.\n");
	}

        //taking while loop for infinite writing
	while(1)
	{
	
	        //accept the client connection 
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0)
		{
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		//
		if((childpid = fork()) == 0)
		{   
		       for(i=0; i< newSocket ; i++)
		       {
		         //storing the pids of clinet in array
		         arrpid[i++] = getpid();
		       }
		       /* printing the pids of client 
		       for(i =0; i<=newSocket ; i++)
                                 printf("%d\t",arrpid[i]); */
		       
		       close(sockfd);

			while(1)
			{ 
                               ////using bzero clear the buffer
				bzero(buffer, sizeof(buffer));
				
				//reading from the buffer
				read (newSocket,buffer,sizeof(buffer));
                              
				//condition to convert the lower case to upper cases received from client
				int i=0;
				for(i=0;buffer[i]!='\0';i++)
				{       
				        // checking the given character is in between a to z
					if (buffer[i] >= 'a' && buffer[i] <= 'z')
					{
						buffer[i]-=32;
					}
					else if(buffer[i] >= 'A' && buffer[i] <= 'Z')
					{
						buffer[i]+=32;
					}
				}

                                
				// print buffer which contains the client contents
				printf("From client %d : %s\t To client : ",newSocket, buffer);

				// This function is used to set all the socket structures with null values
				bzero(buffer, sizeof(buffer));
				int n = 0;

				// copy server message in the buffer 
				// if char contains \n means jump to client
				while ((buffer[n++] = getchar()) != '\n');

				// and sending that buffer to client
				write(newSocket, buffer, sizeof(buffer)); 

			}
		}

	}
	close(newSocket);
       return 0;
}


