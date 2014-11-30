long long qsum(long long q,long long n)
{
    n++;
    long long ans=0,temp=1;
    while(n>0)
    {
        if (n&1)
            ans=((ans*q)%M+temp%M)%M;
        temp=(temp*(1+q))%M;
        q=(q*q)%M;
        n>>=1;
    }
    return ans;
}

mat qsum(mat q,long long n)
{
    n++;
    mat unit=q.unit();
    mat ans(q.n,q.m),temp=unit;
    ans.init();
    while(n>0)
    {
        if (n&1) ans=ans*q+temp;
        temp=temp*(unit+q);
        q=q*q;
        n>>=1;
    }
    return ans;
}
