/*
    Miller_Rabbin大素数测试
    (不能计算long * long)
    复杂度：O(logN) * 测试次数
*/
long long pow_mod(long long a, long long x, long long p)
{
    long long res = 1;
    while(x)
    {
        if (x & 1) res = res * a % p;
        x >>= 1;
        a = a * a % p;
    }
    return res;
}
bool test(long long n, long long a, long long d)
{
    if (n == 2) return true;
    if (n == a) return true;
    if ((n & 1) == 0) return false;
    while(!(d & 1)) d = d >> 1;
    long long t = pow_mod(a, d, n);
    while((d != n - 1) && (t != 1) && (t != n - 1))
    {
        t = t * t % n;
        d = d << 1;
    }
    return (t == n - 1 || (d & 1) == 1);
}
bool Miller_Rabbin(long long n)
{
    if (n < 2) return false;
    int a[] = {2, 7, 61};   //测试集
    for (int i = 0; i <= 2; i++)
        if (!test(n, a[i], n - 1)) return false;
    return true;
}


/*
    Miller_Rabbin 算法进行素数测试
    速度快，而且可以判断 <2^63的数
    复杂度：O(logN) * 测试次数 由于要处理long * long，所以略慢
*/
const int S = 20; //随机算法判定次数，S越大，判错概率越小

//计算 (a*b)%c.   a,b都是long long的数，直接相乘可能溢出的
//  a,b,c <2^63
long long mult_mod(long long a, long long b, long long c)
{
    a %= c;
    b %= c;
    long long ret = 0;
    while(b)
    {
        if(b & 1)
        {
            ret += a;
            ret %= c;
        }
        a <<= 1;
        if(a >= c)a %= c;
        b >>= 1;
    }
    return ret;
}

//计算  x^n %c
long long pow_mod(long long x, long long n, long long mod)   //x^n%c
{
    if(n == 1)return x % mod;
    x %= mod;
    long long tmp = x;
    long long ret = 1;
    while(n)
    {
        if(n & 1) ret = mult_mod(ret, tmp, mod);
        tmp = mult_mod(tmp, tmp, mod);
        n >>= 1;
    }
    return ret;
}

//以a为基,n-1=x*2^t      a^(n-1)=1(mod n)  验证n是不是合数
//一定是合数返回true,不一定返回false
bool check(long long a, long long n, long long x, long long t)
{
    long long ret = pow_mod(a, x, n);
    long long last = ret;
    for(int i = 1; i <= t; i++)
    {
        ret = mult_mod(ret, ret, n);
        if(ret == 1 && last != 1 && last != n - 1) return true; //合数
        last = ret;
    }
    if(ret != 1) return true;
    return false;
}

// Miller_Rabin()算法素数判定
//是素数返回true.(可能是伪素数，但概率极小)
//合数返回false;
bool Miller_Rabbin(long long n)
{
    if(n < 2)return false;
    if(n == 2)return true;
    if((n & 1) == 0) return false; //偶数
    long long x = n - 1;
    long long t = 0;
    while((x & 1) == 0)
    {
        x >>= 1;
        t++;
    }
    for(int i = 0; i < S; i++)
    {
        long long a = rand() % (n - 1) + 1;
        if(check(a, n, x, t))
            return false;//合数
    }
    return true;
}
