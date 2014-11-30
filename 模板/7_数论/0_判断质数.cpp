int isprime(long long n)
{
    if (n==1)
        return 0;
    long long x=sqrt(n);
    for (int i=2; i<=x; i++)
        if (n%i==0)
            return 0;
    return 1;
}
