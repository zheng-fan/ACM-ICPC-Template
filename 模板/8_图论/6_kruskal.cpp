typedef int mytype;
const int NV=105;
const int NE=10005;
struct edge
{
    int u,v;
    mytype l;
    bool operator<(const edge e) const
    {
        return l<e.l;
    }
} E[NE];
int f[NV],rk[NV];
int finds(int x)
{
    return f[x]==x?x:f[x]=finds(f[x]);
}
void uni(int a,int b)
{
    a=finds(a);
    b=finds(b);
    if (a==b) return;
    if (rk[a]>rk[b]) f[b]=a;
    else
    {
        if (rk[a]==rk[b]) rk[b]++;
        f[a]=b;
    }
}
void init(int n,int m)
{
    memset(rk,0,sizeof(rk));
    for (int i=1; i<=n; i++)
        f[i]=i;
    for (int i=1; i<=m; i++)
        scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].l);
}
mytype kruskal(int n,int m)
{
    sort(E+1,E+m+1);
    mytype ans=0;
    for (int i=1; i<=m; i++)
        if (finds(E[i].u)!=finds(E[i].v))
        {
            uni(E[i].u,E[i].v);
            ans+=E[i].l;
        }
    return ans;
}
bool judge(int n)
{
    int flag=0;
    for (int i=1; i<=n; i++)
        if (finds(i)==i)
            flag++;
    return flag==1;
}
