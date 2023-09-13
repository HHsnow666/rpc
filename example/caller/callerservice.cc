#include <iostream>
#include "mprpcapplication.hpp"
#include "user.pb.h"

int main(int argc, char **argv)
{
    // 整个程序启动后，想要使用mprpc框架享受rpc服务调用，一定要先初始化框架
    MprpcApplication::Init(argc, argv);

    // 演示远程发布的rpc方法login
    xuan::UserServiceRpc_Stub stub(new MprpcChannel());
    // rpc方法的请求参数
    xuan::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");
    // rpc方法的响应消息
    xuan::LoginResponse response;
    // rpc方法的调用，同步rpc调用过程 --> callMethod
    stub.Login(nullptr, &request, &response, nullptr);

    // 一次rpc调用完成，读调用结果
    if (0 == response.result().errcode())
    {
        std::cout << "rpc login response success : " << response.success() << std::endl;
    }
    else
    {
        std::cout << "rpc login response error : " << response.result().errmsg() << std::endl;
    }

    // 远程调用发布的rpc方法Register
    xuan::RegisterRequest req;
    req.set_id(2000);
    req.set_name("mprpc");
    req.set_pwd("666666");

    xuan::RegisterResponse res;
    stub.Register(nullptr, &req, &res, nullptr);

    // 一次rpc调用完成，读调用结果
    if (0 == res.result().errcode())
    {
        std::cout << "rpc Register response success : " << res.success() << std::endl;
    }
    else
    {
        std::cout << "rpc Register response error : " << res.result().errmsg() << std::endl;
    }

    return 0;
}