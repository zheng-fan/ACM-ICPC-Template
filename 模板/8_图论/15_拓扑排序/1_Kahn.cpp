const int NV=10005;
const int NE=20005;
int he[NV],ecnt,ind[NV],ord[NV],acnt;
struct edge
{
    int v,next;
} E[NE];
void adde(int u,int v)
{
    E[++ecnt].v=v;
    E[ecnt].next=he[u];
    he[u]=ecnt;
    ind[v]++;
}
void init(int n,int m)
{
    ecnt=0;
    acnt=0;
    memset(he,-1,sizeof(he));
    memset(ind,0,sizeof(ind));
    for (int i=1; i<=m; i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        adde(u,v);
    }
}
int toposort(int n)
{
    queue<int> q;
    for (int i=1; i<=n; i++)
        if (ind[i]==0) q.push(i);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        ord[++acnt]=u;
        for (int i=he[u]; i!=-1; i=E[i].next)
            if (ind[E[i].v])
            {
                ind[E[i].v]--;
                if (ind[E[i].v]==0) q.push(E[i].v);
            }
    }
    if (acnt!=n) return -1;
    return acnt;
}
