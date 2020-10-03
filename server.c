#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{

	/* Variables */
        int sock;
	struct sockaddr_in server;
        int mysock;
	char buff[1024];
	int rval;

	 /* Create Socket */
        
		
	 sock = socket(AF_INET,SOCK_STREAM,0);
	 printf("sock : %d\n",sock);
	 if(sock < 0)
	 {
            perror("Failed to create socket");
	    exit(1);
	 }

	 server.sin_family = AF_INET;
	 server.sin_addr.s_addr = INADDR_ANY;
	 server.sin_port = htons(5000); //Will listen on port 5000
	 


	/* Call bind */
        

	 
	 if(bind(sock,(struct sockaddr*) &server,sizeof(server)))
	 {
           perror("Bind failed");
	   exit(1);
          
	 }



        /* Listen */


	//Listen for up to 5 connections
        listen(sock,5); 




        /* Accept */
	
	do {

          mysock = accept(sock, (struct sockaddr *) 0,0);
	  if(mysock == -1)
	  {
            perror("accept failed");
	    exit(1);
	  }
	  else
	  {
	    memset(buff,0,sizeof(buff));
            
	    rval = (recv(mysock,buff,sizeof(buff),0));
	    if(rval < 0)
	    {
                perror("Reading stream message error!!");
		exit(1);
	    }
	    
	   
	    else if(rval == 0) //Nothing left to print
	    {
               printf("Ending connection\n");
	       close(mysock);
	    }
           	    
	    else
	    {
	       printf("MSG: %s\n",buff);
               printf("Got the message (rval = %d)\n",rval);
	       close(mysock); 
               break;
	    }
	  
	  }


	} while(1);
	
	
	
	return 0;
}
