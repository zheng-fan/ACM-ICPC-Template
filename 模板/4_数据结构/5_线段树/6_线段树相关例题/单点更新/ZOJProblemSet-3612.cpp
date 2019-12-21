#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int NV = 50005;
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
int update(int L,int c,int l,int r,int rt=1)
{
    if (L == l && l == r)
    {
        if (c==-1&&sum[rt]==0) return 0;
        sum[rt] += c;
        return 1;
    }
    int m = (l + r) >> 1;
    int ret;
    if (L <= m) ret=update(L, c, lson);
    else ret=update(L, c, rson);
    PushUp(rt);
    return ret;
}
int query(int c,int l,int r,int rt=1)
{
    if (l == r)
    {
        return l;
    }
    int m = (l + r) >> 1;
    int ret;
    if (sum[rt<<1]>=c) ret=query(c, lson);
    else ret=query(c-sum[rt<<1], rson);
    PushUp(rt);
    return ret;
}
int discrete(int data[],int n,int dis[],int ind[])
{
    int sub[n+1];
    memcpy(sub,data,sizeof(sub));
    sort(sub+1,sub+n+1);
    int m=unique(sub+1,sub+n+1)-sub-1;
    for(int i=1; i<=n; i++)
    {
        dis[i]=lower_bound(sub+1,sub+m+1,data[i])-sub;
        ind[dis[i]]=data[i];
    }
    return m;
}
int op[NV],data[NV],dis[NV],ind[NV];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        scanf("%d",&n);
        char s[10];
        for (int i=1; i<=n; i++)
        {
            scanf("%s",s);
            if (s[0]=='a') op[i]=1;
            else op[i]=2;
            scanf("%d",&data[i]);
        }
        int m=discrete(data,n,dis,ind);
        build(1,m);
        for (int i=1; i<=n; i++)
        {
            if (op[i]==1)
                update(dis[i],1,1,m);
            else
            {
                if (!update(dis[i],-1,1,m))
                {
                    puts("Wrong!");
                    continue;
                }
            }
            if (sum[1]==0) puts("Empty!");
            else
            {
                if (sum[1]%2) printf("%d\n",ind[query(sum[1]/2+1,1,m)]);
                else
                {
                    long long l=ind[query(sum[1]/2,1,m)];
                    long long r=ind[query(sum[1]/2+1,1,m)];
                    if ((l+r)%2) printf("%.1f\n",(l+r)/2.0);
                    else printf("%lld\n",(l+r)/2);
                }
            }
        }
    }
    return 0;
}
