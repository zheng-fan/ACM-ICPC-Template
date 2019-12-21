#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int NV = 100005;
int stt[NV<<2],sum[NV<<2];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void PushDown(int rt,int m)
{
    if (stt[rt])
    {
        stt[rt<<1] = stt[rt];
        stt[rt<<1|1] = stt[rt];
        sum[rt<<1] = stt[rt] * (m - (m >> 1));
        sum[rt<<1|1] = stt[rt] * (m >> 1);
        stt[rt] = 0;
    }
}
void build(int l,int r,int rt=1)
{
    stt[rt] = 0;
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
void update(int L,int R,int c,int l,int r,int rt=1)
{
    if (L <= l && r <= R)
    {
        stt[rt] = c;
        sum[rt] = c * (r - l + 1);
        return ;
    }
    PushDown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, c, lson);
    if (m < R) update(L, R, c, rson);
    PushUp(rt);
}
int query(int L,int R,int l,int r,int rt=1)
{
    if (L <= l && r <= R)
    {
        return sum[rt];
    }
    PushDown(rt, r - l + 1);
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m) ret += query(L, R, lson);
    if (m < R) ret += query(L, R, rson);
    return ret;
}
int main()
{
    int t;
    cin>>t;
    int cas=0;
    while(t--)
    {
        int n,q;
        cin>>n>>q;
        build(1,n);
        while(q--)
        {
            int l,r,c;
            scanf("%d%d%d",&l,&r,&c);
            update(l,r,c,1,n);
        }
        printf("Case %d: The total value of the hook is %d.\n",++cas,sum[1]);
    }
    return 0;
}
