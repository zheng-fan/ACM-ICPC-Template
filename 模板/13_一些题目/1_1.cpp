const int maxn=100010;
const int maxnode=8000010;

int lc[maxnode],rc[maxnode],num[maxnode],cnt;

int ins(int old,int pos,int l,int r,int k)
{
    int mid;
    int n=++cnt,t=n;
    num[n]=num[old]+k;
    lc[n]=lc[old],rc[n]=rc[old];

    while(l<r)
    {
        mid=(l+r)/2;
        if(pos<=mid)
            lc[n]=++cnt,n=lc[n],old=lc[old],r=mid;
        else
            rc[n]=++cnt,n=rc[n],old=rc[old],l=mid+1;
        num[n]=num[old]+k,lc[n]=lc[old],rc[n]=rc[old];
    }
    return t;
}
int build(int l,int r)
{
    int mid=(l+r)/2,n=++cnt;
    num[n]=0;

    if(l==r)
        return n;
    lc[n]=build(l,mid);
    rc[n]=build(mid+1,r);
    return n;
}

int get(int l,int r,int *a,int numa,int *b,int numb,int k)
{
    int t=0,i,tt=0;
    for(i=0; i<numa; i++)
        t+=num[rc[a[i]]],tt+=num[a[i]];
    for(i=0; i<numb; i++)
        t-=num[rc[b[i]]],tt-=num[b[i]];
    if(tt<k)
        return -1;
    if(l==r)
        return l;
    if(t>=k)
    {
        for(i=0; i<numa; i++)
            a[i]=rc[a[i]];
        for(i=0; i<numb; i++)
            b[i]=rc[b[i]];
        return get((l+r)/2+1,r,a,numa,b,numb,k);
    }
    for(i=0; i<numa; i++)
        a[i]=lc[a[i]];
    for(i=0; i<numb; i++)
        b[i]=lc[b[i]];
    return get(l,(l+r)/2,a,numa,b,numb,k-t);
}
int root[maxn],c[maxn];

int a[1100],numa,b[1100],numb;
int lft[maxn],rht[maxn];
void gao(int n,int is)
{
    if(is)
    {
        a[numa++]=root[n];
        n=lft[n];
        while(n)
            a[numa++]=c[n],n-=n&(-n);
    }
    else
    {
        b[numb++]=root[n];
        n=lft[n];
        while(n)
            b[numb++]=c[n],n-=n&(-n);
    }
}

vector<pair<int,int> >V[maxn];
int lca[maxn],fa[maxn],w[maxn],first[maxn],nxt[maxn<<1],vv[maxn<<1],M,tim;
int f[maxn],vis[maxn];

int fin(int n)
{
    if(n==fa[n])
        return n;
    return fa[n]=fin(fa[n]);
}
void dfs(int n)
{
    root[n]=ins(root[f[n]],w[n],1,M,1);
    lft[n]=++tim;
    fa[n]=n;

    for(int e=first[n]; e; e=nxt[e])if(vv[e]-f[n])
            f[vv[e]]=n,dfs(vv[e]),fa[vv[e]]=n;
    vis[n]=1;
    rht[n]=tim;

    for(int i=0; i<V[n].size(); i++)if(vis[V[n][i].first])
        {
            int v=V[n][i].first;
            lca[V[n][i].second]=fin(v);
        }
}
int A[maxn],B[maxn],C[maxn],wa[maxn<<1];
int N;

void upd(int n,int pos,int k)
{
    while(n<=N)
        c[n]=ins(c[n],pos,1,M,k),n+=n&(-n);
}
int main()
{
    int n,q,i,j;

    cin>>n>>q;
    for(i=1; i<=n; i++)
        scanf("%d",&w[i]),wa[i]=w[i];
    N=n;
    M=n;
    int e=2;

    for(i=1; i<n; i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        nxt[e]=first[u],vv[e]=v,first[u]=e++;
        nxt[e]=first[v],vv[e]=u,first[v]=e++;
    }
    for(i=1; i<=q; i++)
    {
        scanf("%d%d%d",&A[i],&B[i],&C[i]);
        if(A[i])
            V[B[i]].push_back(make_pair(C[i],i)),V[C[i]].push_back(make_pair(B[i],i));
        else
            wa[++M]=C[i];
    }
    sort(wa+1,wa+1+M);
    M=unique(wa+1,wa+1+M)-wa-1;
    for(i=1; i<=n; i++)
        w[i]=lower_bound(wa+1,wa+1+M,w[i])-wa;
    root[0]=build(1,M);
    dfs((n+1)/2);
    for(i=1; i<=N; i++)
        c[i]=root[0];

    for(i=1; i<=q; i++)
    {
        if(A[i])
        {
            int u=B[i],v=C[i],l=lca[i];
            numa=numb=0;
            gao(u,1),gao(v,1),gao(l,0),gao(f[l],0);
            u=get(1,M,a,numa,b,numb,A[i]);
            if(u<0)
                puts("invalid request!");
            else
                printf("%d\n",wa[u]);
        }
        else
        {
            int u=B[i],v=C[i];
            v=lower_bound(wa+1,wa+1+M,v)-wa;
            upd(lft[u],w[u],-1);
            upd(rht[u]+1,w[u],1);
            upd(lft[u],v,1);
            upd(rht[u]+1,v,-1);
            w[u]=v;
        }
    }
}
