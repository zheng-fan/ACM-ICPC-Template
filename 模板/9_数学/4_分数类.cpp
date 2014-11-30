struct frac
{
    long long num,den;
    frac(long long num=0,long long den=1)
    {
        if (den<0) num=-num,den=-den;
        long long g=__gcd(abs(num),den);
        this->num=num/g;
        this->den=den/g;
    }
    frac operator +(const frac &o) const
    {
        return frac(num*o.den+den*o.num,den*o.den);
    }
    frac operator -(const frac &o) const
    {
        return frac(num*o.den-den*o.num,den*o.den);
    }
    frac operator *(const frac &o) const
    {
        return frac(num*o.num,den*o.den);
    }
    frac operator /(const frac &o) const
    {
        return frac(num*o.den,den*o.num);
    }
    bool operator <(const frac &o) const
    {
        return num*o.den<den*o.num;
    }
    bool operator ==(const frac &o) const
    {
        return num*o.den==den*o.num;
    }
    void out()
    {
        printf("%lld/%lld",num,den);
    }
};
