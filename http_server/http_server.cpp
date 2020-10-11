#include <string>
#include <vector>
#include <iostream>
#include "cpp-httplib/httplib.h"
#include "../searcher/searcher.h"

int main()
{
    using namespace std;
    using namespace httplib;

    // 1. 初始化搜索模块
    searcher::Searcher searcher;
    bool ret = searcher.init("../data/tmp/raw_input");
    if (!ret)
    {
        cout << "searcher 初始化失败" << endl;
        return 1;
    }

    // 2. 初始化服务器模块
    //    约定客户端通过 query 这样的参数来传递查询词. 
    //    浏览器进行搜索使用的 url 形如:
    //    http://47.98.116.42:10000/searcher?query=filesystem
    Server server;
    server.Get("/searcher", [&searcher](const Request& req, Response& resp) {
            // 1. 获取到 query 参数
            bool ret = req.has_param("query");
            if (!ret)
            {
                resp.set_content("query param miss!", "text/plan");
                return;
            }
            string query = req.get_param_value("query");

            // 2. 使用 searcher 对象来进行搜索. 
            string result;
            searcher.search(query, &result);
            resp.set_content(result, "application/json");
            });

    server.set_base_dir("./front_end");
    server.listen("0.0.0.0", 8888);

    return 0;
}
