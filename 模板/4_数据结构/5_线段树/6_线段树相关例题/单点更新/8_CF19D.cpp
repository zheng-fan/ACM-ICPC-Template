#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int NV = 200005;
set<int> stt[NV];
int mx[NV<<2];
void PushUp(int rt)
{
    mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);
}
void build(int l,int r,int rt=1)
{
    if (l == r)
    {
        mx[rt]=-1;
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void add(int L,int c,int l,int r,int rt=1)
{
    if (l == r)
    {
        mx[rt] = max(mx[rt],c);
        stt[l].insert(c);
        return ;
    }
    int m = (l + r) >> 1;
    if (L <= m) add(L, c, lson);
    else add(L, c, rson);
    PushUp(rt);
}
void remove(int L,int c,int l,int r,int rt=1)
{
    if (l == r)
    {
        stt[l].erase(c);
        mx[rt]=stt[l].empty()?-1:*--stt[l].end();
        return ;
    }
    int m = (l + r) >> 1;
    if (L <= m) remove(L, c, lson);
    else remove(L, c, rson);
    PushUp(rt);
}
pair<int,int> find(int L,int c,int l,int r,int rt=1)
{
    if (mx[rt]<c||r<L) return make_pair(l,-1);
    if (l == r) return make_pair(l,*stt[l].lower_bound(c));
    int m = (l + r) >> 1;
    pair<int,int> p=find(L, c, lson);
    if (p.second!=-1) return p;
    else return find(L, c, rson);
}
int discrete(int data[],int n,int dis[],int index[])
{
    int sub[n+1];
    memcpy(sub,data,sizeof(sub));
    sort(sub+1,sub+n+1);
    int m=unique(sub+1,sub+n+1)-sub-1;
    for(int i=1; i<=n; i++)
    {
        dis[i]=lower_bound(sub+1,sub+m+1,data[i])-sub;
        index[dis[i]]=data[i];
    }
    return m;
}
int dis[NV],op[NV],x[NV],y[NV],index[NV];
int main()
{
    int n;
    cin>>n;
    for (int i=1; i<=n; i++)
    {
        char s[10];
        scanf("%s%d%d",s,&x[i],&y[i]);
        if (s[0]=='a') op[i]=1;
        else if (s[0]=='r') op[i]=2;
        else op[i]=3;
    }
    int m=discrete(x,n,dis,index);
    build(1,m);
    for (int i=1; i<=n; i++)
    {
        if (op[i]==1)
            add(dis[i],y[i],1,m);
        else if (op[i]==2)
            remove(dis[i],y[i],1,m);
        else
        {
            pair<int,int> p=find(dis[i]+1,y[i]+1,1,m);
            if (p.second==-1) puts("-1");
            else printf("%d %d\n",index[p.first],p.second);
        }
    }
    return 0;
}
