int N;
const int NV=500005;
int c[NV];
inline int lowbit(int t)
{
    return t&(-t);
}
void update(int x,int v)
{
    while(x<=N)
    {
        c[x]+=v;
        x+=lowbit(x);
    }
}
int query(int x)
{
    int ans=0;
    while(x>0)
    {
        ans+=c[x];
        x-=lowbit(x);
    }
    return ans;
}
int findkth(int k)
{
    int idx = 0;
    for(int i=20; i>=0; i--)
    {
        idx |= 1 << i;
        if(idx <= N && c[idx] < k)
            k -= c[idx];
        else idx ^= 1 << i;
    }
    return idx + 1;
}
