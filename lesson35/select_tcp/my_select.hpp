#pragma once
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <vector>

class MySelect
{
public:
	MySelect()
	{
		FD_ZERO(&readfds_);

		nfds_ = -1;
	}

	~MySelect()
	{

	}

	void Addfd(int fd)
	{
		//1.将文件描述符添加到集合当中去
		FD_SET(fd, &readfds_);

		if (fd > nfds_)
		{
			nfds_ = fd;
		}
	}

	//将文件描述符从集合当中去除掉
	void Deletefd(int fd)
	{
		//8
		FD_CLR(fd, &readfds_);

		//2.更新最大文件描述符数值
		// 1, 2, ,3, 4, 5 ,6, 7, 8
		for (int i = nfds_; i >= 0; i--)
		{
			//只要判断出来文件描述符在readfds当中, 我们就找到了目前最大的文件描述符, 然后在更新
			if (IsInSet(i))
			{
				nfds_ = i;
				//一定要break
				break;
			}
		}
	}

	//判断文件描述符是否在集合当中
	bool IsInSet(int fd)
	{
		if (FD_ISSET(fd, &readfds_))
		{
			return true;
		}
		return false;
	}

	//监控接口
	//timeout : 设置select是阻塞还是非阻塞还是带有超时时间
	//默认是阻塞的
	//vec是一个出参, 返回给调用者, 就绪的文件描述符
	int Select(std::vector<int>* vec, struct timeval* timeout = NULL)
	{
		printf("begin select...\n");
		fd_set tmp = readfds_;
		int ret = select(nfds_ + 1, &tmp, NULL, NULL, 0);
		if (ret < 0)
		{
			perror("select");
			return ret;
		}
		else if (ret == 0)
		{
			printf("select timeout...\n");
		}

		//需要告诉调用者哪些文件描述符就绪了
		//fd_set tmp
		//遍历的范围到底是[0, ret], 还是[0, nfds_]
		// 1 2 3 4 5 6 7 8 9 10
		// 0 0 0 0 0 0 1 0 1 0  ret = 1
		for (int fd = 0; fd <= nfds_; fd++)
		{
			printf("fd is %d, nfds = %d\n", fd, nfds_);
			if (FD_ISSET(fd, &tmp))
			{
				printf("insert fd is %d\n", fd);
				vec->push_back(fd);
			}
		}

		return ret;
	}
private:
	fd_set readfds_;

	int nfds_;
};