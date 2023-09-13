#ifndef ZOOKEEPER_H
#define ZOOKEEPER_H

#include <semaphore.h>
#include <zookeeper/zookeeper.h>
#include <string>

// 封装的zk客户端类
class ZkClient
{
public:
    ZkClient();
    ~ZkClient();
    // zkclient启动连接
    void Start();
    // zkserver上根据指定的path创建znode节点
    void create(const char *path, const char *data, int datalen, int state = 0);
    // 传入参数，根据路径获取值
    std::string GetData(const char *path);

private:
    // zk客户端句柄
    zhandle_t *m_zhandle;
};

#endif // !ZOOKEEPER_H