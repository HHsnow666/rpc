#include "test.pb.h"
#include <iostream>
#include <string>

using namespace fixbuf;


int main()
{
    LoginResponse rsp;
    ResultCode *rc=rsp.mutable_result();
    rc->set_errcode(0);
    rc->set_errmsg("login failed");
    return 0;
}

// int main()
// {
//     // 封装了login请求对象的数据
//     LoginRequest req;
//     req.set_name("zhang san");
//     req.set_pwd("123456");

//     // 对象数据序列化
//     std::string send_str;
//     if (req.SerializeToString(&send_str))
//     {
//         std::cout << send_str.c_str() << std::endl;
//     }

//     // 对象反序列化
//     LoginRequest reqB;
//     if (reqB.ParseFromString(send_str))
//     {
//         std::cout << reqB.name() << std::endl;
//         std::cout << reqB.pwd() << std::endl;
//     }

//     return 0;
// }