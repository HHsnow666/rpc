#ifndef MPRPCCONFIG_H
#define MPRPCCONFIG_H

#include <string>
#include <unordered_map>

// 框架读取配置文件类
/**
    std::string _rpcserver_ip;
    uint8_t _rpcserver_port;
    std::string _zookeeper_ip;
    uint8_t _zookeeper_port;
*/
class MprpcConfig
{
public:
    // 负责加载配置文件和解析配置文件
    void LoadConfigFile(const char *config_file);

    // 查询配置项信息
    std::string Load(const std::string &key);
private:
    std::unordered_map<std::string,std::string> m_configMap;

    // 去掉字符串前后的空格
    void Trim(std::string &src_buf);
};
#endif // !MPRPCCONFIG_H