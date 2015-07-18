const long long M=1000000007;
long long quickmul(long long a, long long b)
{
    long long ret = 0;
    for (; b; b >>= 1, a = (a << 1) % M)
        if (b & 1)
            ret = (ret + a) % M;
    return ret;
}

///What the fuck is this??!! It works!!
long long quickmul(long long a,long long b)
{
    return (a*b-(long long)(a/(long double)M*b+1e-3)*M+M)%M;
}
