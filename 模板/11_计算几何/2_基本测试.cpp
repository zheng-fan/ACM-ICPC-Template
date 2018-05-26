struct point
{
    long long x,y;
    point(const long long &x = 0, const long long &y = 0): x(x), y(y) {}
    friend bool operator < (const point &a, const point &b)
    {
        return a.x-b.x<0||a.x-b.x==0&&a.y-b.y<0;
    }
};
//to-Left-Test
int to_left(const point &a,const point &b,const point &t)
{
    long long res=(b.x-a.x)*(t.y-a.y)-(b.y-a.y)*(t.x-a.x);
    if (res>0) return 1;
    if (res==0) return 0;
    return -1;
}
//in-Circle-Test
double det3(double a11,double a12,double a13,double a21,double a22,double a23,double a31,double a32,double a33)
{
    return a11*(a22*a33-a32*a23)-a12*(a21*a33-a31*a23)+a13*(a21*a32-a31*a22);
}
int inCircle(const point &a,const point &b,const point &c,const point &p)
{
    double as=a.x*a.x+a.y*a.y;
    double bs=b.x*b.x+b.y*b.y;
    double cs=c.x*c.x+c.y*c.y;
    double ps=p.x*p.x+p.y*p.y;
    double ans=a.x*det3(b.y,bs,1,c.y,cs,1,p.y,ps,1)
               -a.y*det3(b.x,bs,1,c.x,cs,1,p.x,ps,1)
               +as*det3(b.x,b.y,1,c.x,c.y,1,p.x,p.y,1)
               -det3(b.x,b.y,bs,c.x,c.y,cs,p.x,p.y,ps);
    if (ans>0) return 1;
    if (ans==0) return 0;
    return -1;
}
//in-Triangle-Test
int inTriangle(const point &a,const point &b,const point &c,const point &p)
{
    int l1=to_left(a,b,p);
    int l2=to_left(b,c,p);
    int l3=to_left(c,a,p);
    if (l1==0||l2==0||l3==0) return 0;
    return l1==l2&&l2==l3?1:-1;
}
