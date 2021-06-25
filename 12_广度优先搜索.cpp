#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

// 根据图邻接表从指定节点开始搜索连通的路径
// 遍历时序号小的邻居节点会被先访问
void bfs(int start_node, vector<vector<bool> >& edge, 
    vector<bool>& visit, vector<int>& result)
{
    int num_nodes = visit.size();
    if (start_node < 0 || start_node >= num_nodes) {
        return;
    }
    queue<int> q;
    // 放入指定节点到队列中作为遍历起点
    q.push(start_node);
    visit[start_node] = true;
    // 当队列为空则遍历无向图结束
    while (q.size() > 0) {
        int node = q.front();
        result.push_back(node);
        q.pop();
        // 访问邻接表中连通的全部未遍历邻居节点
        for (int k = 0; k < num_nodes; k++) {
            if (edge[node][k] && !visit[k]) {
                q.push(k);
                visit[k] = true;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    int num_nodes = 4, start_node = 0;
    vector<bool> visit(num_nodes, false);
    vector<vector<bool> > edge(num_nodes);
    for (int k = 0; k < num_nodes; k++) {
        edge[k].resize(num_nodes, false);
    }
    // 构造图邻接表，指定节点间的连通关系
    edge[0][2] = true;
    edge[0][3] = true;
    edge[1][2] = true;
    edge[2][0] = true;
    edge[2][1] = true;
    edge[3][0] = true;
    vector<int> result;
    bfs(start_node, edge, visit, result);
    for (int k = 0; k < result.size(); k++) {
        printf("%d ", result[k]);
    }
    printf("\n");
    return 0;
}
