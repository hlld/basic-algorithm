#include <cstdio>
#include <string>
#include <unordered_map>

using namespace std;

// 给出两个字符串 SS 和 TT，要求在O(n)O(n)的时间复杂度内在S中找出
//     最短的包含T中所有字符的子串
// 例如：S ="XDOYEZODEYXNZ" T ="XYZ"
// 找出的最短子串为"YXNZ"
// 注意：如果S中没有包含T中所有字符的子串，返回空字符串""
//      满足条件的子串可能有很多，但题目保证满足条件的最短子串唯一

string min_window(string S, string T) {
    if (S.size() < 1 || T.size() < 1 || S.size() < T.size()) {
        return string("");
    }
    // Map值默认初始化0,假定T中无重复字符
    unordered_map<char, int> window, target;
    for (auto t : T) {
        ++target[t];
    }
    // low,high分别记录当前窗口的左右边界
    // start,min_len分别记录最小窗口的左边界与长度
    // count记录当前窗口是否包含目标字串
    int low = 0, high = 0, start = 0, min_len = INT32_MAX, count = 0;
    while (high < S.size()) {
        if (target.count(S[high])) {
            ++window[S[high]];
            // 窗口中目标字符可以有多个,仅当两者计数相等时更新包含状态
            if (window[S[high]] == target[S[high]]) {
                ++count;
            }
        }
        ++high;
        // 当窗口中字串包含目标字串时尝试收缩窗口
        while (count == target.size()) {
            // 记录最小窗口的范围
            if (high - low < min_len) {
                start = low;
                min_len = high - low;
            }
            // 跳过窗口最左边的目标字符,继续寻找新窗口
            if (target.count(S[low])) {
                if (window[S[low]] == target[S[low]]) {
                    --count;
                }
                --window[S[low]];
            }
            ++low;
        }
    }
    // 未找到包含目标字串的窗口
    if (min_len == INT32_MAX) {
        return string("");
    }
    return S.substr(start, min_len);
}

int main(int argc, char* argv[])
{
    string S("XDOYEZODEYXNZ"), T("XYZ");
    printf("%s\n", min_window(S, T).c_str());
    return 0;
}
