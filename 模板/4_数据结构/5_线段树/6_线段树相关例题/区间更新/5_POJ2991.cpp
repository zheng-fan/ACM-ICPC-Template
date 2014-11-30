#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int NV = 10005;
double add[NV<<2],x[NV<<2],y[NV<<2],ang[NV<<2];
//ang不需要pushup，因为查询是单点查询
void PushUp(int rt)
{
    x[rt]=x[rt<<1]+x[rt<<1|1];
    y[rt]=y[rt<<1]+y[rt<<1|1];
}
void PushDown(int rt,int m)
{
    if (add[rt])
    {
        ang[rt<<1] += add[rt];
        ang[rt<<1|1] += add[rt];
        add[rt<<1] += add[rt];
        add[rt<<1|1] += add[rt];
        double xx=x[rt<<1],yy=y[rt<<1];
        x[rt<<1] = cos(add[rt])*xx-sin(add[rt])*yy;
        y[rt<<1] = sin(add[rt])*xx+cos(add[rt])*yy;
        xx=x[rt<<1|1],yy=y[rt<<1|1];
        x[rt<<1|1] = cos(add[rt])*xx-sin(add[rt])*yy;
        y[rt<<1|1] = sin(add[rt])*xx+cos(add[rt])*yy;
        add[rt] = 0;
    }
}
void build(int l,int r,int rt=1)
{
    add[rt] = ang[rt] = 0;
    if (l == r)
    {
        scanf("%lf",&y[rt]);
        x[rt] = 0;
//        ang[rt] = pi/2; //此处可以不加，因为只需要相对值
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void update(int L,int R,double c,int l,int r,int rt=1)
{
    if (L <= l && r <= R)
    {
        ang[rt] += c;
        add[rt] += c;
        double xx=x[rt],yy=y[rt];
        x[rt] = cos(c)*xx-sin(c)*yy;
        y[rt] = sin(c)*xx+cos(c)*yy;
        return ;
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , c , lson);
    if (m < R) update(L , R , c , rson);
    PushUp(rt);
}
double query(int L,int l,int r,int rt=1)
{
    if (L == l && l == r)
    {
        return ang[rt];
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) return query(L , lson);
    else return query(L , rson);
}
int main()
{
    int n,q;
    while(scanf("%d%d",&n,&q)!=EOF)
    {
        build(1,n);
        while(q--)
        {
            int s,d;
            scanf("%d%d",&s,&d);
            update(s+1,n,d/180.0*pi-(query(s+1,1,n)-query(s,1,n)+pi),1,n);
            printf("%.2f %.2f\n",x[1],y[1]);
        }
        puts("");
    }
    return 0;
}
