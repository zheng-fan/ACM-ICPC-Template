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
    if (L == l && l == r)
    {
        sum[rt] += c;
        return ;
    }
    int m = (l + r) >> 1;
    if (L <= m) update(L , c , lson);
    else update(L , c , rson);
    PushUp(rt);
}
int query(int L,int R,int l,int r,int rt=1)
{
    if (L <= l && r <= R)
        return sum[rt];
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m) ret += query(L , R , lson);
    if (m < R) ret += query(L , R , rson);
    return ret;
}
int main()
{
    int t,cas=0;
    cin>>t;
    while(t--)
    {
        int n;
        scanf("%d",&n);
        int x,v;
        build(1,n);
        for (int i=1; i<=n; i++)
        {
            scanf("%d",&v);
            update(i,v,1,n);
        }
        printf("Case %d:\n",++cas);
        char s[10];
        while(scanf("%s",s),s[0]!='E')
        {
            scanf("%d%d",&x,&v);
            if (s[0]=='A')
                update(x,v,1,n);
            if (s[0]=='S')
                update(x,-v,1,n);
            if (s[0]=='Q')
                printf("%d\n",query(x,v,1,n));
        }
    }
    return 0;
}
