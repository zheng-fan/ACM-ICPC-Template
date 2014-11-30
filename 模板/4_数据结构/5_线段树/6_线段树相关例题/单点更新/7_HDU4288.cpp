#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int NV = 100005;
int sum[NV<<2];
long long ans[NV<<2][5];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    for (int i=0; i<5; i++)
        ans[rt][i]=ans[rt<<1][i]+ans[rt<<1|1][((i-sum[rt<<1])%5+5)%5];
}
void build(int l,int r,int rt=1)
{
    if (l == r)
    {
        sum[rt]=0;
        memset(ans[rt],0,sizeof(ans[rt]));
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void update(int L,int t,int c,int l,int r,int rt=1)
{
    if (L == l && l == r)
    {
        sum[rt]+=t;
        ans[rt][1]+=t*c;
        return ;
    }
    int m = (l + r) >> 1;
    if (L <= m) update(L, t , c , lson);
    else update(L, t , c , rson);
    PushUp(rt);
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
int op[100005],data[100005],dis[100005];
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        char s[5];
        int m=0;
        for (int i=1; i<=n; i++)
        {
            scanf("%s",s);
            if (s[0]=='a') op[i]=1,scanf("%d",&data[++m]);
            else if (s[0]=='d') op[i]=2,scanf("%d",&data[++m]);
            else op[i]=3;
        }
        m=discrete(data,m,dis);
        build(1,m);
        int x=0;
        for (int i=1; i<=n; i++)
        {
            if (op[i]==1) x++,update(dis[x],1,data[x],1,m);
            else if (op[i]==2) x++,update(dis[x],-1,data[x],1,m);
            else printf("%I64d\n",ans[1][3]);
        }
    }
    return 0;
}
