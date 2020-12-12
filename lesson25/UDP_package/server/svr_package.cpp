#include "../udp.hpp"

#define CHECK_ERT(p) if(p < 0){return -1;}

int main()
{
    UdpApi ua; // 服务端的ua
    CHECK_ERT(ua.CreateSocket());
    CHECK_ERT(ua.Bind("0.0.0.0", 19999));

    while(1)
    {
        struct sockaddr_in cli_addr;                                         
        socklen_t cli_len = sizeof(cli_addr);  
        
        std::string data; 
        ua.RecvData(&data, &cli_addr, &cli_len);
        printf("client say: %s\n", data.c_str());

        data.clear();

        printf("please enter respond: ");
        fflush(stdout);
        std::cin >> data;
        ua.SendData(data, &cli_addr, cli_len);
    }
    ua.Close();
    return 0;
}
