typedef int mytype;
const int NV=40005;
const int NE=NV;
const int NQ=10005;
mytype dis[NV],ans[NV];
int vis[NV],he[NV],hq[NV],ecnt,qcnt;
struct edge
{
    int v,next;
    mytype l;
} E[2*NE];
struct quer
{
    int v,next,i;
} q[2*NQ];
void adde(int u,int v,mytype l)
{
    E[++ecnt].v=v;
    E[ecnt].l=l;
    E[ecnt].next=he[u];
    he[u]=ecnt;
}
void addq(int u,int v,int i)
{
    q[++qcnt].v=v;
    q[qcnt].i=i;
    q[qcnt].next=hq[u];
    hq[u]=qcnt;
}
int fa[NV],rk[NV];
void init(int n,int m)
{
    ecnt=0;
    qcnt=0;
    memset(vis,0,sizeof(vis));
    memset(rk,0,sizeof(rk));
    memset(he,-1,sizeof(he));
    memset(hq,-1,sizeof(hq));
    for (int i=1; i<=m; i++)
    {
        int u,v;
        mytype l;
        scanf("%d%d%d",&u,&v,&l);
        adde(u,v,l);
        adde(v,u,l);
    }
}
int finds(int x)
{
    int k,j,r;
    r=x;
    while(r!=fa[r])
        r=fa[r];
    k=x;
    while(k!=r)
    {
        j=fa[k];
        fa[k]=r;
        k=j;
    }
    return r;
}
void tarjan(int u,mytype d)
{
    dis[u]=d;
    fa[u]=u;
    vis[u]=1;
    for (int i=he[u]; i!=-1; i=E[i].next)
        if (!vis[E[i].v])
            tarjan(E[i].v,d+E[i].l),fa[E[i].v]=u;
    for (int i=hq[u]; i!=-1; i=q[i].next)
        if (vis[q[i].v])
            ans[q[i].i]=dis[u]+dis[q[i].v]-2*dis[finds(q[i].v)];
}
void solve(int n,int m)
{
    init(n,m);
    int k;
    scanf("%d",&k);
    for (int i=1; i<=k; i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        addq(u,v,i);
        addq(v,u,i);
    }
    tarjan(1,0);
    for (int i=1; i<=k; i++)
        printf("%d\n",ans[i]);
}
