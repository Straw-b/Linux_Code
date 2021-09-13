#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "my_select.hpp"

int main()
{
	//1.创建套接字, 绑定地址信息, 监听
	int listen_scokfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_scokfd < 0)
	{
		perror("socket");
		return 0;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(18989);
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");

	int ret = bind(listen_scokfd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret < 0)
	{
		perror("bind");
		return 0;
	}

	ret = listen(listen_scokfd, 5);
	if (ret < 0)
	{
		perror("listen");
		return 0;
	}

	MySelect ms;
	ms.Addfd(listen_scokfd);

	while (1)
	{
		std::vector<int> vec;
		vec.clear();
		ret = ms.Select(&vec, NULL);
		if (ret <= 0)
		{
			continue;
		}

		//监控的文件描述符有对应的事件发生
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (vec[i] == listen_scokfd)
			{
				//意味着侦听套接字有事件产生
				//接收新连接
				int newfd = accept(listen_scokfd, NULL, NULL);
				if (newfd < 0)
				{
					perror("accept");
					continue;
				}

				//接收成功, 将新创建出来的文件描述符添加到select集合当中去
				ms.Addfd(newfd);
			}
			else
			{
				//意味着新连接创建出来的套接字有数据到来了, 需要接收数据了
				printf("newfd recv data...%d\n", vec[i]);
				char buf[1024] = { 0 };
				ssize_t recv_size = recv(vec[i], buf, sizeof(buf), 0);
				if (recv_size < 0)
				{
					perror("recv");
					continue;
				}
				else if (recv_size == 0)
				{
					printf("peer shutdown conect\n");
					ms.Deletefd(vec[i]);
					close(vec[i]);
					continue;
				}

				//说明接收成功
				printf("buf is %s\n", buf);
			}
		}
	}
	return 0;
}