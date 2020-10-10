///////////////////////////////////////////////////////
// 通过这个文件来进行索引的简单测试. 
///////////////////////////////////////////////////////

#include <iostream>
#include "../searcher/searcher.h"

int main()
{
    // std 的作用范围越小越好
    using namespace std;

    searcher::Index index; 
    bool ret = index.build("../data/tmp/raw_input");
    if (!ret)
    {
        cout << "build failed" << endl;
        return 1;
    }
    // 调用 index 中的查正排和查倒排的方法. 
    auto* invertedList = index.getInverted("filesystem");
    for (const auto& weight : *invertedList)
    {
        cout << "docId: " << weight.docId << "; weight: " << weight.weight << "; word: " << weight.word << endl;
        // 根据 docId 再查查正排, 看看查到的结果对不对. 
        const searcher::DocInfo* docInfo = index.getDocInfo(weight.docId);
        cout << "docId: " << docInfo->docId << "; title: " << docInfo->title 
            << " url: " << docInfo->url << endl;
        cout << docInfo->content << endl;
        cout << "=========================================" << endl;
    }
    return 0;
}
