#pragma once
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>


class SelectSvr
{
    public:
        SelectSvr()
        {
            maxfd_ = -1;                                
        }

        ~SelectSvr()
        {

        }

        //监控的接口
        int Select()
        {
            //select(nfds, readfds);
        }

        //添加
        void AddFd(int fd)
        {
            //FD_SET接口
            FD_SET(fd, &readfds_);
            if(fd > maxfd_)
            {
                maxfd_ = fd;
            }
        }

        //删除
        void DeleteFD()
        {
            //FD_CLR接口
            FD_CLR(fd, &readfds_);
            //0 1 2 3 4 5 6 7 8
            for(int i = maxfd_; i >=0; i--)
            {
                if(FD_ISSET(i, &readfds_))
                {
                    maxfd_ = i;
                    break;
                }
            }
        }

         void JudgeFd()
         {
              //FD_ISSET
         }


    private:
        //当前监控的文件描述符当中的最大值
        int maxfd_;
        //可读事件集合
        fd_set readfds_;
};
