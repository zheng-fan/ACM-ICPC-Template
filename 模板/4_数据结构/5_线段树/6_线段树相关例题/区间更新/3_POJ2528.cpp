#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int NV = 20005;
int col[NV<<2];
void PushDown(int rt,int m)
{
    if (col[rt])
    {
        col[rt<<1] = col[rt];
        col[rt<<1|1] = col[rt];
        col[rt] = 0;
    }
}
void build(int l,int r,int rt=1)
{
    col[rt] = 0;
    if (l == r)
    {
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
}
void update(int L,int R,int c,int l,int r,int rt=1)
{
    if (L <= l && r <= R)
    {
        col[rt] = c;
        return ;
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , c , lson);
    if (m < R) update(L , R , c , rson);
}
int query(int L,int l,int r,int rt=1)
{
    if (L == l && l == r)
    {
        return col[rt];
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) return query(L , lson);
    else return query(L , rson);
}
int discrete(int data[],int n,int dis[])
{
    int sub[n+1];
    memcpy(sub,data,sizeof(sub));
    sort(sub+1,sub+n+1);
    int m=unique(sub+1,sub+n+1)-sub-1;
    for(int i=1; i<=n; i++)
        dis[i]=lower_bound(sub+1,sub+m+1,data[i])-sub;
    return m;
}
int a[NV],dis[NV],co[NV];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for (int i=1; i<=n; i++)
            scanf("%d%d",&a[i],&a[i+n]);
        discrete(a,2*n,dis);
        build(1,2*n);
        for (int i=1; i<=n; i++)
            update(dis[i],dis[i+n],i,1,2*n);
        memset(co,0,sizeof(co));
        for (int i=1; i<=2*n; i++)
            co[query(i,1,2*n)]=1;
        printf("%d\n",accumulate(co+1,co+2*n+1,0));
    }
    return 0;
}
