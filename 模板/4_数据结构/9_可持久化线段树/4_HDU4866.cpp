#define lson l,m
#define rson m+1,r
const int NV = 200005;
const int NN = NV*25;
int cnt[NN],ln[NN],rn[NN];
long long sum[NN];
int tot,root[NV];
void PushUp(int k)
{
    sum[k]=sum[ln[k]]+sum[rn[k]];
    cnt[k]=cnt[ln[k]]+cnt[rn[k]];
}
int build(int l,int r)
{
    int k=++tot;
    if (l == r)
    {
        sum[k]=0;
        cnt[k]=0;
        return k;
    }
    int m = (l + r) >> 1;
    ln[k]=build(lson);
    rn[k]=build(rson);
    PushUp(k);
    return k;
}
int M,data[NV];
int update(int o,int L,int c,int l,int r)
{
    int k=++tot;
    sum[k]=sum[o];
    cnt[k]=cnt[o];
    ln[k]=ln[o];
    rn[k]=rn[o];
    if (L == l && l == r)
    {
        sum[k]+=c*data[l];
        cnt[k]+=c;
        return k;
    }
    int m = (l + r) >> 1;
    if (L <= m) ln[k]=update(ln[o], L , c , lson);
    else rn[k]=update(rn[o], L , c , rson);
    PushUp(k);
    return k;
}
long long query(int a,int L,int l,int r)
{
    if (l==r) return (long long)data[l]*L; //注意不能是sum[a]
    int m = (l + r) >> 1;
    if (L <= cnt[ln[a]]) return query(ln[a], L , lson);
    return sum[ln[a]]+query(rn[a], L-cnt[ln[a]] , rson);
}
int inithash(int n)
{
    sort(data+1,data+n+1);
    return unique(data+1,data+n+1)-data-1;
}
int hash(int x)
{
    return lower_bound(data+1,data+M+1,x)-data;
}
struct node
{
    int d,x;
    node(int d=0,int x=0):d(d),x(x) {}
    int sgn() const
    {
        if (d>0) return 1;
        if (d==0) return 0;
        return -1;
    }
    bool operator <(const node &b) const
    {
        if (x!=b.x) return x<b.x;
        else if (sgn()!=b.sgn()) return sgn()>b.sgn();
        return abs(d)<abs(b.d);
    }
} a[NV];
int main()
{
    int n,m,x,P;
    while(~scanf("%d%d%d%d",&n,&m,&x,&P))
    {
        tot=0;
        for (int i=1; i<=n; i++)
        {
            int l,r;
            scanf("%d%d%d",&l,&r,&data[i]);
            a[i].d=data[i];
            a[i].x=l;
            //在r处加负的，但在排序时把负的的全排到最后
            //二分时，如果当前位置没有点，那么会找到x后面的一个位置
            //如果有很多点，肯定会找到正数后面的一个位置（下个x或当前x但为负的点）
            //最后位置减1即可
            a[i+n].d=-data[i];
            a[i+n].x=r;
        }
        sort(a+1,a+2*n+1);
        M=inithash(n);
        root[0]=build(1,M);
        for (int i=1; i<=2*n; i++)
        {
            int d=a[i].d;
            if (d>0) root[i]=update(root[i-1],hash(d),1,1,M);
            else root[i]=update(root[i-1],hash(-d),-1,1,M);
        }
        long long pre=1;
        while(m--)
        {
            int X,aa,bb,cc;
            scanf("%d%d%d%d",&X,&aa,&bb,&cc);
            int k=(aa%cc*pre%cc+bb)%cc;
            int p=lower_bound(a+1,a+2*n+1,node(0,X))-a-1;
            long long ans;
            if (k) ans=query(root[p],k,1,M);
            else ans=0;
            if (pre>P) ans*=2;
            pre=ans;
            printf("%I64d\n",ans);
        }
    }
    return 0;
}
