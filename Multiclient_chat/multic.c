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
	int c_sock;
	char buf1[100]="\0",buf2[100],msg[100],name[100];
	c_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(9009);
	client.sin_addr.s_addr = inet_addr("35.246.29.33");
	if(connect(c_sock, (struct sockaddr*)&client, sizeof(client))==-1)
	{
		printf("Connection error\n");
		exit(1);
	}
	recv(c_sock,msg,sizeof(msg),0);
	printf("%s ",msg);
	gets(name);
        send(c_sock,name,sizeof(name),0);
	while(1)
	{       
		printf(">>>Enter client to server : %s",buf1);
		fgets(buf1,100,stdin);
		send(c_sock, buf1, sizeof(buf1), 0);
		if(strncmp(buf1, "end", 3)==0)
			exit(0);
                bzero(buf1, sizeof(buf1));
		recv(c_sock, buf2, sizeof(buf2), 0);
		printf("Server message is : %s", buf2);
	}
	close(c_sock);
	return 0;	
}
