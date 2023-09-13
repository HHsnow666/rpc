#ifndef RPCPROVIDER_H
#define RPCPROVIDER_H

#include <google/protobuf/service.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/base/Timestamp.h>
#include <google/protobuf/descriptor.h>
#include <string>
#include <functional>
#include <unordered_map>

// 框架提供的专门服务发布rpc服务的网络对象类
class RpcProvider
{
public:
    // 这里是框架提供给外部使用的，可以发布rpc方法的函数接口
    void NotifyService(::google::protobuf::Service *service);

    // 启动rpc服务节点,开始提供rpc远程网络服务
    void Run();

private:
    // 组合EventLoop
    muduo::net::EventLoop m_eventloop;

    // service服务类型消息
    struct ServiceInfo
    {
        google::protobuf::Service *m_service; // 保存服务对象
        std::unordered_map<std::string,
                           const google::protobuf::MethodDescriptor *>
            m_methodMap; // 描述服务方法
    };

    // 存储注册成功的服务对象及其服务方法的所有信息
    std::unordered_map<std::string, ServiceInfo> m_serviceInfoMap;

    // 新的socket连接
    void onConnection(const muduo::net::TcpConnectionPtr &conn);

    // 已建立连接用户的读写事件回调
    void onMessage(const muduo::net::TcpConnectionPtr &conn,
                   muduo::net::Buffer *buffer,
                   muduo::Timestamp time);

    // Closure的回调操作，用于序列化rpc的响应和网络发送
    void SendRpcResponse(const muduo::net::TcpConnectionPtr &,
                         google::protobuf::Message *);
};

#endif // !RPCPROVIDER_H