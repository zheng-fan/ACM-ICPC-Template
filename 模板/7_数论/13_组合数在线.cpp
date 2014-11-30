const int fcnt=100005;
const long long M=1000000007;
long long fac[fcnt];
void getfac()
{
    fac[0]=1;
    for (int i=1; i<fcnt; i++)
        fac[i]=fac[i-1]*i%M;
}
long long C(long long n,long long m)
{
    if (n<m)
        return 0;
    return fac[n]*inv(fac[m])%M*inv(fac[n-m])%M;
}
