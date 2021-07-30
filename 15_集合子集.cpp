#include <cstdio>
#include <vector>

using namespace std;

// 回溯法输出集合的全部子集
void subsets(int index, vector<int>& S, vector<int>& vt, 
             vector<vector<int> >& res) {
    res.emplace_back(vt);
    for (int k = index; k < S.size(); ++k) {
        vt.emplace_back(S[k]);
        subsets(k + 1, S, vt, res);
        vt.pop_back();
    }
}

int main(int argc, char* argv[])
{
    vector<vector<int> > res;
    vector<int> S{1, 2, 3}, vt;
    subsets(0, S, vt, res);
    for (int k = 0; k < res.size(); ++k) {
        for (int j = 0; j < res[k].size(); ++j) {
            printf("%d ", res[k][j]);
        }
        printf("\n");
    }
    return 0;
}
