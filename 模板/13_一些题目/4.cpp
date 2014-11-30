typedef int mytype;
const int NV=1005;
const int NE=10005;
mytype dis[NV][2];
int vis[NV][2],he[NV],ecnt,cnt[NV][2];
struct edge
{
    int v,next;
    mytype l;
} e[NE];
void adde(int u,int v,mytype l)
{
    ecnt++;
    e[ecnt].v=v;
    e[ecnt].l=l;
    e[ecnt].next=he[u];
    he[u]=ecnt;
}
struct point
{
    int u,flag;
    mytype l;
    point(int a,mytype b,int c):u(a),l(b),flag(c) {}
    bool operator<(const point p) const
    {
        return l>p.l;
    }
};
int dijkstra_heap(int n,int m,int s,int E)
{
    priority_queue<point> q;
    q.push(point(s,0,0));
    while(!q.empty())
    {
        point p=q.top();
        q.pop();
        int u=p.u;
        if (vis[u][p.flag])
            continue;
        vis[u][p.flag]=1;
        for (int i=he[u]; i!=-1; i=e[i].next)
        {
            int v=e[i].v;
            int dist=p.l+e[i].l;
            if (dist<dis[v][0])
            {
                if (dis[v][0]!=inf)
                {
                    dis[v][1]=dis[v][0];
                    cnt[v][1]=cnt[v][0];
                    q.push(point(v,dis[v][1],1));
                }
                dis[v][0]=dist;
                cnt[v][0]=cnt[u][p.flag];
                q.push(point(v,dis[v][0],0));
            }
            else if (dist==dis[v][0])
            {
                cnt[v][0]+=cnt[u][p.flag];
            }
            else if (dist<dis[v][1])
            {
                dis[v][1]=dist;
                cnt[v][1]=cnt[u][p.flag];
                q.push(point(v,dis[v][1],1));
            }
            else if (dist==dis[v][1])
            {
                cnt[v][1]+=cnt[u][p.flag];
            }
        }
    }
    if (dis[E][0]+1==dis[E][1])
        return cnt[E][0]+cnt[E][1];
    return cnt[E][0];
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        ecnt=0;
        memset(he,-1,sizeof(he));
        memset(vis,0,sizeof(vis));
        memset(cnt,0,sizeof(cnt));
        for (int i=1; i<=m; i++)
        {
            int u,v;
            mytype l;
            scanf("%d%d%d",&u,&v,&l);
            adde(u,v,l);
        }
        int s,E;
        scanf("%d%d",&s,&E);
        for (int i=1; i<=n; i++)
            dis[i][0]=dis[i][1]=inf;
        dis[s][0]=0;
        cnt[s][0]=1;
        printf("%d\n",dijkstra_heap(n,m,s,E));
    }
    return 0;
}
