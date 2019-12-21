const int NV=100005;
//num为初始数组，rank只在为初始数组build时使用
int num[NV],siz[NV],top[NV],son[NV];
int dep[NV],w[NV],rank[NV],fa[NV];
int he[NV],to[2*NV],next[2*NV],ecnt,tot;
void adde(int u,int v)
{
    to[ecnt]=v,next[ecnt]=he[u],he[u]=ecnt++;
    to[ecnt]=u,next[ecnt]=he[v],he[v]=ecnt++;
}
void dfs1(int u,int father,int d)
{
    dep[u]=d;
    fa[u]=father;
    siz[u]=1;
    for(int i=he[u]; ~i; i=next[i])
    {
        int v=to[i];
        if(v!=father)
        {
            dfs1(v,u,d+1);
            siz[u]+=siz[v];
            if(son[u]==-1||siz[v]>siz[son[u]])
                son[u]=v;
        }
    }
}
void dfs2(int u,int tp)
{
    top[u]=tp;
    w[u]=++tot;
    rank[w[u]]=u;
    if(son[u]==-1) return;
    dfs2(son[u],tp);
    for(int i=he[u]; ~i; i=next[i])
    {
        int v=to[i];
        if(v!=son[u]&&v!=fa[u])
            dfs2(v,v);
    }
}
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
int sum[NV<<2];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt=1)
{
    if (l == r)
    {
        sum[rt]=num[l];
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void update(int L,int c,int l,int r,int rt=1)
{
    if (L == l && l == r)
    {
        sum[rt] = c;
        return ;
    }
    int m = (l + r) >> 1;
    if (L <= m) update(L, c, lson);
    else update(L, c, rson);
    PushUp(rt);
}
int query(int L,int R,int l,int r,int rt=1)
{
    if (L <= l && r <= R)
    {
        return sum[rt];
    }
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m) ret += query(L, R, lson);
    if (m < R) ret += query(L, R, rson);
    return ret;
}
int getsum(int x,int y,int l,int r)
{
    int ret=0;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        ret+=query(w[top[x]],w[x],l,r);
        x=fa[top[x]];
    }
    if (x==y) return ret; ///Notice! 防止产生son[x]为-1的情况
    if(dep[x]>dep[y]) swap(x,y);
    ret+=query(w[son[x]],w[y],l,r); ///Notice! 比点权多了个son
    return ret;
}
int uu[NV],vv[NV],ll[NV];
void init(int n)
{
    memset(he,-1,sizeof(he));
    memset(son,-1,sizeof(son));
    tot=0;
    ecnt=0;
    for(int i=1; i<n; i++)
    {
        scanf("%d%d%d",&uu[i],&vv[i],&ll[i]);
        adde(uu[i],vv[i]);
    }
    dfs1(1,0,0);
    dfs2(1,1);
    num[1]=0;
    for (int i=1; i<n; i++)
    {
        if (dep[uu[i]]<dep[vv[i]]) num[w[vv[i]]]=ll[i];
        else num[w[uu[i]]]=ll[i];
    }
    build(1,n);
}
int main()
{
    int n,q,s;
    while(~scanf("%d%d%d",&n,&q,&s))
    {
        init(n);
        while(q--)
        {
            int a,b;
            int op;
            scanf("%d",&op);
            if(op==0)
            {
                scanf("%d",&a);
                printf("%d\n",getsum(a,s,1,n));
                s=a;
            }
            else
            {
                scanf("%d%d",&a,&b);
                if (dep[uu[a]]<dep[vv[a]]) a=w[vv[a]];
                else a=w[uu[a]];
                update(a,b,1,n);
            }
        }
    }
    return 0;
}
