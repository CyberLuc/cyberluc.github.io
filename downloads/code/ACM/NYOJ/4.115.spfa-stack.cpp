#include <stdio.h>
#include <string.h>
#define VMAX 1001
#define EMAX 100001
struct edge{
    int v,w,next;
}e[EMAX];
int head[VMAX], ep;
int stack[VMAX], top, q, n;
int dis[VMAX], troop[101];
bool vis[VMAX];

void addedge(int u, int v, int w){
    ep++;
    e[ep].v = v; e[ep].w = w;
    e[ep].next = head[u];
    head[u] = ep;
}

void spfa(){
    int i, u = q, v;
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(dis));
    dis[u] = top = 0;
    vis[u] = true;
    stack[top++] = u;

    while(top){
        u = stack[--top];
        vis[u] = 0;
        for(i = head[u]; i != -1; i = e[i].next){
            v = e[i].v;
            if(dis[v] > dis[u] + e[i].w){
                dis[v] = dis[u] + e[i].w;
                if(!vis[v]){
                    vis[v] = true;
                    stack[top++] = v;
                }
            }
        }
    }
    int min = 0x7FFFFFFF;
    for(i = 1; i <= n; i++){
        int tmp = dis[troop[i]];
        min = tmp < min ? tmp : min;
    }
    printf("%d\n", min);
}
int main(){
    int k, p, i, m, v1, v2, cost;
    freopen("data.in", "r", stdin);
    scanf("%d", &k);
    while(k--){
        ep = 0;
        memset(head, -1, sizeof(head));
        memset(e, 0, sizeof(e));
        scanf("%d%d%d%d", &n, &m, &p, &q);
        for(i = 1; i <= n; i++) scanf("%d", &troop[i]);
        for(i = 1; i <= p; i++){
            scanf("%d%d%d", &v1, &v2, &cost);
            addedge(v1, v2, cost);
            addedge(v2, v1, cost);
        }
        spfa();
    }

    return 0;
}
