#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "cppjieba/Jieba.hpp"

using std::string;
using std::vector;
using std::unordered_map;

// 注意, 在 .h 中千万不要 using namespace std !!!!

namespace searcher
{

///////////////////////////////////////////////////////
// 索引相关代码
///////////////////////////////////////////////////////
// 用于构建正排索引. 
// 正排本质上就是个 DocInfo 的数组. 
struct DocInfo
{
    int64_t docId;
    string title;
    string url;
    string content;
};

// 作为倒排索引的 value . 
// 倒排索引也是一个键值对结构, key 就是分词结果. value 就是 Weight 对象构成的数组. 
struct Weight
{
    int64_t docId;
    int weight;
    string word;
};

// 倒排拉链
typedef vector<Weight> InvertedList;

// 表示索引
// 提供的属性(成员变量)主要有两个: 正排索引 + 倒排索引
// 提供的方法(成员函数)主要有三个: 查正排, 查倒排, 构建索引
class Index
{
private:
    vector<DocInfo> forwardIndex;
    unordered_map<string, InvertedList> invertedIndex;

public:
    // 根据文档 id 获取正排索引内容
    const DocInfo* getDocInfo(int64_t docId);
    // 根据词, 获取到倒排拉链
    const InvertedList* getInverted(const string& key);
    // 构建索引
    // inputPath 就是指向 raw_input 这个文件
    bool build(const string& inputPath);

    Index();

    void cutWord(const string& word, vector<string>* tokens);

private:
    DocInfo* buildForward(const std::string& line);
    void buildInverted(const DocInfo& docInfo);

    cppjieba::Jieba jieba; 
};

///////////////////////////////////////////////////
// 搜索模块相关代码
/////////////////////////////////////////////////////
class Searcher
{
private:
    Index* index;

public:
    Searcher()
        : index(new Index())
    {}
    // 通过 inputPath 进行构造索引. inputPath 就指向 data/tmp/raw_input
    bool init(const std::string& inputPath);
    // 通过这个函数来进行整个搜索的处理过程. 
    bool search(const std::string query, std::string* result);

private:
    static string generateDesc(const string& content, const string& word);
};

}  // end searcher
