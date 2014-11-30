#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int NV = 50005;
long long mul[NV<<2],sum[NV<<2],mx[NV<<2];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);
}
void PushDown(int rt,int m)
{
    if (mul[rt]!=1)
    {
        mul[rt<<1] *= mul[rt];
        mul[rt<<1|1] *= mul[rt];
        sum[rt<<1] *= mul[rt];
        sum[rt<<1|1] *= mul[rt];
        mx[rt<<1] *= mul[rt];
        mx[rt<<1|1] *= mul[rt];
        mul[rt] = 1;
    }
}
void build(int l,int r,int rt=1)
{
    mul[rt] = 1;
    if (l == r)
    {
        sum[rt]=1;
        mx[rt]=1;
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void update(int L,long long c,int l,int r,int rt)
{
    if (L == l && l == r)
    {
        sum[rt] += c;
        mx[rt] += c;
        return ;
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L , c , lson);
    else update(L , c , rson);
    PushUp(rt);
}
void update(int L,int R,long long c,int l,int r,int rt)
{
    if (L <= l && r <= R)
    {
        mul[rt] *= c;
        sum[rt] *= c;
        mx[rt] *= c;
        return ;
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , c , lson);
    if (m < R) update(L , R , c , rson);
    PushUp(rt);
}
long long num;
int query(long long c,int l,int r,int rt)
{
    if (l == r)
    {
        num=c;
        return l;
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (sum[rt<<1]>=c) return query(c , lson);
    else return query(c-sum[rt<<1] , rson);
}
long long query(int L,int R,int l,int r,int rt)
{
    if (L <= l && r <= R)
    {
        return mx[rt];
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    long long ret = 0;
    if (L <= m) ret = max(ret,query(L , R , lson));
    if (m < R) ret = max(ret,query(L , R , rson));
    return ret;
}
int main()
{
    int t;
    cin>>t;
    int cas=0;
    while(t--)
    {
        printf("Case #%d:\n",++cas);
        int n,m;
        scanf("%d%d",&n,&m);
        build(1,n);
        while(m--)
        {
            char str[5];
            long long a,b;
            scanf("%s%I64d%I64d",str,&a,&b);
            long long mx=0,s1,s2,mx1=0,mx2=0;
            int l=query(a,1,n,1);
            s1=num;
            mx1=query(l,l,1,n,1)-s1+1;
            l++;
            int r=query(b,1,n,1);
            s2=num;
            mx2=s2;
            r--;
            if (str[0]=='Q')
            {
                if (l<=r) mx=query(l,r,1,n,1);
                if (l-1!=r+1) mx=max(mx,max(mx1,mx2));
                else mx=b-a+1;
                printf("%I64d\n",mx);
            }
            else
            {
                if (l<=r) update(l,r,2,1,n,1);
                if (l-1==r+1)
                    update(l-1,b-a+1,1,n,1);
                else
                {
                    if (mx1) update(l-1,mx1,1,n,1);
                    if (mx2) update(r+1,mx2,1,n,1);
                }
            }
        }
    }
    return 0;
}
