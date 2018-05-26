/*
 * 给定平面上一系列的点，对这些点构造一个 Delaunay 三角剖分，输出这个剖分中所有的边所对应的端点的标号的和
 * 若 {e1, e2, e3, … ,eh} 为构造出来的 Delaunay 三角剖分中的所有边，其中某条边 ek 的两个端点的标号分别为 ik, jk
 * 则输出(i1 + j1 + i2 + j2 + i3 + j3 + … + ih + jh) mod (h + 1)
 * 如果需要random_shuffle，则要在vertex中记录id号
 * **该结果适用于没有四点共圆的情况，因为共圆会导致有多个结果**
 */
//IO optimization
template<typename T>
inline void RD(T &ret)
{
    char c=getchar();
    int sgn;
    while(c!='-'&&(c<'0'||c>'9')) c=getchar();
    sgn=(c=='-')?-1:1;
    ret=(c=='-')?0:(c-'0');
    while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
    ret*=sgn;
}
//Point class
struct point
{
    long long x, y;
    point(long long x,long long y):x(x),y(y) {}
    point(const point &p):x(p.x),y(p.y) {}
    point() {}
    bool operator==(const point &p)
    {
        return x==p.x&&y==p.y;
    }
    void in()
    {
        RD(x),RD(y);
    }
    void out()
    {
        printf("%lld %lld\n",x,y);
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
const int NV=300005;
point P[NV]; //input data
//bucket
struct BUCKET
{
    int he[NV*(3+6*2)],ecnt,bucket[NV];
    struct edge
    {
        int v,next;
    } E[NV*(3+6*2)];
    void adde(int u,int v) //bucket_id(face_id), vertex_id
    {
        E[++ecnt].v=v;
        E[ecnt].next=he[u];
        he[u]=ecnt;
    }
    BUCKET():ecnt(0) {}
    void InitBucket(point p[],int n)
    {
        he[1]=-1;
        for (int i=1; i<=n; i++)
            adde(1,i),bucket[i]=1;
    }
    void Rebucket(int fa,int fb,int fc,int fp,const point &a,const point &b,const point &c,const point &p)
    {
        he[fa]=he[fb]=he[fc]=-1;
        for (int i=he[fp]; i!=-1; i=E[i].next)
            if (inTriangle(p,b,c,P[E[i].v])==1) adde(fa,E[i].v),bucket[E[i].v]=fa;
            else if (inTriangle(p,c,a,P[E[i].v])==1) adde(fb,E[i].v),bucket[E[i].v]=fb;
            else if (inTriangle(p,a,b,P[E[i].v])==1) adde(fc,E[i].v),bucket[E[i].v]=fc;
        //Three points collinear
            else if (!(P[E[i].v]==p)&&to_left(p,a,P[E[i].v])==0) adde(fb,E[i].v),bucket[E[i].v]=fb;
            else if (!(P[E[i].v]==p)&&to_left(p,b,P[E[i].v])==0) adde(fc,E[i].v),bucket[E[i].v]=fc;
            else if (!(P[E[i].v]==p)&&to_left(p,c,P[E[i].v])==0) adde(fa,E[i].v),bucket[E[i].v]=fa;
    }
    void RebucketForEdgeFlip(int fa,int fb,int fc,int fd,const point &a,const point &b,const point &c,const point &d)
    {
        he[fc]=he[fd]=-1;
        for (int i=he[fa]; i!=-1; i=E[i].next)
            if (inTriangle(a,b,c,P[E[i].v])==1) adde(fc,E[i].v),bucket[E[i].v]=fc;
            else if (inTriangle(a,b,d,P[E[i].v])==1) adde(fd,E[i].v),bucket[E[i].v]=fd;
        //Three points collinear
            else if (to_left(a,b,P[E[i].v])==0) adde(fc,E[i].v),bucket[E[i].v]=fc;
        for (int i=he[fb]; i!=-1; i=E[i].next)
            if (inTriangle(a,b,c,P[E[i].v])==1) adde(fc,E[i].v),bucket[E[i].v]=fc;
            else if (inTriangle(a,b,d,P[E[i].v])==1) adde(fd,E[i].v),bucket[E[i].v]=fd;
        //Three points collinear
            else if (to_left(a,b,P[E[i].v])==0) adde(fc,E[i].v),bucket[E[i].v]=fc;
    }
} bucket;
//DCEL
long long ans=0;
int cnt=0;
struct DCEL
{
    struct edge
    {
        int twin,ori,inc,pred,succ;
        edge(int twin,int ori,int inc,int pred,int succ):twin(twin),ori(ori),inc(inc),pred(pred),succ(succ) {}
        edge() {}
    };
    struct vertex
    {
        int inc;
        point p;
        vertex(int inc,const point &p):inc(inc),p(p) {}
        vertex() {}
    };
    struct face
    {
        int inc;
        face(int inc):inc(inc) {}
        face() {}
    };
    edge e[NV*2*(3+6)]; //3 in triangle, 6 edge flip
    vertex v[NV];
    face f[NV*(3+6*2)]; //3 in triangle, 6 edge flip
    int ecnt,vcnt,fcnt;
    DCEL():ecnt(0),vcnt(0),fcnt(0) {}
    //init DCEL with 3 points (-inf,-inf) (inf,-inf) (0,inf)
    void InitDCEL()
    {
        point a(-inf,-inf);
        point b(inf,-inf);
        point c(0,inf);
        e[ecnt++]=edge(3,0,1,2,1); //0 for oustside face
        e[ecnt++]=edge(4,1,1,0,2); //1 for inner face
        e[ecnt++]=edge(5,2,1,1,0);
        e[ecnt++]=edge(0,1,0,4,5);
        e[ecnt++]=edge(1,2,0,5,3);
        e[ecnt++]=edge(2,0,0,3,4);
        v[vcnt++]=vertex(0,a);
        v[vcnt++]=vertex(1,b);
        v[vcnt++]=vertex(2,c);
        f[fcnt++]=face(3);
        f[fcnt++]=face(0);
    }
    void InsertPoint(int x)
    {
        int fp=bucket.bucket[x];
        int fa=fcnt++;
        int fb=fcnt++;
        int fc=fcnt++;
        int ea1=ecnt++;
        int ea2=ecnt++;
        int eb1=ecnt++;
        int eb2=ecnt++;
        int ec1=ecnt++;
        int ec2=ecnt++;
        int vp=vcnt++;
        int ec0=f[fp].inc;
        int ea0=e[f[fp].inc].succ;
        int eb0=e[e[f[fp].inc].succ].succ;
        int va0=e[ec0].ori;
        int vb0=e[ea0].ori;
        int vc0=e[eb0].ori;
        bucket.Rebucket(fa,fb,fc,fp,v[va0].p,v[vb0].p,v[vc0].p,P[x]);
        //old e
        e[ea0].inc=fa;
        e[eb0].inc=fb;
        e[ec0].inc=fc;
        e[ea0].pred=eb2;
        e[ea0].succ=ec1;
        e[eb0].pred=ec2;
        e[eb0].succ=ea1;
        e[ec0].pred=ea2;
        e[ec0].succ=eb1;
        //new v, e, f
        v[vp]=vertex(ea2,P[x]);
        f[fa]=face(ea0);
        f[fb]=face(eb0);
        f[fc]=face(ec0);
        e[ea1]=edge(ea2,va0,fb,eb0,ec2);
        e[ea2]=edge(ea1,vp,fc,eb1,ec0);
        e[eb1]=edge(eb2,vb0,fc,ec0,ea2);
        e[eb2]=edge(eb1,vp,fa,ec1,ea0);
        e[ec1]=edge(ec2,vc0,fa,ea0,eb2);
        e[ec2]=edge(ec1,vp,fb,ea1,eb0);
        //get ans
        if (vp>=3&&va0>=3)
        {
            cnt++;
            ans+=vp+va0-4;
        }
        if (vp>=3&&vb0>=3)
        {
            cnt++;
            ans+=vp+vb0-4;
        }
        if (vp>=3&&vc0>=3)
        {
            cnt++;
            ans+=vp+vc0-4;
        }
        //edge flip
        queue<int> q;
        q.push(ea0),q.push(eb0),q.push(ec0);
        while(!q.empty())
        {
            int e0=q.front();
            q.pop();
            if (e[e[e0].twin].inc==0) continue; //outside
            int ea0_ef=e[e0].pred;
            int eb0_ef=e[e[e0].twin].pred;
            int ec0_ef=e[eb0_ef].pred;
            int ed0_ef=e[ea0_ef].pred;
            int va_ef=e[ea0_ef].ori;
            int vb_ef=e[eb0_ef].ori;
            int vc_ef=e[ec0_ef].ori;
            int vd_ef=e[ed0_ef].ori;
            if (inCircle(v[va_ef].p,v[vc_ef].p,v[vd_ef].p,v[vb_ef].p)==1) //b is not inf point & b in circle(a,c,d)
            {
                int fc_ef=fcnt++;
                int fd_ef=fcnt++;
                int fa_ef=e[e0].inc;
                int fb_ef=e[e[e0].twin].inc;
                int ec_ef=ecnt++;
                int ed_ef=ecnt++;
                bucket.RebucketForEdgeFlip(fa_ef,fb_ef,fc_ef,fd_ef,v[va_ef].p,v[vb_ef].p,v[vc_ef].p,v[vd_ef].p);
                //old e
                e[ea0_ef].inc=fc_ef;
                e[ec0_ef].inc=fc_ef;
                e[eb0_ef].inc=fd_ef;
                e[ed0_ef].inc=fd_ef;
                e[ea0_ef].pred=ec_ef;
                e[ea0_ef].succ=ec0_ef;
                e[eb0_ef].pred=ed_ef;
                e[eb0_ef].succ=ed0_ef;
                e[ec0_ef].pred=ea0_ef;
                e[ec0_ef].succ=ec_ef;
                e[ed0_ef].pred=eb0_ef;
                e[ed0_ef].succ=ed_ef;
                //new e, f
                f[fc_ef]=face(ec_ef);
                f[fd_ef]=face(ed_ef);
                e[ec_ef]=edge(ed_ef,vb_ef,fc_ef,ec0_ef,ea0_ef);
                e[ed_ef]=edge(ec_ef,va_ef,fd_ef,ed0_ef,eb0_ef);
                //push edge
                q.push(eb0_ef),q.push(ec0_ef);
                //get ans
                if (vc_ef>=3&&vd_ef>=3)
                {
                    cnt--;
                    ans-=vc_ef+vd_ef-4;
                }
                if (va_ef>=3&&vb_ef>=3)
                {
                    cnt++;
                    ans+=va_ef+vb_ef-4;
                }
            }
        }
    }
} dcel;
int main()
{
    int n;
    RD(n);
    for (int i=1; i<=n; i++) P[i].in();
//    random_shuffle(P+1,P+n+1);
    dcel.InitDCEL();
    bucket.InitBucket(P,n);
    for (int i=1; i<=n; i++) dcel.InsertPoint(i);
    cout<<ans%(cnt+1)<<endl;
    return 0;
}
