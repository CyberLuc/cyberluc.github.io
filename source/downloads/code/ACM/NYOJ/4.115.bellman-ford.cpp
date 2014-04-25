#include<cstdio>
#include<cstring>
#include <vector>
using namespace std;

#define INF 0x7FFFFFFF
#define N 1001
#define M 200001
struct node{
    int from, to, weight;
};
int dist[N], Army[101];
int n, m, p, q;
vector<node> G;

void bellman(){
    int i, flag, j, k, temp;
    for(i = 0; i < m; ++i) dist[i] = INF;
    dist[q] = 0;

    for(i = 1; i < m; ++i){    // 遍历n-1次
        flag = false;
        for(j = 0; j < 2*p; ++j)     // 遍历所有边
            if(dist[G[j].from] != INF){ // 如果边存在
                temp = dist[G[j].from] + G[j].weight;
                // 若第j条边的存在缩短了到G[j].to的最短路径
                if(temp < dist[G[j].to]){
                    dist[G[j].to] = temp;
                    flag = true;
                }
            }
        if(!flag) break;        //如果不松弛了，可以提前跳出循环
    }
    // 本题不需要判断负权回路
}

int main(){
    int i, j, a, b, t, k, min;
    freopen("data.in", "r", stdin);
    scanf("%d", &k);
    while(k--){
        scanf("%d%d%d%d", &n, &m, &p, &q);
        for(i = 0; i < n; i++) scanf("%d", &Army[i]);
        G.reserve(2*p);
        for(i = 0; i < 2*p; i++) G[i].weight = INF;

        for(i = 0; i < p ; ++i){
            scanf("%d%d%d", &a, &b, &t);
            j = 2 * i;           // 无向边，存两次2*i,2*i-1
            // 为了便于Bellman-Ford进行遍历，直接将所有边依次存为数组
            if(t < G[j].weight){ // 重边处理
                // 无向图
                G[j].from = a;
                G[j].to = b;
                G[j].weight = t;

                G[++j].from = b;
                G[j].to = a;
                G[j].weight = t;
            }
        }
        bellman();
        min = INF;
        for(i = 0; i < n; ++i)
            if(dist[Army[i]] < min) min = dist[Army[i]];
        printf("%d\n",min);
    }
    return 0;
}
