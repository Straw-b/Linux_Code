#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/*
* 1.监控0号文件描述符(标准输入), 是否有可读事件
*    只需要在标准输入当中, 输入内容
*
*  2.测试select 是否可以监控多个文件描述符, 0号文件, socket文件描述符
*
*  3.测试select是否只返回就绪的文件描述符
*  触发0号文件描述符的可读事件, 使得select进行返回, 返回之后, 我们判断select返回的可读事件集合当中是否有 socket文件描述符
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

	//1.创建一个可读事件集合, 按照位图的方式来使用
	fd_set readfds;

	//2.清空, 防止申请的变量对应的内存当中有其他值
	FD_ZERO(&readfds);

	//3.添加0号文件描述符到可读事件集合当中
	FD_SET(0, &readfds);
	FD_SET(sockfd, &readfds);

	while (1)
	{
		//timeout 参数
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