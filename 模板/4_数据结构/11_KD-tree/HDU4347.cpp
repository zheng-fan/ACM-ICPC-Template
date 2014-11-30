#define sqr(x) (x)*(x)
const int NV=50005,K=5;
//k为维数,n为点数,idx为当前比较的维度
int k,n,idx;
struct point
{
    int x[K];
    bool operator <(const point &u) const
    {
        return x[idx]<u.x[idx];
    }
} po[NV]; //输入的点
priority_queue<pair<double,point> >nq;
//线段树节点
point pt[NV<<2];
int son[NV<<2];
void build(int l,int r,int rt=1,int dep=0)
{
    if(l>r) return;
    son[rt]=r-l;
    son[rt<<1]=son[rt<<1|1]=-1;
    idx=dep%k;
    int mid=l+r>>1;
    nth_element(po+l,po+mid,po+r+1);
    pt[rt]=po[mid];
    build(l,mid-1,rt<<1,dep+1);
    build(mid+1,r,rt<<1|1,dep+1);
}
void query(point &p,int m,int rt=1,int dep=0)
{
    if(son[rt]==-1) return;
    pair<double,point> nd(0,pt[rt]);
    for(int i=0; i<k; i++) nd.first+=sqr(nd.second.x[i]-p.x[i]);
    int dim=dep%k,x=rt<<1,y=rt<<1|1,fg=0;
    if(p.x[dim]>=pt[rt].x[dim]) swap(x,y);
    if(~son[x]) query(p,m,x,dep+1);
    if(nq.size()<m) nq.push(nd),fg=1;
    else
    {
        if(nd.first<nq.top().first) nq.pop(),nq.push(nd);
        if(sqr(p.x[dim]-pt[rt].x[dim])<nq.top().first) fg=1;
    }
    if(~son[y]&&fg) query(p,m,y,dep+1);
}
int main()
{
    while(scanf("%d%d",&n,&k)!=EOF)
    {
        for(int i=1; i<=n; i++)
            for(int j=0; j<k; j++)
                scanf("%d",&po[i].x[j]);
        build(1,n);
        int t;
        scanf("%d",&t);
        while(t--)
        {
            point ask;
            for(int j=0; j<k; j++) scanf("%d",&ask.x[j]);
            int m;
            scanf("%d",&m);
            query(ask,m);
            printf("the closest %d points are:\n", m);
            point ans[20];
            int cnt=0;
            while(!nq.empty())
            {
                ans[++cnt]=nq.top().second;
                nq.pop();
            }
            for(int i=cnt; i>=1; i--)
                for(int j=0; j<k; j++)
                    printf("%d%c",ans[i].x[j]," \n"[j==k-1]);
        }
    }
    return 0;
}
