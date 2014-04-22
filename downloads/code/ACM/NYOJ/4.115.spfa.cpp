#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x7FFFFFFF
#define MAXN 1001
struct node{ int to, weight; };
int n, m, p, q;
int Army[MAXN], dist[MAXN];
bool inQueue[MAXN];
vector<node> G[MAXN];

void SPFA(){
    int i, cur = q, v, cur2v;
    queue<int> que;
    for(i = 0; i < m; i++){
        dist[i] = INF;
        inQueue[i] = 0;
    }
    dist[cur] = 0;
    que.push(cur);
    inQueue[cur] = true;

    while(!que.empty()){
        cur = que.front();
        que.pop();
        inQueue[cur] = false;
        for(i = 0; i < G[cur].size(); i++){
            v = G[cur][i].to;
            cur2v = G[cur][i].weight;
            if(dist[cur] + cur2v < dist[v]){
                dist[v] = dist[cur] + cur2v;
                if(!inQueue[v]){
                    que.push(v);
                    inQueue[v] = 1;
                }
            }
        } // for
    } // while
} // void SPFA()

int main(){
    int k, i, a, b, t;
    freopen("data.in", "r", stdin);
    scanf("%d", &k);
    while(k--){
        scanf("%d%d%d%d", &n, &m, &p, &q);
        for(i = 0; i < n; i++) scanf("%d", &Army[i]);
        for(i = 0; i < m; i++) G[i].clear();
        for(i = 0; i < p; i++){
            scanf("%d%d%d", &a, &b, &t);
            node tmp;
            tmp.to = b; tmp.weight = t;
            G[a].push_back(tmp);
            tmp.to = a;
            G[b].push_back(tmp);
        }
        SPFA();

        int min = INF;
        for(i = 0; i < n; i++){
            if(dist[Army[i]]<min) min = dist[Army[i]];
        }
        printf("%d\n", min);
    }
    return 0;
}
