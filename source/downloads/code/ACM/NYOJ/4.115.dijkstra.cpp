#include<cstdio>
#include<cstring>
#include<vector>
#define N 1001
#define INF 0x7FFFFFFF
using namespace std;
struct node{
    int v, w;
    node(int a, int b){
        v = a; w = b;
    }
};
vector<node*> G[N];
int dist[N], Army[101];
bool vis[N];
int m, n, p, q;

void dijkstra(){
    int i, j, u, w, cur = q;
    dist[cur] = 0;
    while(!vis[cur]){           // 当还有节点没有被访问时
        vis[cur] = 1;
        for(i = 0; i < G[cur].size(); i++){ // 遍历cur节点的邻接点
            u = G[cur][i]->v;               // 邻接点的节点号
            w = G[cur][i]->w;               // 权重
            if(dist[cur] + w < dist[u])     // 更新邻接点最短路径权值
                dist[u] = dist[cur] + w;
        }
        int min_cost = INF;
        for(i = 1; i <= m; i++){ // 查找未访问的最短路径节点
            if(!vis[i] && dist[i] < min_cost){
                min_cost = dist[i];
                cur = i;
            }
        }
    }
}

int main(){
    int i, j, k, a, b, c;
    freopen("data.in", "r", stdin);
    scanf("%d", &k);
    while(k--){
        scanf("%d%d%d%d", &n, &m, &p, &q);
        for(i = 0; i <= m; i++){ // 初始化
            G[i].clear();
            dist[i] = INF;
            vis[i] = 0;
        }
        for(i = 0; i < n; i++) scanf("%d", &Army[i]);
        while(p--){
            scanf("%d%d%d", &a, &b, &c);
            G[a].push_back(new node(b, c));
            G[b].push_back(new node(a, c));
        }
        dijkstra();
        int ans = INF;
        for(i = 0; i < n; i++){
            if(ans > dist[Army[i]])
                ans = dist[Army[i]];
        }
        printf("%d\n", ans);
    }
    return 0;
}
