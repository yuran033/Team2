#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define	MYPORT 5555
int main() {
	int sock = 0;
	struct sockaddr_in my_addr, cl_addr;
	int addrlen = sizeof(cl_addr);
	char buf[64] = { 0 };
	char msg[64] = { 0 };


	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) {
		printf("socket failed!\n");
		return -1;
	}


	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (-1 == bind(sock, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)))
	{
		printf("bind failed!\n");
		return -1;
	}


	while (1)
	{
		memset(buf, 0, sizeof(buf));
		recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&cl_addr, &addrlen);
		printf("from client: %s\n", buf);

		memset(msg, 0, sizeof(msg));
		printf("please input:\n");
		scanf("%s", msg);
		addrlen = sizeof(struct sockaddr);
		sendto(sock, msg, strlen(msg), 0, (struct sockaddr*)&cl_addr, addrlen);
	}
	return 0;
}