#include "../udp.hpp"
#include <stdlib.h>

#define CHECK_ERT(p) if(p < 0){return -1;}

int main(int argc, char* argv[])
{
    // ./udp_cli_package -ip [svr_ip] -port [svr_port]
    if(argc != 5)
    {
        printf("./udp_cli_package -ip [svr_ip] -port [svr_port]\n");
        return -1;
    }

    std::string svr_ip;
    uint16_t svr_port;
    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-ip") == 0)
        {
            svr_ip = argv[i + 1];
        }
        else if(strcmp(argv[i], "-port") == 0)
        {
            svr_port = atoi(argv[i + 1]); //char* -> int
        }
    }

    UdpApi ua; // 客户端的ua
    CHECK_ERT(ua.CreateSocket());

    while(1)
    {
        struct sockaddr_in svr_addr;
        svr_addr.sin_family = AF_INET;
        svr_addr.sin_port = htons(svr_port);
        svr_addr.sin_addr.s_addr = inet_addr(svr_ip.c_str());

        std::string data;
        printf("please input message: ");
        fflush(stdout);
        std::cin >> data;
        ua.SendData(data, &svr_addr, sizeof(svr_addr));

        data.clear();

        ua.RecvData(&data, NULL, NULL);
        printf("svr say:%s\n", data.c_str());
    }

    ua.Close();
    return 0;
}
