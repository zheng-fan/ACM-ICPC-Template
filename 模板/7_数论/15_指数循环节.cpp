long long phi(long long n)
{
    long long ans=n;
    long long x=sqrt(n);
    for (long long i=2; i<=x; i++)
    {
        if (n%i==0)
        {
            while(n%i==0)
                n/=i;
            ans=ans/i*(i-1);
        }
    }
    if (n>1)
        ans=ans/n*(n-1);
    return ans;
}
long long quickpow(long long a, long long b, long long c)
{
    if(b < 0) return 0;
    long long ret = 1;
    a %= c;
    for (; b; b >>= 1, a = (a * a) % c)
        if (b & 1)
            ret = (ret * a) % c;
    return ret;
}
long long solve(long long a[],int i,int n,long long c)
{
    if (i==n)
        return a[i]%c;
    long long p=phi(c);
    return quickpow(a[i],solve(a,i+1,n,p)%p+p,c);
}
int main()
{
    int m,n;
    int cas=0;
    while(scanf("%d%d",&m,&n)!=0)
    {
        long long a[50];
        for (int i=1; i<=n; i++)
            scanf("%lld",&a[i]);
        printf("Case #%d: %lld\n",++cas,solve(a,1,n,m));
    }
    return 0;
}
