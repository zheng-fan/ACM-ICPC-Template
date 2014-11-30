typedef int mytype;
const int NV=105;
const int NE=10005*2;
mytype dis[NV];
int pre[NV],vis[NV],vcnt[NV],he[NV],ecnt,flag;
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
    memset(vcnt,0,sizeof(vcnt));
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
void spfa(int n,int m,int s)
{
    queue<int> q;
    vis[s]=1;
    q.push(s);
    flag=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=0;
        if(vcnt[u]>=n)
        {
            flag=1;
            break;
        }
        for (int i=he[u]; i!=-1; i=E[i].next)
            if (dis[u]+E[i].l<dis[E[i].v])
            {
                dis[E[i].v]=dis[u]+E[i].l;
                pre[E[i].v]=u;
                if (!vis[E[i].v])
                {
                    vis[E[i].v]=1;
                    q.push(E[i].v);
                    vcnt[E[i].v]++;
                }
            }
    }
}
