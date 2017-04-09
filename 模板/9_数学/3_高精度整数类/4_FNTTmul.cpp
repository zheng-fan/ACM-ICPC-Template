///double型的精度有十进制的15位，在万进制下，要存储10000*10000*n以及计算中可能会产生精度问题，可以使用快速数论变换
long long epsilon[NV],repsilon[NV],buffera[NV],bufferb[NV],ffttemp[NV];
///p = r * 2^k + 1
///4179340454199820289 = 29 * 2^57 + 1, g = 3, 要保证fftmul处理后的n<2^k且10000*10000*n<p且M+M<2^63-1，这个数完全符合
const long long M=4179340454199820289ll;
///两个long long相乘要用快速乘
//long long quickmul(long long a, long long b)
//{
//    long long ret = 0;
//    for (; b; b >>= 1, a = (a << 1) % M)
//        if (b & 1)
//            ret = (ret + a) % M;
//    return ret;
//}
///下面这个神奇的做法暂时还没发现会出问题的地方，而且效率很高
long long quickmul(long long a,long long b)
{
    return (a*b-(long long)(a/(long double)M*b+1e-3)*M+M)%M;
}
long long quickpow(long long a, long long b)
{
    if(b < 0) return 0;
    long long ret = 1;
    a %= M;
    for (; b; b >>= 1, a = quickmul(a,a))
        if (b & 1)
            ret = quickmul(ret,a);
    return ret;
}
long long inv(long long a)
{
    return quickpow(a,M-2);
}
void init_epsilon(int n)
{
    epsilon[0]=repsilon[0]=1;
    long long gr=quickpow(3,(M-1)/n);
    for (int i=1; i<n; i++)
    {
        epsilon[i]=quickmul(epsilon[i-1],gr);
        repsilon[i]=inv(epsilon[i]);
    }
}
void fft(int n, long long *buffer, int offset, int step, long long *epsilon)
{
    if(n==1) return;
    int m=n>>1;
    fft(m,buffer,offset,step<<1,epsilon);
    fft(m,buffer,offset+step,step<<1,epsilon);
    for(int k=0; k<m; k++)
    {
        int pos=2*step*k;
        ffttemp[k]=(buffer[pos+offset]+quickmul(epsilon[k*step],buffer[pos+offset+step]))%M;
        ffttemp[k+m]=(buffer[pos+offset]-quickmul(epsilon[k*step],buffer[pos+offset+step])+M)%M;
    }
    for(int i=0; i<n; i++)
        buffer[i*step+offset]=ffttemp[i];
}
integer fftmul(const integer &a,const integer &b)
{
    ///high bit
    int n=max(a.d[0],b.d[0]);
    n=2*n-1;
    n|=n>>1;
    n|=n>>2;
    n|=n>>4;
    n|=n>>8;
    n|=n>>16;
    n++;
    init_epsilon(n);
    for (int i=0; i<n; i++) buffera[i]=a.d[i+1],bufferb[i]=b.d[i+1];
    fft(n,buffera,0,1,epsilon);
    fft(n,bufferb,0,1,epsilon);
    for (int i=0; i<n; i++) buffera[i]=quickmul(buffera[i],bufferb[i]);
    fft(n,buffera,0,1,repsilon);
    integer ans;
    ans.d[0]=0;
    long long invn=inv(n);
    long long intrem=0;
    for (int i=0; i<n; i++)
    {
        long long x=quickmul(buffera[i],invn)+intrem;
        ans.d[++ans.d[0]]=x%radix;
        intrem=x/radix;
    }
    while(ans.d[0]>1&&ans.d[ans.d[0]]==0) ans.d[0]--;
    return ans;
}
