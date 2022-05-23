#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 1024

void send_file(FILE* fp, int socket_fd){
    int n = 0;
    char data[SIZE] = {0};

    char current;
    do{
        current = fgetc(fp);
        if (current != EOF)
            data[n++] = current;
    }while(current !=  EOF);

    if(send(socket_fd,data,SIZE,0) == -1){
        printf("[-]Error sending file");
    }
    bzero(data, SIZE);
    printf("[+]File send successfully");
    exit(0);

    
}

void write_file(int socket_fd){

    int n;
    FILE* output_file;
    char *filename = "output_file.txt";
    char buffer[SIZE];

    output_file = fopen(filename,"w");
    if(output_file == NULL){
        printf("[-]Error opening file.\n");
    }

    while(1){
        n = recv(socket_fd,buffer,SIZE,0);
        if (n <= 0){
            break;
            return;
        }

        fprintf(output_file, "%s", buffer);
        bzero(buffer, SIZE);
    }

}

int main()
{
        struct sockaddr_in c_addr;                                 
        int c_fd,c_len;
	    char buff[100];  
        FILE* input_file; 

        if((c_fd=socket(AF_INET,SOCK_STREAM,0))==-1){
        	printf("[-]Error in Socket\n");
            exit(0);
        }			       
        printf("[+]Client Socket created\n");

        c_addr.sin_family=AF_INET;                                    
        c_addr.sin_addr.s_addr=INADDR_ANY;                       
        c_addr.sin_port=3452;                                     
        c_len=sizeof(c_addr); 

        if(connect(c_fd,(struct sockaddr*)& c_addr,c_len)==-1){
        	printf("[-]Error in Connect\n");
            exit(0);
        }
        printf("[+]Connected to the Server: \n\n");

        while(1)
        {
            char choice;
            printf("Do you want to send file? [y/n] ");
            scanf("%c",&choice);



            if(choice == 'y'){

                char filename[20];
                printf("Please Enter file name: ");
                scanf("%s",filename);
                input_file = fopen(filename,"r");

                if(input_file == NULL){
                  printf("[-]Error opening file.\n");
                break;
                }

                send_file(input_file, c_fd);

            }

            if(choice == 'n'){
                printf("\n[+]Recieving file Please Wait...\n");
                write_file(c_fd);  
                printf("[+]File recieved successfully!!!.");
                exit(0);
            }
        }       
        close(c_fd);                                              
        return 0;
}

