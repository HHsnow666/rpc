#include <iostream>
#include "mprpcapplication.hpp"
#include "friend.pb.h"

int main(int argc, char **argv)
{
    MprpcApplication::Init(argc, argv);

    xuan::FriendServiceRpc_Stub stub(new MprpcChannel());

    xuan::GetFriendListRequest request;
    request.set_userid(123456);

    xuan::GetFriendListResponse response;

    MprpcController controller;

    stub.GetFriendList(&controller, &request, &response, nullptr);

    if (controller.Failed())
    {
        std::cout << controller.ErrorText() << std::endl;
    }
    else
    {
        if (0 == response.result().errcode())
        {
            std::cout << "rpc GetFriendList response success : " << std::endl;
            for (int i = 0; i < response.friends_size(); ++i)
            {
                std::cout << "index: " << i + 1 << ", name: " << response.friends(i) << std::endl;
            }
        }
        else
        {
            std::cout << "rpc GetFriendList response error : " << response.result().errmsg() << std::endl;
        }
    }
}