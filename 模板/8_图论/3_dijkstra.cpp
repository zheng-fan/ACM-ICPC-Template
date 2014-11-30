typedef int mytype;
const int NV=1005;
int pre[NV],vis[NV];
mytype dis[NV],g[NV][NV];
void init(int n,int m,int s)
{
    memset(pre,0,sizeof(pre));
    memset(vis,0,sizeof(vis));
    for (int i=0; i<=n; i++)
        dis[i]=inf;
    dis[s]=0;
    for (int i=1; i<=n; i++)
        for (int j=1; j<=n; j++)
            g[i][j]=inf;
    for (int i=1; i<=m; i++)
    {
        int u,v,l;
        scanf("%d%d%d",&u,&v,&l);
        g[u][v]=l;
        g[v][u]=l;
    }
}
void dijkstra(int n)
{
    for (int i=1; i<=n; i++)
    {
        int u=0;
        for (int j=1; j<=n; j++)
            if (!vis[j]&&dis[j]<dis[u])
                u=j;
        vis[u]=1;
        for (int j=1; j<=n; j++)
            if (g[u][j]!=inf&&!vis[j]&&dis[u]+g[u][j]<dis[j])
            {
                dis[j]=dis[u]+g[u][j];
                pre[j]=u;
            }
    }
}
