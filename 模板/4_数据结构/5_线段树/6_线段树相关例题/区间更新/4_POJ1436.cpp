#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int NV = 8005;
int stt[NV<<3];
bool a[NV][NV];
void PushDown(int rt,int m)
{
    if (stt[rt])
    {
        stt[rt<<1] = stt[rt];
        stt[rt<<1|1] = stt[rt];
        stt[rt] = 0;
    }
}
void build(int l,int r,int rt=1)
{
    stt[rt] = 0;
    if (l == r)
    {
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
}
void update(int L,int R,int c,int l,int r,int rt=1)
{
    if (L <= l && r <= R)
    {
        stt[rt] = c;
        return ;
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , c , lson);
    if (m < R) update(L , R , c , rson);
}
void query(int L,int R,int c,int l,int r,int rt=1)
{
    if (stt[rt])
    {
        a[stt[rt]][c]=1;
        return;
    }
    if (l == r)
    {
        return;
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) query(L , R , c , lson);
    if (m < R) query(L , R , c , rson);
}
struct node
{
    int x,y1,y2;
} q[NV];
bool cmp(node a,node b)
{
    return a.x<b.x;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for (int i=1; i<=n; i++)
        {
            scanf("%d%d%d",&q[i].y1,&q[i].y2,&q[i].x);
            q[i].y1*=2;
            q[i].y1++;
            q[i].y2*=2;
            q[i].y2++;
        }
        sort(q+1,q+1+n,cmp);
        build(1,16001);
        memset(a,0,sizeof(a));
        for (int i=1; i<=n; i++)
        {
            query(q[i].y1,q[i].y2,i,1,16001);
            update(q[i].y1,q[i].y2,i,1,16001);
        }
        int ans=0;
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++)
                if (a[i][j])
                    for (int k=1; k<=n; k++)
                        ans+=a[i][k]&&a[j][k];
        printf("%d\n",ans);
    }
    return 0;
}
