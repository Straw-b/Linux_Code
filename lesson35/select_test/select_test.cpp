#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/*
* 1.���0���ļ�������(��׼����), �Ƿ��пɶ��¼�
*    ֻ��Ҫ�ڱ�׼���뵱��, ��������
*
*  2.����select �Ƿ���Լ�ض���ļ�������, 0���ļ�, socket�ļ�������
*
*  3.����select�Ƿ�ֻ���ؾ������ļ�������
*  ����0���ļ��������Ŀɶ��¼�, ʹ��select���з���, ����֮��, �����ж�select���صĿɶ��¼����ϵ����Ƿ��� socket�ļ�������
*/


int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0)
	{
		perror("socket");
		return 0;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(17890);
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");

	int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret < 0)
	{
		perror("bind");
		return 0;
	}

	listen(sockfd, 5);
	//int select(int nfds, fd_set *readfds, fd_set *writefds,
	//              fd_set *exceptfds, struct timeval *timeout);

	//1.����һ���ɶ��¼�����, ����λͼ�ķ�ʽ��ʹ��
	fd_set readfds;

	//2.���, ��ֹ����ı�����Ӧ���ڴ浱��������ֵ
	FD_ZERO(&readfds);

	//3.���0���ļ����������ɶ��¼����ϵ���
	FD_SET(0, &readfds);
	FD_SET(sockfd, &readfds);

	while (1)
	{
		//timeout ����
		struct timeval tv;
		tv.tv_sec = 5;
		tv.tv_usec = 0;

		fd_set tmp = readfds;
		ret = select(sockfd + 1, &tmp, NULL, NULL, &tv);
		printf("ret : %d\n", ret);
		if (ret < 0)
		{
			perror("select");
			return 0;
		}
		else if (ret == 0)
		{
			printf("select timeout\n");
		}

		if (FD_ISSET(0, &tmp))
		{
			char buf[1024] = { 0 };
			read(0, buf, sizeof(buf) - 1);
			printf("stdin : %s", buf);
		}
		else
		{
			printf("0 not in readfds\n");
		}

		if (FD_ISSET(sockfd, &tmp))
		{
			printf("sockfd in readfds\n");
		}
		else
		{
			printf("sockfd not in readfds\n");
		}
	}
	return 0;
}