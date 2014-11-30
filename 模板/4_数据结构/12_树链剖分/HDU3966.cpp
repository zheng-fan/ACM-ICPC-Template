const int NV=50005;
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
int add[NV<<2],sum[NV<<2];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void PushDown(int rt,int m)
{
    if (add[rt])
    {
        add[rt<<1] += add[rt];
        add[rt<<1|1] += add[rt];
        sum[rt<<1] += add[rt] * (m - (m >> 1));
        sum[rt<<1|1] += add[rt] * (m >> 1);
        add[rt] = 0;
    }
}
void build(int l,int r,int rt=1)
{
    add[rt] = 0;
    if (l == r)
    {
        sum[rt]=num[rank[l]];
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void update(int L,int R,int c,int l,int r,int rt=1)
{
    if (L <= l && r <= R)
    {
        add[rt] += c;
        sum[rt] += c * (r - l + 1);
        return ;
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , c , lson);
    if (m < R) update(L , R , c , rson);
    PushUp(rt);
}
int query(int L,int l,int r,int rt=1)
{
    if (L == l && l == r)
    {
        return sum[rt];
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) return query(L , lson);
    return query(L , rson);
}
void change(int x,int y,int l,int r,int c)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        update(w[top[x]],w[x],c,l,r);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    update(w[x],w[y],c,l,r);
}
void init(int n)
{
    memset(he,-1,sizeof(he));
    memset(son,-1,sizeof(son));
    tot=0;
    ecnt=0;
    for(int i=1; i<=n; i++)
        scanf("%d",&num[i]);
    for(int i=1; i<n; i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        adde(u,v);
    }
    dfs1(1,0,0);
    dfs2(1,1);
    build(1,n);
}
int main()
{
    int n,q;
    while(~scanf("%d%*d%d",&n,&q))
    {
        init(n);
        while(q--)
        {
            int a,b,c;
            char op[5];
            scanf("%s",op);
            if(op[0]=='Q')
            {
                scanf("%d",&a);
                printf("%d\n",query(w[a],1,n));
            }
            else
            {
                scanf("%d%d%d",&a,&b,&c);
                if(op[0]=='D') c=-c;
                change(a,b,1,n,c);
            }
        }
    }
    return 0;
}
