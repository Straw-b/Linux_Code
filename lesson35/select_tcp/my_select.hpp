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
		//1.���ļ���������ӵ����ϵ���ȥ
		FD_SET(fd, &readfds_);

		if (fd > nfds_)
		{
			nfds_ = fd;
		}
	}

	//���ļ��������Ӽ��ϵ���ȥ����
	void Deletefd(int fd)
	{
		//8
		FD_CLR(fd, &readfds_);

		//2.��������ļ���������ֵ
		// 1, 2, ,3, 4, 5 ,6, 7, 8
		for (int i = nfds_; i >= 0; i--)
		{
			//ֻҪ�жϳ����ļ���������readfds����, ���Ǿ��ҵ���Ŀǰ�����ļ�������, Ȼ���ڸ���
			if (IsInSet(i))
			{
				nfds_ = i;
				//һ��Ҫbreak
				break;
			}
		}
	}

	//�ж��ļ��������Ƿ��ڼ��ϵ���
	bool IsInSet(int fd)
	{
		if (FD_ISSET(fd, &readfds_))
		{
			return true;
		}
		return false;
	}

	//��ؽӿ�
	//timeout : ����select���������Ƿ��������Ǵ��г�ʱʱ��
	//Ĭ����������
	//vec��һ������, ���ظ�������, �������ļ�������
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

		//��Ҫ���ߵ�������Щ�ļ�������������
		//fd_set tmp
		//�����ķ�Χ������[0, ret], ����[0, nfds_]
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