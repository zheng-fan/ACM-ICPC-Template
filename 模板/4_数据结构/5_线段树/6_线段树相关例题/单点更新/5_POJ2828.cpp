#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int NV = 200005;
int sum[NV<<2];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt=1)
{
    if (l == r)
    {
        sum[rt]=1;
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
int update(int c,int l,int r,int rt=1)
{
    if (l == r)
    {
        sum[rt]--;
        return l;
    }
    int m = (l + r) >> 1;
    int ret;
    if (sum[rt<<1]>=c) ret=update(c, lson);
    else ret=update(c-sum[rt<<1], rson);
    PushUp(rt);
    return ret;
}
int a[200005];
int q[200005];
int w[200005];
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        build(1,n);
        for (int i=1; i<=n; i++)
            scanf("%d%d",&q[i],&w[i]);
        for (int i=n; i>=1; i--)
            a[update(q[i]+1,1,n)]=w[i];
        for (int i=1; i<=n; i++)
            printf("%d%c",a[i]," \n"[i==n]);
    }
    return 0;
}
