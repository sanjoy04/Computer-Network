#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 1024

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

int main()
{
	struct sockaddr_in s_addr,c_addr;    
    FILE* input_file;                     
	int s_fd,c_fd,s_len,c_len;



	if((s_fd=socket(AF_INET,SOCK_STREAM,0))==-1){
		printf("[-]Error in Socket\n");
        exit(0);
    }				
	printf("[+]Server Socket created\n");

	s_addr.sin_family = AF_INET;                                  
	s_addr.sin_port = 3452;                                       
	s_len=sizeof(s_addr); 

	if(bind(s_fd,(struct sockaddr*)& s_addr,s_len)==-1)	{
		printf("[-]Error in binding\n");
        exit(0);
    }	   
	printf("[+]Binding successfull\n");

	if(listen(s_fd,5)==-1){                                     
		printf("[-]Error in listen\n");
        exit(0);
    }
	printf("[+]Listening... \n");


    c_len=sizeof(c_addr);                                 	
	if((c_fd=accept(s_fd,(struct sockaddr*)&c_addr,&c_len))==-1){	
		printf("\n[-]Error in accepting\n");
        exit(0);
    }
	printf("[+]New Client Connected!!!: \n\n");

    char buff[100];
	while(1)
	{
            char choice
            ;
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
