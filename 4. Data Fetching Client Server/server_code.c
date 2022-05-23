#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>


struct StudentDetails
{
    int roll_no;
    char* name;
    char* address;
    float marks1;
    float marks2;
};


int main()
{
	struct sockaddr_in s_addr,c_addr;                            
	int s_fd,c_fd,s_len,c_len;

    struct StudentDetails studentdet[13];

    studentdet[0].roll_no = 1;
    studentdet[0].name = "Mainak Ghosh";
    studentdet[0].address = "Shyamnagar,South 24 Parganas";
    studentdet[0].marks1 = 89.0;
    studentdet[0].marks2 = 99.0;

    studentdet[1].roll_no = 2;
    studentdet[1].name = "Rishav Datta";
    studentdet[1].address = "Basirhat,North 24 Parganas";
    studentdet[1].marks1 = 81.0;
    studentdet[1].marks2 = 92.0;

    studentdet[2].roll_no = 3;
    studentdet[2].name = "Nabajit Sarmah";
    studentdet[2].address = "DRM,Jalpaiguri";
    studentdet[2].marks1 = 76.0;
    studentdet[2].marks2 = 87.0;

    studentdet[3].roll_no = 4;
    studentdet[3].name = "Dhruva Boro";
    studentdet[3].address = "DS Colony,Alipurduar";
    studentdet[3].marks1 = 87.0;
    studentdet[3].marks2 = 94.0;

    studentdet[4].roll_no = 5;
    studentdet[4].name = "Sanjoy Roy";
    studentdet[4].address = "Berubari,Jalpaiguri";
    studentdet[4].marks1 = 77.0;
    studentdet[4].marks2 = 77.0;

    studentdet[5].roll_no = 6;
    studentdet[5].name = "Somyajit Dhar";
    studentdet[5].address = "Salt lake,kolkata";
    studentdet[5].marks1 = 89.0;
    studentdet[5].marks2 = 91.0;

    studentdet[6].roll_no = 7;
    studentdet[6].name = "Akash Deb";
    studentdet[6].address = "Jadavpur,Kolkata";
    studentdet[6].marks1 = 81.0;
    studentdet[6].marks2 = 91.0;

    studentdet[7].roll_no = 8;
    studentdet[7].name = "Pryobrata Sarkar";
    studentdet[7].address = "Nabin Club,Alipurduar";
    studentdet[7].marks1 = 86.0;
    studentdet[7].marks2 = 90.0;

    studentdet[8].roll_no = 9;
    studentdet[8].name = "Anuska Sarkar";
    studentdet[8].address = "Hakim Para,Jalpaiguri";
    studentdet[8].marks1 = 90.0;
    studentdet[8].marks2 = 90.0;

    studentdet[9].roll_no = 10;
    studentdet[9].name = "Ujjan Sarkar";
    studentdet[9].address = "Hakim Para,Darjeeling";
    studentdet[9].marks1 = 89.0;
    studentdet[9].marks2 = 92.0;




	if((s_fd=socket(AF_INET,SOCK_STREAM,0))==-1){				
		printf("[-]Error in Socket\n");
        exit(0);
    }
	printf("[+]Server Socket created\n");

	s_addr.sin_family = AF_INET;                                  
	s_addr.sin_port = 3452;                                       
	s_len=sizeof(s_addr); 

	if(bind(s_fd,(struct sockaddr*)& s_addr,s_len)==-1){		   
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
        int roll; 

        read(c_fd,buff,100);
        roll = atoi(buff);
        for(int i = 0; i < 10; i++){
            if(studentdet[i].roll_no == roll){
                snprintf(buff, 100, "\nRoll No: %d\nName: %s\nAddress: %s\nMarks 1: %2.f\nMarks 2: %2.f\n"
                ,studentdet[i].roll_no, studentdet[i].name,studentdet[i].address, 
                studentdet[i].marks1, studentdet[i].marks2);
                write(c_fd,buff,100); 
                printf("[+]Detail found and sent to client successfully!");
                break;

            }
            else if(studentdet[i].roll_no != roll && i == 9){
                printf("[-]Details not found.");
                write(c_fd,"\n[-]Details not found.\n",100);
            }

        }								            
	}
    close(c_fd);
	return 0;
}
