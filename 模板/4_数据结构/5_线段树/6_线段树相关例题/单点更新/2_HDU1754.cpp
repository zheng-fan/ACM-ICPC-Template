#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int NV = 200005;
int mx[NV<<2];
void PushUp(int rt)
{
    mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);
}
void build(int l,int r,int rt=1)
{
    if (l == r)
    {
        scanf("%d",&mx[rt]);
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
        mx[rt] = c;
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
        return mx[rt];
    int m = (l + r) >> 1;
    int ret = -1;
    if (L <= m) ret = max(ret,query(L , R , lson));
    if (m < R) ret = max(ret,query(L , R , rson));
    return ret;
}
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        build(1,n);
        char s[10];
        int a,b;
        while(m--)
        {
            scanf("%s%d%d",s,&a,&b);
            if (s[0]=='U')
                update(a,b,1,n);
            else
                printf("%d\n",query(a,b,1,n));
        }
    }
    return 0;
}
