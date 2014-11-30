#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define ll long long
const int NV = 55555;
long long stt[NV << 2], mn[NV << 2];
void PushUp(int rt)
{
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
}
void PushDown(int rt, int m)
{
    if (stt[rt] != inf)
    {
        stt[rt << 1] = min(stt[rt], stt[rt << 1]);
        stt[rt << 1 | 1] = min(stt[rt], stt[rt << 1 | 1]);
        mn[rt << 1] = min(mn[rt << 1], stt[rt << 1]);
        mn[rt << 1 | 1] = min(mn[rt << 1 | 1], stt[rt << 1 | 1]);
        stt[rt] = inf;
    }
}
void build(int l, int r, int rt = 1)
{
    stt[rt] = inf;
    if (l == r)
    {
        mn[rt] = inf;
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void update(int L, int R, long long c, int l, int r, int rt = 1)
{
    if (L <= l && r <= R)
    {
        stt[rt] = min(c, stt[rt]);
        mn[rt] = min(mn[rt], stt[rt]);
        return ;
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , c , lson);
    if (m < R) update(L , R , c , rson);
    PushUp(rt);
}
ll query(int L, int l, int r, int rt = 1)
{
    if (L == l && l == r)
    {
        return mn[rt];
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) return query(L , lson);
    else return query(L , rson);
}
ll mon[NV];
int day[NV], n;
int main()
{
    while(~scanf("%d", &n))
    {
        for (int i = 1; i <= n; i++) scanf("%lld", mon + i);
        for (int i = 1; i <= n; i++) scanf("%d", day + i);
        build(1, n, 1);
        ll get = 0;
        for (int i = 1; i <= n; i++)
        {
            update(i, min(i + day[i] - 1, n), get + mon[i], 1, n, 1);
            get = query(i, 1, n, 1);
            //cout<<get<<endl;
        }
        printf("%lld\n", get);
    }
    return 0;
}
