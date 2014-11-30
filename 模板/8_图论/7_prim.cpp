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
mytype prim(int n)
{
    mytype ans=0;
    for (int i=1; i<=n; i++)
    {
        int u=0;
        for (int j=1; j<=n; j++)
            if (!vis[j]&&dis[j]<dis[u])
                u=j;
        vis[u]=1;
        ans+=dis[u];
        for (int j=1; j<=n; j++)
            if (!vis[j]&&g[u][j]<dis[j])
            {
                dis[j]=g[u][j];
                pre[j]=u;
            }
    }
    return ans;
}
bool judge(int n)
{
    int cnt=0;
    for (int i=1; i<=n; i++)
        cnt+=vis[i];
    return cnt==n;
}
