typedef long long mytype;
const int SZ=105;
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
long long inv(long long a)
{
    return quickpow(a,M-2);
}
struct mat
{
    int n,m;
    mytype a[SZ][SZ];
    void init()
    {
        memset(a,0,sizeof(a));
    }
    mat(int n=SZ,int m=SZ):n(n),m(m) {}
    mat unit()
    {
        mat t(n,n);
        t.init();
        for (int i=0; i<n; i++)
            t.a[i][i]=1;
        return t;
    }
    mytype *operator [](int n)
    {
        return *(a+n);
    }
    mat operator +(const mat &b)
    {
        mat t(n,m);
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                t.a[i][j]=(a[i][j]+b.a[i][j]+M)%M;
        return t;
    }
    mat operator -(const mat &b)
    {
        mat t(n,m);
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                t.a[i][j]=(a[i][j]-b.a[i][j]+M)%M;
        return t;
    }
    mat operator *(const mat &b)
    {
        mat t(n,b.m);
        for(int i=0; i<n; i++)
            for(int j=0; j<b.m; j++)
            {
                t.a[i][j]=0;
                for(int k=0; k<m; k++)
                    t.a[i][j]=(t.a[i][j]+(a[i][k]*b.a[k][j])%M)%M;
            }
        return t;
    }
    mat operator *(const mytype &b)
    {
        mat t(n,m);
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                t.a[i][j]=a[i][j]*b%M;
        return t;
    }
    mat operator /(const mytype &b)
    {
        mat t(n,m);
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                t.a[i][j]=a[i][j]*inv(b)%M;
        return t;
    }
    mat operator !()
    {
        mat t(m,n);
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
                t.a[i][j]=a[j][i];
        return t;
    }
    mytype det()
    {
    }
    mat invm(mat &a)
    {
    }
    friend mat quickpow(mat a, mytype b)
    {
        if(b<0) return a.unit();
        mat ret=a.unit();
        for (; b; b>>=1,a=a*a)
            if (b&1)
                ret=ret*a;
        return ret;
    }
    void in()
    {
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                scanf("%lld",&a[i][j]);
    }
    void out()
    {
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                printf("%lld%c",a[i][j]," \n"[j==m-1]);
    }
};
