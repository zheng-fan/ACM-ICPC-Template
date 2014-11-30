typedef int mytype;
const int NV=40005;
const int NE=2*NV;
int vis[NV],he[NV],ecnt;
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
void init(int n,int m)
{
    ecnt=0;
    memset(he,-1,sizeof(he));
    for (int i=1; i<=m; i++)
    {
        int u,v;
        mytype l;
        scanf("%d%d%d",&u,&v,&l);
        adde(u,v,l);
        adde(v,u,l);
    }
}
int U;
mytype L;
void dfs(int u,int uu,mytype l)
{
    if (l>L)
    {
        U=u;
        L=l;
    }
    for (int i=he[u]; i!=-1; i=E[i].next)
        if (E[i].v!=uu)
            dfs(E[i].v,u,l+E[i].l);
}
mytype solve()
{
    dfs(1,0,0);
    dfs(U,0,0);
    return L;
}
