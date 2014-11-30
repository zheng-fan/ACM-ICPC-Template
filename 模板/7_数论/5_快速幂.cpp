const long long M=1000000007;
long long quickpow(long long a, long long b)
{
    if(b < 0) return 0;
    long long ret = 1;
    a %= M;
    for (; b; b >>= 1, a = (a * a) % M)
        if (b & 1)
            ret = (ret * a) % M;
    return ret;
}
