#include <stdio.h> 

#include <string.h> 

#include <stdlib.h> 

#include <strings.h> 

#include <sys/types.h> 

#include <sys/socket.h> 

#include <arpa/inet.h> 

#include <netinet/in.h> 

int main()

{

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);//�����׽��� 

    if (sockfd < 0)

    {

        perror("socket");

        return -1;

    } //����ʧ�ܵĴ����� 

    printf("socket..............\n"); //�ɹ����ӡ��socket���������� 



    struct sockaddr_in myaddr; //�������ҵĵ�ַ���ṹ�� 

    memset(&myaddr, 0, sizeof(myaddr)); //���ڴ����㣨��������� 

    myaddr.sin_family = AF_INET; //ѡ��IPV4��ַ���� 

    myaddr.sin_port = htons(5555); //ѡ��˿ں� 

    myaddr.sin_addr.s_addr = inet_addr("192.168.85.145"); //ѡ��IP��ַ 



    if (0 > bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr)))//���׽��� 

    {

        perror("bind");

        return -1;

    }

    printf("bind..........\n");



    if (0 > listen(sockfd, 8))//����listen��ָ���˿ڽ��м��� 

    {

        perror("listen");

        return -1;

    }

    printf("listen............\n");



    int connfd = accept(sockfd, NULL, NULL);//ʹ��accept����Ϣ�����л�ȡ���� 

    if (connfd < 0)

    {

        perror("accept");

        return -1;

    }

    printf("accept..............\n");

    char buf[100];//����һ�����������洢���յ������� 

    int ret;

    while (1)

    {

        memset(buf, 0, sizeof(buf));

        ret = read(connfd, buf, sizeof(buf));

        if (0 > ret)

        {

            perror("read");

            break;

        }//ִ��whileѭ����ȡ���ݣ��� 

        else if (0 == ret)

        {

            printf("write close!\n");

            break;

        }

        printf("recv: ");

        fputs(buf, stdout);//��ӡ���յ������� 

    }

    close(sockfd);//�ر��׽��� 

    close(connfd);//�Ͽ����� 

    return 0;

}