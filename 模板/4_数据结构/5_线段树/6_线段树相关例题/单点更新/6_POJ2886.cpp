#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int NV = 500005;
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
    else ret=update(c-sum[rt<<1] , rson);
    PushUp(rt);
    return ret;
}
int y[500005]= {};
void getfactor(int n)
{
    int x=sqrt(n);
    for (int i=1; i<=x; i++)
    {
        for (int j=i+1; j*i<=n; j++)
            y[i*j]+=2;
        y[i*i]++;
    }
}
char s[500005][20];
int x[500005];
int main()
{
    getfactor(500000);
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        build(1,n);
        for (int i=1; i<=n; i++)
            scanf("%s%d",s[i],&x[i]);
        int m,mx=-1;
        for (int i=1; i<=n; i++)
            if (y[i]>mx)
            {
                m=i;
                mx=y[i];
            }
        int ans=k;
        while(m--)
        {
            ans=update(k,1,n);
            if (!m) continue;
            if (x[ans]>0)
                k=((k-1+x[ans]-1)%sum[1]+sum[1])%sum[1]+1;
            else
                k=((k-1+x[ans])%sum[1]+sum[1])%sum[1]+1;
        }
        printf("%s %d\n",s[ans],mx);
    }
    return 0;
}
