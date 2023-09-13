#include <iostream>
#include <string>
#include <vector>

#include "friend.pb.h"
#include "mprpcapplication.hpp"
#include "rpcprovider.hpp"
#include "logger.hpp"

class FriendService : public xuan::FriendServiceRpc
{
public:
    std::vector<std::string> GetFriendList(uint32_t userid)
    {
        std::cout << "doing FriendService service:GetFriendList" << std::endl;
        std::vector<std::string> vec;
        vec.emplace_back("gao yang");
        vec.emplace_back("liu hong");
        vec.emplace_back("wang shuo");
        return vec;
    }

    void GetFriendList(::google::protobuf::RpcController *controller,
                       const ::xuan::GetFriendListRequest *request,
                       ::xuan::GetFriendListResponse *response,
                       ::google::protobuf::Closure *done)
    {
        uint32_t userid = request->userid();

        std::vector<std::string> friendlist = GetFriendList(userid);
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        for (auto &name : friendlist)
        {
            std::string *p = response->add_friends();
            *p = name;
        }
        done->Run();
    }
};


int main(int argc, char **argv)
{
    LOG_INFO("first log message!");
    LOG_ERR("%s : %s : %d",__FILE__,__FUNCTION__,__LINE__);

    // 调用框架的初始化操作
    MprpcApplication::Init(argc, argv);

    // provider是一个rpc网络服务对象，把UserService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new FriendService());

    // 启动一个rpc服务发布节点
    provider.Run();
    return 0;
}
