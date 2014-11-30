const int MAXN=100005;
// 分治算法求最近点对
struct point
{
    double x,y;
};
point p[MAXN];
int index[MAXN];  //保存筛选的坐标点的索引
int cmpx(const point &a,const point &b)
{
    return a.x<b.x;
}
int cmpy(int a,int b)  //这里用的是下标索引
{
    return p[a].y<p[b].y;
}
inline double dis(point &a , point &b)
{
    return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}
inline double min(double a , double b)
{
    return a<b?a:b;
}
double closest(int low , int high)
{
    if(low+1==high)
        return dis(p[low],p[high]);
    if(low+2==high)
        return min( dis(p[low],p[high]) , min(dis(p[low],p[low+1]),dis(p[low+1],p[high])) );
    int mid = (low + high)>>1;//求中点
    double ans = min( closest(low,mid),closest(mid+1,high) );  //分治法进行递归求解
    int cnt = 0;
    for(int i=low; i<=high; i++) //把x坐标在p[mid].x-ans~p[mid].x+ans范围内的点取出来
    {
        if(p[i].x >= p[mid].x - ans && p[i].x <= p[mid].x + ans)
            index[cnt++]=i;     //保存的是下标索引
    }
    sort(index,index+cnt,cmpy);   //按y坐标进行升序排序
    for(int i=0; i<cnt; i++)
        for(int j=i+1; j<cnt; j++)
        {
            if(p[index[j]].y - p[index[i]].y >= ans)   //注意下标索引
                break;
            ans = min( ans,dis(p[index[i]],p[index[j]]) );
        }
    return ans;
}
void init(int n)
{
    for (int i=0; i<n; i++)
        scanf("%lf%lf",&p[i].x,&p[i].y);
    sort(p,p+n,cmpx);
    return;
}
int main()
{
    int n;
    while(cin>>n,n!=0)
    {
        init(n);
        printf("%.2lf\n",closest(0,n-1)/2);
    }
    return 0;
}
