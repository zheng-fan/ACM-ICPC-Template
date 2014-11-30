const int NV=505;
const int NE=10005;
int he[NV],ecnt,pre[NV],vis[NV];
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
int dfs(int u)
{
    for(int i=he[u]; i!=-1; i=E[i].next)
    {
        int v=E[i].v;
        if(!vis[v])
        {
            vis[v]=1;
            if(pre[v]==0||dfs(pre[v]))
            {
                pre[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
void init(int m)
{
    ecnt=0;
    memset(he,-1,sizeof(he));
    memset(pre,0,sizeof(pre));
    while(m--)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        adde(u,v);
    }
}
int hungary(int n)
{
    int ans=0;
    for (int i=1; i<=n; i++)
    {
        memset(vis,0,sizeof(vis));
        ans+=dfs(i);
    }
    return ans;
}
