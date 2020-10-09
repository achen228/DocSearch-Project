#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>

namespace common
{
    class Util
    {
    public:
        static bool read(const std::string& input, std::string* output)
        {
            // 根据 input 字符串对应的路径, 读取文件内容, 并放到 output 中即可
            // 按二进制方式打开. 以字节为单位进行读写了. 默认是以字符为单位进行读写. 
            std::ifstream file(input.c_str(), std::ios::binary);
            if (!file.is_open())
            {
                return false;
            }
            // 根据文件长度, 来调整 output 的空间大小, 然后直接把数据读取进去即可. 
            file.seekg(0, file.end);
            int length = file.tellg();
            file.seekg(0, file.beg);
            // 根据文件大小, 设置 output 的空间. 
            output->resize(length);
            file.read(const_cast<char*>(output->data()), length);
            file.close();
            return true;
        }

        // 可以直接调用 boost 的 split 来实现
        static void split(const std::string& input, const std::string& delimiter, std::vector<std::string>* output)
        {
            boost::split(*output, input, boost::is_any_of(delimiter), boost::token_compress_off);
        }
    };
}  // end common
