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
