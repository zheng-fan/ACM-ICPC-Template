const int NV=10005;
const int NE=NV;
int he[NV],ecnt;
struct edge
{
    int v,next;
} E[NE];
void adde(int u,int v)
{
    ecnt++;
    E[ecnt].v=v;
    E[ecnt].next=he[u];
    he[u]=ecnt;
}
int l[NV],r[NV],p;
void dfs(int u)
{
    p++;
    l[u]=p;
    for (int i=he[u]; i!=-1; i=E[i].next)
        dfs(E[i].v);
    r[u]=p;
}
void init()
{
    ecnt=p=0;
    memset(he,-1,sizeof(he));
}
