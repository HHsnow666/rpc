#include "logger.hpp"
#include <ctime>
#include <iostream>

// 获取日志的单例
Logger &Logger::GetInstance()
{
    static Logger logger;
    return logger;
}

Logger::Logger()
{
    // 启动专门的写日志线程
    std::thread writeLogTask([&]()
                             {
        for(;;)
        {
            // 获取当天的日期，然后取日志信息，写入对应的日志文件中
            time_t now=time(nullptr);
            tm *nowtm=localtime(&now);

            char file_name[128];
            sprintf(file_name,"%d-%d-%d-log.txt",nowtm->tm_year+1900,nowtm->tm_mon+1,nowtm->tm_mday);

            FILE *pf=fopen64(file_name,"a+");
            if(pf==nullptr)
            {
                std::cout<<"logger file: "<<file_name<<" open error!"<<std::endl;
                exit(EXIT_FAILURE);
            }

            std::string msg = m_lckQue.Pop();

            char time_buf[128]={0};
            sprintf(time_buf,"%d:%d:%d --> [%s] ",
                                nowtm->tm_hour,
                                nowtm->tm_min,
                                nowtm->tm_wday,
                                (m_loglevel == INFO ? "info" : "error"));
            msg.insert(0,time_buf);
            msg.append("\n");
            fputs(msg.c_str(),pf);
            fclose(pf);
        } });
    writeLogTask.detach(); // 设置分离线程
}

// 设置日志级别
void Logger::SetLogLevel(LogLevel level)
{
    this->m_loglevel = level;
}
// 写日志,把日志写入缓冲区中
void Logger::Log(std::string msg)
{
    m_lckQue.Push(msg);
}