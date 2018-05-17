const int NV=300005;
struct point
{
    double x, y;
    void in()
    {
        scanf("%lf%lf",&x,&y);
    }
} p[NV],py[NV];
int pyidx[NV];
bool cmpX(const point &p1,const point &p2)
{
    return p1.x<p2.x;
}
bool cmpY(const point &p1,const point &p2)
{
    return p1.y<p2.y;
}
double dis(const point &p1,const point &p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double ClosestPair(int l,int r) //[l, r]
{
    if (r-l+1<=3) sort(py+l,py+r+1,cmpY);
    if (r-l+1==2) return dis(p[l],p[r]);
    if (r-l+1==3) return min(dis(p[l],p[r]),min(dis(p[l],p[l+1]),dis(p[l+1],p[r])));
    int m=l+r>>1;
    double delta=min(ClosestPair(l,m),ClosestPair(m+1,r)); //\delta=\min(\delta_1,\delta_2)
    inplace_merge(py+l,py+m+1,py+r+1,cmpY); //利用归并排序的思想合并得到按y有序的序列
    int cnt=0;
    for (int i=l; i<=r; i++) //把所有x坐标在p[m].x的[-delta, delta]的点取出来
    {
        if(p[m].x-delta<=py[i].x&&py[i].x<=p[m].x+delta)
            pyidx[cnt++]=i;
    }
    for(int i=0; i<cnt; i++)
        for(int j=i+1; j<cnt; j++)
        {
            if(py[pyidx[j]].y-py[pyidx[i]].y>=delta) break; //最多寻找6个点后一定会break
            delta=min(delta,dis(py[pyidx[i]],py[pyidx[j]]));
        }
    return delta;
}
void init(int n)
{
    for (int i=0; i<n; i++) p[i].in();
    sort(p,p+n,cmpX);
    for (int i=0; i<n; i++) py[i]=p[i];
}
int main()
{
    int n;
    cin>>n;
    init(n); //input and presort
    printf("%.2f\n",ClosestPair(0,n-1));
    return 0;
}
