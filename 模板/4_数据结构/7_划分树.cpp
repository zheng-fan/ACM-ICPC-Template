const int NV=100005;
int a[NV],sum[20][NV],s[20][NV];
void build(int l,int r,int rt=0)
{
    int mid=l+r>>1;
    int ln=l,rn=mid+1;
    int x=a[mid];
    sum[rt][l]=0;
    int cnt=mid-l+1;
    for (int i=l;i<=r;i++)
        if (s[rt][i]<x) cnt--;
    for (int i=l; i<=r; i++)
    {
        if (i>l) sum[rt][i]=sum[rt][i-1];
        if (ln<=mid&&(s[rt][i]<x||s[rt][i]==x&&cnt-->0))
            s[rt+1][ln++]=s[rt][i],sum[rt][i]++;
        else s[rt+1][rn++]=s[rt][i];
    }
    if (l<mid) build(l,mid,rt+1);
    if (mid+1<r) build(mid+1,r,rt+1);
}
int query(int k,int L,int R,int l,int r,int rt=0)
{
    if (l==r) return s[rt][l];
    int mid=l+r>>1;
    int lsum=0;
    if (L>l) lsum=sum[rt][L-1];
    int t=sum[rt][R]-lsum;
    if (t>=k) return query(k,l+lsum,l+sum[rt][R]-1,l,mid,rt+1);
    else return query(k-t,mid+1+L-l-lsum,mid+1+R-l-sum[rt][R],mid+1,r,rt+1);
}
void init(int n)
{
    for (int i=0; i<20; i++) sum[i][0]=0;
    for (int i=1; i<=n; i++) s[0][i]=a[i];
    sort(a+1,a+n+1);
    build(1,n);
}