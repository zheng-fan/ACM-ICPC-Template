typedef int mytype;
const int NV=300005;
const int NE=300005*2;
mytype dis[NV];
int pre[NV],vis[NV],he[NV],ecnt;
struct edge
{
    int v,next;
    mytype l;
} E[NE];
void adde(int u,int v,mytype l)
{
    ecnt++;
    E[ecnt].v=v;
    E[ecnt].l=l;
    E[ecnt].next=he[u];
    he[u]=ecnt;
}
void init(int n,int m,int s)
{
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
    point(int a,mytype b):u(a),l(b) {}
    bool operator<(const point p) const
    {
        return l>p.l;
    }
};
void dijkstra_heap(int s)
{
    priority_queue<point> q;
    q.push(point(s,0));
    while(!q.empty())
    {
        point p=q.top();
        q.pop();
        int u=p.u;
        if (vis[u])
            continue;
        vis[u]=1;
        for (int i=he[u]; i!=-1; i=E[i].next)
            if (!vis[E[i].v]&&p.l+E[i].l<dis[E[i].v])
            {
                dis[E[i].v]=dis[u]+E[i].l;
                pre[E[i].v]=u;
                q.push(point(E[i].v,dis[E[i].v]));
            }
    }
}
int main()
{
    int t;
    cin>>t;
    int cas=0;
    while(t--)
    {
        int n,m,c;
        scanf("%d%d%d",&n,&m,&c);
        ecnt=0;
        memset(pre,0,sizeof(pre));
        memset(vis,0,sizeof(vis));
        memset(he,-1,sizeof(he));
        for (int i=1; i<=n; i++)
        {
            int x;
            scanf("%d",&x);
            adde(i,n+x,0);
            adde(2*n+x,i,0);
        }
        for (int i=1; i<n; i++)
        {
            adde(n+i,2*n+i+1,c);
            adde(n+i+1,2*n+i,c);
        }
        init(n*3,m,1);
        dijkstra_heap(1);
        int ans=dis[n];
        if (ans==inf)
            ans=-1;
        printf("Case #%d: %d\n",++cas,ans);
    }
    return 0;
}
