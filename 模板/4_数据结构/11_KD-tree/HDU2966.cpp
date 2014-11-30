const int NV=100005;
struct point
{
    int x, y;
    void in()
    {
        scanf("%d%d",&x,&y);
    }
} p[NV];
bool Div[NV];
bool cmpX(const point &p1,const point &p2)
{
    return p1.x<p2.x;
}
bool cmpY(const point &p1,const point &p2)
{
    return p1.y<p2.y;
}
long long dis(const point &p1,const point &p2)
{
    return (long long)(p1.x-p2.x)*(p1.x-p2.x)+(long long)(p1.y-p2.y)*(p1.y-p2.y);
}
void build(int l, int r, point p[])
{
    if (l > r) return;
    int mid = l + r >> 1;
    int minX, minY, maxX, maxY;
    minX = min_element(p + l, p + r + 1, cmpX)->x;
    minY = min_element(p + l, p + r + 1, cmpY)->y;
    maxX = max_element(p + l, p + r + 1, cmpX)->x;
    maxY = max_element(p + l, p + r + 1, cmpY)->y;
    Div[mid] = (maxX - minX >= maxY - minY);
    nth_element(p + l, p + mid, p + r + 1, Div[mid] ? cmpX : cmpY);
    build(l, mid - 1, p);
    build(mid + 1, r, p);
}
void find(long long &res, int l, int r, point &a, point p[])
{
    if (l > r)  return;
    int mid = l + r >> 1;
    long long dist = dis(a, p[mid]);
    if (dist > 0) ///NOTICE
        res = min(res, dist);
    long long d = Div[mid] ? (a.x - p[mid].x) : (a.y - p[mid].y);
    int l1, l2, r1, r2;
    l1 = l, l2 = mid + 1;
    r1 = mid - 1, r2 = r;
    if (d > 0) swap(l1, l2), swap(r1, r2);
    find(res, l1, r1, a, p);
    if (d * d < res) find(res, l2, r2, a, p);
}
long long find(int l,int r, point &a, point p[])
{
    long long res=INF;
    find(res,l,r,a,p);
    return res;
}
point pp[NV];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for (int i=1; i<=n; i++) p[i].in(),pp[i]=p[i];
        build(1,n,p);
        for (int i=1; i<=n; i++)
            printf("%I64d\n",find(1,n,pp[i],p));
    }
    return 0;
}
