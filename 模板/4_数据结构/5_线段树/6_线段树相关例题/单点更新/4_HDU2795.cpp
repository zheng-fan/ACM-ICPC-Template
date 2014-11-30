#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
int h,w,n;
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
        mx[rt]=w;
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void update(int c,int l,int r,int rt=1)
{
    if (l == r)
    {
        mx[rt]-=c;
        printf("%d\n",l);
        return;
    }
    int m = (l + r) >> 1;
    if (mx[rt<<1]>=c) update(c , lson);
    else update(c , rson);
    PushUp(rt);
}
int main()
{
    while(~scanf("%d%d%d",&h,&w,&n))
    {
        build(1,min(h,200000));
        for (int i=1; i<=n; i++)
        {
            int x;
            scanf("%d",&x);
            if (x<=mx[1]) update(x,1,min(h,200000));
            else puts("-1");
        }
    }
    return 0;
}
