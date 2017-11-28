const int NV=10005;
const int NE=20005;
int he[NV],ecnt,vis[NV],ord[NV],acnt; ///这里ord顺序是反过来的
struct edge
{
    int v,next;
} E[NE];
void adde(int u,int v)
{
    E[++ecnt].v=v;
    E[ecnt].next=he[u];
    he[u]=ecnt;
}
void init(int n,int m)
{
    ecnt=0;
    acnt=0;
    memset(he,-1,sizeof(he));
    memset(vis,0,sizeof(vis));
    for (int i=1; i<=m; i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        adde(u,v);
    }
}
int dfs(int u)
{
    vis[u]=1;
    for (int i=he[u]; i!=-1; i=E[i].next)
    {
        if (vis[E[i].v]==1) return -1;
        else if (!vis[E[i].v]&&dfs(E[i].v)==-1) return -1;
    }
    vis[u]=2;
    ord[++acnt]=u;
    return 0;
}
int toposort(int n)
{
    for (int i=1; i<=n; i++)
        if (!vis[i]&&dfs(i)==-1)
            return -1;
    return acnt;
}
