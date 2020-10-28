#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>
int main()
{
	int s_sock, c_client, flag=0,clientcount=0,id=0,complete;
	char buf1[100],buf2[100]="\0",buf3[100]="bye",msg[100]="ENTER YOUR NAME :",name[100];
	pid_t childpid; 
	socklen_t addr_size;
	s_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server, other;
	memset(&other, 0, sizeof(other));
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(9009);
	server.sin_addr.s_addr = INADDR_ANY;
	if(bind(s_sock, (struct sockaddr*)&server, sizeof(server))==-1)
	{
		printf("Server is busy....\n");
		exit(1);
	}
	listen(s_sock, 10);
	addr_size = sizeof(other);
	while(1)
	{      
		c_client = accept(s_sock, (struct sockaddr*)&other, &addr_size);
		clientcount++;
		id=clientcount;
		
		send(c_client,msg,sizeof(msg),0);
		recv(c_client,name,sizeof(name),0);
		printf("\nConnection %d accepted from : %s with port %d\n\n",id,inet_ntoa(other.sin_addr), ntohs(other.sin_port));
		if(c_client==-1)
			exit(1);
		if((childpid=fork())==0)
		{
			close(s_sock);
			while(1)
			{      
				recv(c_client, buf1, sizeof(buf1), 0);
				if(buf1!="\0")
				{
					if(strncmp(buf1, "end", 3)==0)
					{
						flag = 1;
                                                //send(c_client, buf3, sizeof(buf3),0);
						printf("Disconnected from connection%d : %s with port %d\n\n",id,inet_ntoa(other.sin_addr), ntohs(other.sin_port));
						break;
					}
					else
					{       
						printf("%s : %s",name,buf1);
						printf(">>>Server to %s : %s",name,buf2);
						fgets(buf2,100,stdin);
						send(c_client, buf2, sizeof(buf2),0);
						bzero(buf2, sizeof(buf2));
					}
				}
			}
			if(flag == 1)
				break;
		}
	}
close(s_sock);
return 0;
}
