#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>

int main()
{
        struct sockaddr_in c_addr;                                 
        int c_fd,c_len;
	    char buff[100];   

        if((c_fd=socket(AF_INET,SOCK_STREAM,0))==-1){			 
        	printf("[-]Error in Socket\n");
            exit(0);
        }
        printf("[+]Client Socket created\n");

        c_addr.sin_family=AF_INET;                                    
        c_addr.sin_addr.s_addr=INADDR_ANY;                       
        c_addr.sin_port=3452;                                     
        c_len=sizeof(c_addr); 

        if(connect(c_fd,(struct sockaddr*)& c_addr,c_len)==-1) { 
        	printf("[-]Error in Connect\n");
            exit(0);
        }
        printf("[+]Connected to the Server: \n\n");

        while(1)
        {
            printf("\nEnter Roll No of Student: \n");
            fgets(buff,sizeof(buff),stdin);
              
            if (strcmp(buff, "Exit\n") == 0){
                printf("[-]Disconneted from Server");
                write(c_fd,"Disconnected\n",100);
                break;
            }
            else{
                write(c_fd,buff,100);
            }
            read(c_fd,buff,100);									  
            printf("%s",buff);
        }       
        close(c_fd);                                              
        return 0;
}

