int N;
const int NV=500005;
long long c[NV],b[NV];
inline int lowbit(int t)
{
    return t&(-t);
}
void update(long long c[],int flag,int x,long long v)
{
    if (flag) for (int i=x; i<=N; i+=lowbit(i)) c[i]+=x*v;
    else for (int i=x; i>0; i-=lowbit(i)) c[i]+=v;
}
long long query(long long c[],int flag,int x)
{
    long long ans=0;
    if (flag) for (int i=x; i>0; i-=lowbit(i)) ans+=c[i];
    else for (int i=x; i<=N; i+=lowbit(i)) ans+=c[i];
    return ans;
}
void add(int l,int r,long long v)
{
    update(b,0,r,v);
    update(c,1,r,v);
    if (l>1)
    {
        update(b,0,l-1,-v);
        update(c,1,l-1,-v);
    }
}
long long sum(int x)
{
    if (x) return query(b,0,x)*x+query(c,1,x-1);
    else return 0;
}
long long sum(int l,int r)
{
    return sum(r)-sum(l-1);
}
