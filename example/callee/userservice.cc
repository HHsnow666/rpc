#include <iostream>
#include <string>

#include "user.pb.h"
#include "mprpcapplication.hpp"
#include "rpcprovider.hpp"

/**
 * UserService原来是一个本地服务，提供了两个进程内的本地方法
 */

class UserService : public xuan::UserServiceRpc
{
public:
    bool Login(std::string name, std::string pwd)
    {
        std::cout << "doing login service:login" << std::endl;
        std::cout << "name: " << name << ", pwd= " << pwd << std::endl;
        return true;
    }

    bool Register(uint32_t id, std::string name, std::string pwd)
    {
        std::cout << "doing local service:Register" << std::endl;
        std::cout << "id: " << id << "name: " << name << ", pwd= " << pwd << std::endl;
        return true;
    }

    /*
     * 重写虚函数，下面这些方法都是框架直接调用的
     1. caller --> Login(LoginRequest) --> muduo --> callee
     2. callee --> Login(LoginRequest) --> 交给下面重写的方法
     */
    void Login(::google::protobuf::RpcController *controller,
               const ::xuan::LoginRequest *request,
               ::xuan::LoginResponse *response,
               ::google::protobuf::Closure *done)
    {
        // 框架给业务上报了请求参数LoginRequest，业务获取响应数据做本地业务
        std::string name = request->name();
        std::string pwd = request->pwd();

        // 本地业务
        bool login_result = Login(name, pwd);

        // 把响应写入
        xuan::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);

        // 执行回调函数
        done->Run();
    }

    void Register(::google::protobuf::RpcController *controller,
                  const ::xuan::RegisterRequest *request,
                  ::xuan::RegisterResponse *response,
                  ::google::protobuf::Closure *done)
    {
        uint32_t id = request->id();
        std::string name = request->name();
        std::string pwd=request->pwd();

        bool ret=Register(id,name,pwd);

        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        response->set_success(ret);

        done->Run();
    }
};

int main(int argc, char **argv)
{
    // 调用框架的初始化操作
    MprpcApplication::Init(argc, argv);

    // provider是一个rpc网络服务对象，把UserService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new UserService());

    // 启动一个rpc服务发布节点
    provider.Run();
    return 0;
}