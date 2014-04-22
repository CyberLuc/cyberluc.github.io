#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x7FFFFFFF
using namespace std;
int n, m, p, q;
int City[1001][1001], troop[101];
bool vis[1001];
queue<int> que;
int bfs(){
    int cur = q, time, i;
    memset(vis, 0, sizeof(vis));
    vis[cur] = true;
    que.push(cur);
    while(!que.empty()){
        cur = que.front(); que.pop();
        //printf("Checking %d.\n", cur);
        time = City[cur][0];
        for(i = 1; i <= m; i++){
            if(City[cur][i]){
                if(!vis[i]){
                    City[i][0] = time + City[cur][i];
                    vis[i] = true;
                    que.push(i);
                }else if(time + City[cur][i] < City[i][0]){
                    City[i][0] = time + City[cur][i];
                }
                //printf("\tAccessing %d->%d (%d).\n", cur, i, City[i][0]);
            }
        }
    }
    int min = INF;
    for(i = 1; i <= n; i++){
        int tmp = City[troop[i]][0];
        min = tmp < min ? tmp : min;
    }
    return min;
}
int main(){
    int k, i, a, b, t;
    freopen("data.in", "r", stdin);
    scanf("%d", &k);
    while(k--){
        scanf("%d%d%d%d", &n, &m, &p, &q);
        memset(troop, 0, sizeof(troop));
        memset(City, 0, sizeof(City));
        for(i = 1; i <= n; i++) scanf("%d", &troop[i]);
        for(i = 1; i <= p; i++){
            scanf("%d%d%d", &a, &b, &t);
            City[b][a] = City[a][b] = t;
        }
        printf("%d\n", bfs());
    }
    return 0;
}
