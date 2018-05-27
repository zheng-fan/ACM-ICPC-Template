template<typename T> inline void RD(T &ret)
{
    char c;
    int sgn;
    while(c!='-'&&(c<'0'||c>'9'))
        c=getchar();
    sgn=(c=='-')?-1:1;
    ret=(c=='-')?0:(c-'0');
    while(c=getchar(),c>='0'&&c<='9')
        ret=ret*10+(c-'0');
    ret*=sgn;
}
struct point
{
    long long x,y;
    point(const long long &x = 0, const long long &y = 0): x(x), y(y) {}
    friend bool operator < (const point &a, const point &b)
    {
        return a.x-b.x<0||a.x-b.x==0&&a.y-b.y<0;
    }
};
int to_left(const point &a,const point &b,const point &t)
{
    long long res=(b.x-a.x)*(t.y-a.y)-(b.y-a.y)*(t.x-a.x);
    if (res>0) return 1;
    if (res==0) return 0;
    return -1;
}
const int NV=100005;
point u[NV],d[NV];
point ansu[NV],ansd[NV];
int cntu,cntd;
int vi,ei; //for judge
int getHalfConvexHullAndJudge(int n)
{
    sort(u+1,u+1+n);
    cntu=0;
    for (int i=1; i<=n; i++) //lowerhull of upper points
    {
        while(cntu>1&&to_left(ansu[cntu-1],ansu[cntu],u[i])<=0) cntu--;
        ansu[++cntu]=u[i];
    }
    sort(d+1,d+1+n);
    cntd=0;
    for (int i=1; i<=n; i++) //upperhull of lower points
    {
        while(cntd>1&&to_left(ansd[cntd-1],ansd[cntd],d[i])>=0) cntd--;
        ansd[++cntd]=d[i];
    }
    //judge convex hull intersection
    vi=ei=1;
    while(vi<=n&&ei<cntu)
    {
        if (d[vi].x<ansu[ei].x) vi++;
        else if (d[vi].x>ansu[ei+1].x) ei++;
        else
        {
            if (to_left(ansu[ei],ansu[ei+1],d[vi])==1) return 1;
            vi++;
        }
    }
    vi=ei=1;
    while(vi<=n&&ei<cntd)
    {
        if (u[vi].x<ansd[ei].x) vi++;
        else if (u[vi].x>ansd[ei+1].x) ei++;
        else
        {
            if (to_left(ansd[ei],ansd[ei+1],u[vi])==-1) return 1;
            vi++;
        }
    }
    return 0;
}
int main()
{
    setvbuf(stdin,new char[1<<20],_IOFBF,1<<20);
    setvbuf(stdout,new char[1<<20],_IOFBF,1<<20);
    int m;
    RD(m);
    while(m--)
    {
        int n;
        RD(n);
        for (int i=1; i<=n; i++)
        {
            int x,y1,y2;
            RD(x),RD(y1),RD(y2);
            if (y1>y2) swap(y1,y2);
            d[i]=point(x,y1);
            u[i]=point(x,y2);
        }
        if (getHalfConvexHullAndJudge(n)) putchar('N');
        else putchar('Y');
    }
    puts("");
    return 0;
}
