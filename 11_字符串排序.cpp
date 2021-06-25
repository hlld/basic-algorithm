#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

// 题目描述：给定一个数组由一些非负整数组成，现需要将他们进行排列并拼接
// 使得最后的结果最大，返回值需要是string类型 否则可能会溢出

using namespace std;

// 比较小于则结果为升序排列
// 比较大于则结果为降序排列
bool cmp(string a, string b) {
    return a + b > b + a;
}

int main(int argc, char* argv[])
{
    vector<int> vc{1, 30};
    vector<string> vs;
    for (int k = 0; k < vc.size(); k++) {
        vs.push_back(to_string(vc[k]));
    }
    // 字符串比较是从左到右进行字符大小比较
    // 当相等则比较下一字符，不等则停止比较
    sort(vs.begin(), vs.end(), cmp);
    string result = "";
    // 当输入存在全为多个0的情况
    if (vs[0] == "0") {
        result = vs[0];
    }
    else {
        // 按照降序排序字符串逐个拼接
        for(int k = 0; k < vs.size(); k++) {
            result += vs[k];
        }
    }
    printf("%s\n", result.c_str());
    return 0;
}
