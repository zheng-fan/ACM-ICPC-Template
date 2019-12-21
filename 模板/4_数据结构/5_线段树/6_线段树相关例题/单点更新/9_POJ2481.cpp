#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int NV = 100005;
int sum[NV<<2];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt=1)
{
    if (l == r)
    {
        sum[rt]=0;
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void update(int L,int c,int l,int r,int rt=1)
{
    if (l == r)
    {
        sum[rt] += c;
        return ;
    }
    int m = (l + r) >> 1;
    if (L <= m) update(L, c, lson);
    else update(L, c, rson);
    PushUp(rt);
}
int query(int L,int R,int l,int r,int rt=1)
{
    if (L <= l && r <= R)
        return sum[rt];
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m) ret += query(L, R, lson);
    if (m < R) ret += query(L, R, rson);
    return ret;
}
struct node
{
    int l,r,i;
    bool operator<(const node &b) const
    {
        if (l==b.l) return r>b.r;
        return l<b.l;
    }
} a[100005];
int ans[100005];
int main()
{
    int n;
    while(cin>>n,n)
    {
        build(1,100001);
        for (int i=1; i<=n; i++)
            scanf("%d%d",&a[i].l,&a[i].r),a[i].l++,a[i].r++,a[i].i=i;
        sort(a+1,a+n+1);
        for (int i=1; i<=n; i++)
        {
            if (a[i].l==a[i-1].l&&a[i].r==a[i-1].r)
                ans[a[i].i]=ans[a[i-1].i];
            else
                ans[a[i].i]=query(a[i].r,100001,1,100001);
            update(a[i].r,1,1,100001);
        }
        for (int i=1; i<=n; i++)
            printf("%d%c",ans[i]," \n"[i==n]);
    }
    return 0;
}
