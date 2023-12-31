#include "mprpcapplication.hpp"
#include <iostream>
#include "unistd.h"
#include <string>

MprpcConfig MprpcApplication::m_config;

void ShowArgHelp()
{
    std::cout << "format : command -i <configfile>" << std::endl;
}

void MprpcApplication::Init(int argc, char **argv)
{
    if (argc < 2)
    {
        ShowArgHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;
    while ((c = getopt(argc, argv, "i:")) != -1)
    {
        switch (c)
        {
        case 'i':
        {
            config_file = optarg;
            break;
        }
        case '?':
        {
            ShowArgHelp();
            exit(EXIT_FAILURE);
        }
        case ':':
        {
            ShowArgHelp();
            exit(EXIT_FAILURE);
        }
        default:
            break;
        }
    }

    // 开始加载配置文件
    m_config.LoadConfigFile(config_file.c_str());

    // std::cout << "rpcserver_ip: " << m_config.Load("rpcserver_ip") << std::endl;
    // std::cout << "rpcserver_port: " << m_config.Load("rpcserver_port") << std::endl;
    // std::cout << "zookeeper_ip: " << m_config.Load("zookeeper_ip") << std::endl;
    // std::cout << "zookeeper_port: " << m_config.Load("zookeeper_port") << std::endl;
}

MprpcApplication &MprpcApplication::GetInstance()
{
    static MprpcApplication app;
    return app;
}


MprpcConfig& MprpcApplication::GetConfig()
{
    return m_config;
}