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
	struct sockaddr_in s_addr,c_addr;    
                          
	int s_fd,c_fd,s_len,c_len;



	if((s_fd=socket(AF_INET,SOCK_STREAM,0))==-1)				
		printf("[-]Error in Socket\n");
	printf("[+]Server Socket created\n");
	

	s_addr.sin_family = AF_INET;                                  
	s_addr.sin_port = 3452;                                       
	s_len=sizeof(s_addr); 

	if(bind(s_fd,(struct sockaddr*)& s_addr,s_len)==-1)		   
		printf("[-]Error in binding\n");
	printf("[+]Binding successfull\n");

	if(listen(s_fd,5)==-1)                                     
		printf("[-]Error in listen\n");
	printf("[+]Listening... \n");



	int nums[2], n = 0;

	c_len=sizeof(c_addr);                                 	
	if((c_fd=accept(s_fd,(struct sockaddr*)&c_addr,&c_len))==-1)	
		printf("\n[-]Error in accepting\n");
	printf("[+]New Client Connected!!!: \n\n");


	while(n < 2)
	{   
		
    	char buff[100];
        read(c_fd,buff,100);	

        printf("From Client Number %d is %s",n+1,buff);
		nums[n++] = atoi(buff); 

	}

	printf("\nAddition of %d and %d is %d\n",nums[0],nums[1],nums[0]+nums[1]);
	printf("Subtaction of %d and %d is %d\n",nums[0],nums[1],nums[0]-nums[1]);
	printf("Multiplication of %d and %d is %d\n",nums[0],nums[1],nums[0]*nums[1]);

	close(c_fd);
	return 0;
}


