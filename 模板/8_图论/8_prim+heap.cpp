typedef int mytype;
const int NV=105;
const int NE=10005*2;
mytype dis[NV];
int pre[NV],vis[NV],he[NV],ecnt,pcnt;
struct edge
{
    int v,next;
    mytype l;
} E[NE];
void adde(int u,int v,mytype l)
{
    E[++ecnt].v=v;
    E[ecnt].l=l;
    E[ecnt].next=he[u];
    he[u]=ecnt;
}
void init(int n,int m,int s)
{
    ecnt=0;
    memset(pre,0,sizeof(pre));
    memset(vis,0,sizeof(vis));
    memset(he,-1,sizeof(he));
    for (int i=0; i<=n; i++)
        dis[i]=inf;
    dis[s]=0;
    for (int i=1; i<=m; i++)
    {
        int u,v;
        mytype l;
        scanf("%d%d%d",&u,&v,&l);
        adde(u,v,l);
        adde(v,u,l);
    }
}
struct point
{
    int u;
    mytype l;
    point(int u,mytype l):u(u),l(l) {}
    bool operator<(const point &p) const
    {
        return l>p.l;
    }
};
mytype prim_heap(int s)
{
    priority_queue<point> q;
    q.push(point(s,0));
    mytype ans=0;
    pcnt=0;
    while(!q.empty())
    {
        point p=q.top();
        q.pop();
        int u=p.u;
        if (vis[u])
            continue;
        vis[u]=1;
        ans+=p.l;//==dis[x]
        pcnt++;
        for (int i=he[u]; i!=-1; i=E[i].next)
            if (!vis[E[i].v]&&E[i].l<dis[E[i].v])
            {
                dis[E[i].v]=E[i].l;
                pre[E[i].v]=u;
                q.push(point(E[i].v,dis[E[i].v]));
            }
    }
    return ans;
}
bool judge(int n)
{
    return pcnt==n;
}
