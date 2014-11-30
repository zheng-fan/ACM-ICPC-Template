long long exgcd(long long a,long long b,long long &x,long long &y)
{
    if (b==0)
    {
        x=1;
        y=0;
        return a;
    }
    long long ans=exgcd(b,a%b,x,y);
    long long temp=x;
    x=y;
    y=temp-(a/b)*y;
    return ans;
}
