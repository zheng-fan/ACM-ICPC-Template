const int NV=60005;
const int M=NV*40;
int N,m,tot;
int a[NV],T[NV],S[NV],use[NV];
int lson[M],rson[M],c[M];
int build(int l,int r)
{
    int rt = tot++;
    c[rt] = 0;
    if(l != r)
    {
        int mid = l+r>>1;
        lson[rt] = build(l,mid);
        rson[rt] = build(mid+1,r);
    }
    return rt;
}
int insert(int rt,int pos,int val)
{
    int nrt = tot++, tmp = nrt;
    int l = 1, r = m;
    c[nrt] = c[rt] + val;
    while(l < r)
    {
        int mid = l+r>>1;
        if(pos <= mid)
        {
            lson[nrt] = tot++;
            rson[nrt] = rson[rt];
            nrt = lson[nrt];
            rt = lson[rt];
            r = mid;
        }
        else
        {
            rson[nrt] = tot++;
            lson[nrt] = lson[rt];
            nrt = rson[nrt];
            rt = rson[rt];
            l = mid+1;
        }
        c[nrt] = c[rt] + val;
    }
    return tmp;
}
inline int lowbit(int x)
{
    return x&(-x);
}
int sum(int x)
{
    int ans = 0;
    while(x > 0)
    {
        ans += c[lson[use[x]]];
        x -= lowbit(x);
    }
    return ans;
}
void update(int x,int p,int d)
{
    while(x <= N)
    {
        S[x] = insert(S[x],p,d);
        x += lowbit(x);
    }
}
int query(int L,int R,int k)
{
    int lrt = T[L-1];
    int rrt = T[R];
    int l = 1, r = m;
    for(int i = L-1; i; i -= lowbit(i)) use[i] = S[i];
    for(int i = R; i ; i -= lowbit(i)) use[i] = S[i];
    while(l < r)
    {
        int mid = l+r>>1;
        int tmp = sum(R) - sum(L-1) + c[lson[rrt]] - c[lson[lrt]];
        if(tmp >= k)
        {
            r = mid;
            for(int i = L-1; i ; i -= lowbit(i))
                use[i] = lson[use[i]];
            for(int i = R; i; i -= lowbit(i))
                use[i] = lson[use[i]];
            lrt = lson[lrt];
            rrt = lson[rrt];
        }
        else
        {
            l = mid+1;
            k -= tmp;
            for(int i = L-1; i; i -= lowbit(i))
                use[i] = rson[use[i]];
            for(int i = R; i; i -= lowbit(i))
                use[i] = rson[use[i]];
            lrt = rson[lrt];
            rrt = rson[rrt];
        }
    }
    return l;
}
int op[NV],ql[NV],qr[NV],qk[NV],data[NV];
void inithash()
{
    sort(data+1,data+m+1);
    m=unique(data+1,data+m+1)-data;
}
int hash(int x)
{
    return lower_bound(data+1,data+m+1,x)-data;
}
void init(int n,int q)
{
    N=n;
    tot=0;
    m=0;
    for(int i = 1; i <= n; i++)
        scanf("%d",&a[i]),data[++m]=a[i];
    char s[10];
    for(int i = 1; i <= q; i++)
    {
        scanf("%s",s);
        if(s[0] == 'Q')
        {
            op[i]=0;
            scanf("%d%d%d",&ql[i],&qr[i],&qk[i]);
        }
        else
        {
            op[i]=1;
            scanf("%d%d",&ql[i],&data[++m]);
            qk[i]=data[m];
        }
    }
    inithash();
    T[0] = build(1,m);
    for(int i = 1; i <= n; i++)
        T[i] = insert(T[i-1],hash(a[i]),1);
    for(int i = 1; i <= n; i++)
        S[i] = T[0];
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,q;
        scanf("%d%d",&n,&q);
        init(n,q);
        for(int i = 1; i <= q; i++)
        {
            if(op[i])
            {
                update(ql[i],hash(a[ql[i]]),-1);
                update(ql[i],hash(qk[i]),1);
                a[ql[i]]=qk[i];
            }
            else printf("%d\n",data[query(ql[i],qr[i],qk[i])]);
        }
    }
    return 0;
}
