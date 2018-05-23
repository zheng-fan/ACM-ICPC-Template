#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
#include<climits>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<deque>
#include<list>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<numeric>
#include<iomanip>
#include<bitset>
#include<sstream>
#include<fstream>
#define debug puts("-----")
#define pi (acos(-1.0))
#define eps (1e-8)
#define inf (1<<30)
#define INF (1ll<<62)
using namespace std;
inline double sqr(const double &x)
{
    return x * x;
}
inline int sgn(const double &x)
{
    return x < -eps ? -1 : x > eps;
}
struct point
{
    double x, y;
    point(const double &x = 0, const double &y = 0): x(x), y(y) {}
    friend point operator + (const point &a, const point &b)
    {
        return point(a.x + b.x, a.y + b.y);
    }
    friend point operator - (const point &a, const point &b)
    {
        return point(a.x - b.x, a.y - b.y);
    }
    friend point operator * (const point &a, const double &b)
    {
        return point(a.x * b, a.y * b);
    }
    friend point operator * (const double &a, const point &b)
    {
        return point(a * b.x, a * b.y);
    }
    friend point operator / (const point &a, const double &b)
    {
        return point(a.x / b, a.y / b);
    }
    friend bool operator == (const point &a, const point &b)
    {
        return !sgn(a.x - b.x) && !sgn(a.y - b.y);
    }
    friend bool operator < (const point &a, const point &b)
    {
        return sgn(a.x - b.x) < 0 || (sgn(a.x - b.x) == 0 && sgn(a.y - b.y) < 0);
    }
    double norm()
    {
        return sqrt(sqr(x) + sqr(y));
    }
    friend double det(const point &a, const point &b)
    {
        return a.x * b.y - a.y * b.x;
    }
    friend double dot(const point &a, const point &b)
    {
        return a.x * b.x + a.y * b.y;
    }
    friend double dist(const point &a, const point &b)
    {
        return (a - b).norm();
    }
    double arg()
    {
        return atan2(y, x);
//        double res = atan2(y, x);   //(-pi, pi]
//        if(res < -pi / 2 + eps) res += 2 * pi; //eps修正精度
//        return res;
    }
    //逆时针旋转angle弧度
    point rotate(const double &angle)
    {
        return rotate(cos(angle), sin(angle));
    }
    point rotate(const point &p, const double &angle)
    {
        return (*this-p).rotate(angle)+p;
    }
    point rotate(const double &cosa, const double &sina)
    {
        return point(x * cosa - y * sina, x * sina + y * cosa);
    }
    int in()
    {
        return scanf("%lf %lf", &x, &y);
    }
    void out()
    {
        printf("%.2f %.2f\n", x, y);
    }
};

struct line
{
    point s, t;
    line(const point &s = point(), const point &t = point()): s(s), t(t) {}
    point vec() const
    {
        return t - s;
    }
    double norm() const
    {
        return vec().norm();
    }
    //点在直线上
    bool ispointonline(const point &p) const
    {
        return sgn(det(p - s, t - s)) == 0;
    }
    //点在线段上
    bool ispointonseg(const point &p) const
    {
        return ispointonline(p) && sgn(dot(p - s, p - t)) <= 0;
    }
    //点在线段上不含端点
    bool ispointonsegex(const point &p)
    {
        return ispointonline(p) && sgn(dot(p - s, p - t)) < 0;
    }
    //点到直线的垂足
    point pointprojline(const point &p)
    {
        return s + vec() * ((dot(p - s, vec()) / norm()) / (norm()));
    }
    //点到直线的距离
    double pointdistline(const point &p)
    {
        return fabs(det(p - s, vec()) / norm());
    }
    //点到线段的距离
    double pointdistseg(const point &p)
    {
        if (sgn(dot(p - s, t - s)) < 0) return (p - s).norm();
        if (sgn(dot(p - t, s - t)) < 0) return (p - t).norm();
        return pointdistline(p);
    }
    //判断两直线是否平行
    friend bool parallel(const line &l1, const line &l2)
    {
        return !sgn(det(l1.vec(), l2.vec()));
    }
    //判断两个点是否在直线的同一侧
    friend bool sameside(const line &l, const point &a, const point &b)
    {
        return sgn(det(b - l.s, l.vec())) * sgn(det(a - l.s, l.vec())) > 0;
    }
    //两直线的交点
    friend point linexline(const line &l1, const line &l2) //利用相似三角形对应边成比例
    {
        double s1 = det(l1.s - l2.s, l2.vec());
        double s2 = det(l1.t - l2.s, l2.vec());
        return (l1.t * s1 - l1.s * s2) / (s1 - s2);
    }
    //判断线段交
    friend bool issegxseg(const line &l1, const line &l2)
    {
        if(!sgn(det(l2.s - l1.s, l1.vec())) && !sgn(det(l2.t - l1.s, l1.vec())))
        {
            return l1.ispointonseg(l2.s) ||
                   l1.ispointonseg(l2.t) ||
                   l2.ispointonseg(l1.s) ||
                   l2.ispointonseg(l1.t);
        }
        return !sameside(l1, l2.s, l2.t) && !sameside(l2, l1.s, l1.t);
    }
    //直线沿法线方向移动d距离
    friend line move(const line &l, const double &d)
    {
        point t = l.vec();
        t = t / t.norm();
        t = t.rotate(pi / 2);
        return line(l.s + t * d, l.t + t * d);
    }
    int in()
    {
        s.in();
        return t.in();
    }
    void out()
    {
        s.out(), t.out();
    }
};

// ***多边形点的顺序可能会引发正负号问题***
struct polygon
{
#define next(i) ((i+1)%n)
    int n;
    vector<point> p;
    polygon(int n = 0): n(n)
    {
        p.resize(n);
    }
//    polygon(vector<point> &v):p(v){}
    //多边形周长
    double perimeter()
    {
        double sum = 0;
        for (int i = 0; i < n; i++)
            sum += (p[next(i)] - p[i]).norm();
        return sum;
    }
    //多边形面积
    double area()
    {
        double sum = 0;
        for (int i = 0; i < n; i++)
            sum += det(p[i], p[next(i)]);
        return sum / 2 + eps/10.0; //用sgn判断面积是否为0，所以只+eps/10.0
    }
    //判断点与多边形的位置关系，0外, 1内,2边上
    int pointin(const point &t)
    {
        int num = 0;
        for (int i = 0; i < n; i++)
        {
            if (line(p[i], p[next(i)]).ispointonseg(t))
                return 2;
            int k = sgn(det(p[next(i)] - p[i], t - p[i]));
            int d1 = sgn(p[i].y - t.y);
            int d2 = sgn(p[next(i)].y - t.y);
            if (k > 0 && d1 <= 0 && d2 > 0) num++;
            if (k < 0 && d2 <= 0 && d1 > 0) num--;
        }
        return num != 0;
    }
    //多边形重心
    point masscenter()
    {
        point ans;
        if (sgn(area()) == 0) return ans;
        for (int i = 0; i < n; i++)
            ans = ans + (p[i] + p[next(i)]) * det(p[i], p[next(i)]);
        return ans / area() / 6 + point(eps,eps); //要加eps吗？
    }
    //多边形边界上格点的数量
    int borderpointnum()
    {
        int num = 0;
        for (int i = 0; i < n; i++)
        {
            int a = fabs(p[next(i)].x - p[i].x);
            int b = fabs(p[next(i)].y - p[i].y);
            num += __gcd(a, b);
        }
        return num;
    }
    //多边形内格点数量
    int insidepointnum()
    {
        return int(area()) + 1 - borderpointnum() / 2;
    }
    void in()
    {
        for (int i = 0; i < n; i++)
            p[i].in();
    }
    void out()
    {
        for (int i = 0; i < n; i++)
            p[i].out();
    }
};

struct convex : public polygon
{
    convex(int n = 0): polygon(n) {}
//    convex(vector<point> &v):polygon(v){}
    //需要先求凸包，若凸包每条边除端点外都有点，则可唯一确定凸包
    bool isunique(vector<point> &v)
    {
        if (sgn(area()) == 0)
            return 0;
        for (int i = 0; i < n; i++)
        {
            line l(p[i], p[next(i)]);
            bool flag = 0;
            for (int j = 0; j < v.size(); j++)
                if (l.ispointonsegex(v[j]))
                {
                    flag = 1;
                    break;
                }
            if (!flag)
                return 0;
        }
        return 1;
    }
    //O(n)时间内判断点是否在凸包内
    bool containon(const point &a)
    {
        int sign = 0;
        for (int i = 0; i < n; i++)
        {
            int x = sgn(det(p[i] - a, p[next(i)] - a));
            if (x)
            {
                if (sign)
                {
                    if (sign != x)
                        return 0;
                }
                else
                    sign = x;
            }
        }
        return 1;
    }
    //O(logn)时间内判断点是否在凸包内
    bool containologn(const point &a)
    {
        point g = (p[0] + p[n / 3] + p[2 * n / 3]) / 3.0;
        int l = 0, r = n;
        while(l + 1 < r)
        {
            int m = (l + r) / 2;
            if (sgn(det(p[l] - g, p[m] - g)) > 0)
            {
                if (sgn(det(p[l] - g, a - g)) >= 0 && sgn(det(p[m] - g, a - g)) < 0)
                    r = m;
                else
                    l = m;
            }
            else
            {
                if (sgn(det(p[l] - g, a - g)) < 0 && sgn(det(p[m] - g, a - g)) >= 0)
                    l = m;
                else
                    r = m;
            }
        }
        return sgn(det(p[r % n] - a, p[l] - a)) - 1;
    }
    //最远点对（直径）
    int first, second; //最远的两个点对应标号
    double diameter()
    {
        double mx = 0;
        if (n == 1)
        {
            first = second = 0;
            return mx;
        }
        for (int i = 0, j = 1; i < n; i++)
        {
            while(sgn(det(p[next(i)] - p[i], p[j] - p[i]) -
                      det(p[next(i)] - p[i], p[next(j)] - p[i])) < 0)
                j = next(j);
            double d = dist(p[i], p[j]);
            if (d > mx)
            {
                mx = d;
                first = i;
                second = j;
            }
            d = dist(p[next(i)], p[next(j)]);
            if (d > mx)
            {
                mx = d;
                first = next(i);
                second = next(j);
            }
        }
        return mx;
    }
    //凸包是否与直线有交点O(log(n)), 需要On的预处理, 适合判断与直线集是否有交点
    vector<double> ang; //角度
    bool isinitangle;
    int finda(const double &x)
    {
        return upper_bound(ang.begin(), ang.end(), x) - ang.begin();
    }
    double getangle(const point &p) //获取向量角度[0, 2pi]
    {
        double res = atan2(p.y, p.x);   //(-pi, pi]
//        if (res < 0) res += 2 * pi; //为何不可以
        if(res < -pi / 2 + eps) res += 2 * pi; //eps修正精度
        return res;
    }
    void initangle()
    {
        for(int i = 0; i < n; i++)
            ang.push_back(getangle(p[next(i)] - p[i]));
        isinitangle = 1;
    }
    bool isxline(const line &l)
    {
        if(!isinitangle) initangle();
        int i = finda(getangle(l.t - l.s));
        int j = finda(getangle(l.s - l.t));
        if(sgn(det(l.t - l.s, p[i] - l.s) * det(l.t - l.s, p[j] - l.s) >= 0)) //可以不写sgn，不过还是先这样吧，不改了
            return 0;
        return 1;
    }
};
convex convexhull(vector<point> &a)
{
    //从一个vector获取凸包（逆时针）
    convex res(2 * a.size() + 5); //考虑退化的情况，全部共线，最多会有n+n-2+1个点（左端点和中间点各重复计算一次）
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int m = 0;
    for (int i = 0; i < a.size(); i++) //求下凸包
    {
        //<=0则不含边界，<0则含边界。注意，这里和下面两个循环都要改。
        while(m > 1 && sgn(det(res.p[m - 1] - res.p[m - 2], a[i] - res.p[m - 2])) <= 0) //所有不符合的都出栈
            m--;
        res.p[m++] = a[i];
    }
    int k = m;
    for (int i = a.size() - 2; i >= 0; i--) //求上凸包
    {
        //<=0则不含边界，<0则含边界。注意，这里和上面两个循环都要改。
        while(m > k && sgn(det(res.p[m - 1] - res.p[m - 2], a[i] - res.p[m - 2])) <= 0) //所有不符合的都出栈
            m--;
        res.p[m++] = a[i];
    }
    if (m > 1) m--; //起点重复计算了
    res.p.resize(m);
    res.n = m;
    return res;
}

struct halfplane: public line
{
    //ax+by+c<=0
    double a, b, c;
    //s->t的左侧表示半平面
    halfplane(const point &s = point(), const point &t = point()): line(s, t)
    {
        a = t.y - s.y;
        b = s.x - t.x;
        c = det(t, s);
    }
    halfplane(double a, double b, double c): a(a), b(b), c(c)
    {
        if (sgn(a)==0) s=point(0,-c/b);
        else s=point(-c/a,0);
        t=s+point(-b,a);
    }
    //求点p带入直线方程的值
    double calc(const point &p) const
    {
        return p.x * a + p.y * b + c;
    }
    //好像跟linexline一样，那个是4个点计算。这个是用abc与两点进行计算
    friend point halfxline(const halfplane &h, const line &l)
    {
        point res;
        double t1 = h.calc(l.s), t2 = h.calc(l.t);
        res.x = (t2 * l.s.x - t1 * l.t.x) / (t2 - t1);
        res.y = (t2 * l.s.y - t1 * l.t.y) / (t2 - t1);
        return res;
    }
    //用abc进行计算 尚未测试
    friend point halfxhalf(const halfplane &h1, const halfplane&h2)
    {
        return point((h1.b * h2.c - h1.c * h2.b) / (h1.a * h2.b - h2.a * h1.b) + eps,
                     (h1.a * h2.c - h2.a * h1.c) / (h1.b * h2.a - h1.a * h2.b) + eps);
    }
    //凸多边形与半平面交(cut)
    friend convex halfxconvex(const halfplane &h, const convex &c)
    {
        convex res;
        for (int i = 0; i < c.n; i++)
        {
            if (h.calc(c.p[i]) < -eps)
                res.p.push_back(c.p[i]);
            else
            {
                int j = i - 1;
                if (j < 0) j = c.n - 1;
                if (h.calc(c.p[j]) < -eps)
                    res.p.push_back(halfxline(h, line(c.p[j], c.p[i])));
                j = i + 1;
                if (j == c.n) j = 0;
                if (h.calc(c.p[j]) < -eps)
                    res.p.push_back(halfxline(h, line(c.p[i], c.p[j])));
            }
        }
        res.n = res.p.size();
        return res;
    }
    //点在半平面内
    friend int satisfy(const point &p, const halfplane &h)
    {
        return sgn(det(p - h.s, h.t - h.s)) <= 0;
    }
    friend bool operator <(const halfplane &h1, const halfplane &h2)
    {
        int res = sgn(h1.vec().arg() - h2.vec().arg());
        return res == 0 ? satisfy(h1.s, h2) : res < 0;
    }
    //半平面交出的凸多边形
    friend convex halfx(vector<halfplane> &v)
    {
        sort(v.begin(), v.end());
        deque<halfplane> q;
        deque<point> ans;
        q.push_back(v[0]);
        for (int i = 1; i < v.size(); i++)
        {
            if (sgn(v[i].vec().arg() - v[i - 1].vec().arg()) == 0)
                continue;
            while(ans.size() > 0 && !satisfy(ans.back(), v[i]))
            {
                ans.pop_back();
                q.pop_back();
            }
            while(ans.size() > 0 && !satisfy(ans.front(), v[i]))
            {
                ans.pop_front();
                q.pop_front();
            }
            ans.push_back(linexline(q.back(), v[i]));
            q.push_back(v[i]);
        }
        while(ans.size() > 0 && !satisfy(ans.back(), q.front()))
        {
            ans.pop_back();
            q.pop_back();
        }
        while(ans.size() > 0 && !satisfy(ans.front(), q.back()))
        {
            ans.pop_front();
            q.pop_front();
        }
        ans.push_back(linexline(q.back(), q.front()));
        convex c(ans.size());
        int i = 0;
        for (deque<point>::iterator it = ans.begin(); it != ans.end(); it++, i++)
            c.p[i] = *it;
        return c;
    }
};
//多边形的核，逆时针
convex core(const polygon &a)
{
    convex res;
    res.p.push_back(point(-inf, -inf));
    res.p.push_back(point(inf, -inf));
    res.p.push_back(point(inf, inf));
    res.p.push_back(point(-inf, inf));
    res.n = 4;
    for (int i = 0; i < a.n; i++)
        res = halfxconvex(halfplane(a.p[i], a.p[(i + 1) % a.n]), res);
    return res;
}
//凸多边形交出的凸多边形
convex convexxconvex(convex &c1, convex &c2)
{
    vector<halfplane> h;
    for (int i = 0; i < c1.p.size(); i++)
        h.push_back(halfplane(c1.p[i], c1.p[(i + 1) % c1.p.size()]));
    for (int i = 0; i < c2.p.size(); i++)
        h.push_back(halfplane(c2.p[i], c2.p[(i + 1) % c2.p.size()]));
    return halfx(h);
}
double mysqrt(double n) //防止出现sqrt(-eps)的情况
{
    return sqrt(max(0.0, n));
}
struct circle
{
    point o;
    double r;
    circle(point o = point(), double r = 0): o(o), r(r) {}
    bool operator ==(const circle &c)
    {
        return o == c.o && !sgn(r - c.r);
    }
    double area()
    {
        return pi * r * r;
    }
    //圆与线段交 用参数方程表示直线：P=A+t*(B-A)，带入圆的方程求解t
    friend vector<point> cirxseg(const circle &c, const line &l)
    {
        double dx = l.t.x - l.s.x, dy = l.t.y - l.s.y;
        double A = dx * dx + dy * dy;
        double B = 2 * dx * (l.s.x - c.o.x) + 2 * dy * (l.s.y - c.o.y);
        double C = sqr(l.s.x - c.o.x) + sqr(l.s.y - c.o.y) - sqr(c.r);
        double delta = B * B - 4 * A * C;
        vector<point> res;
        if(sgn(delta) >= 0) //or delta > -eps ?
        {
            //可能需要注意delta接近-eps的情况，所以使用mysqrt
            double w1 = (-B - mysqrt(delta)) / (2 * A);
            double w2 = (-B + mysqrt(delta)) / (2 * A);
            if(sgn(w1 - 1) <= 0 && sgn(w1) >= 0)
                res.push_back(l.s + w1 * (l.t - l.s));
            if(sgn(w2 - 1) <= 0 && sgn(w2) >= 0)
                res.push_back(l.s + w2 * (l.t - l.s));
        }
        return res;
    }
    //圆与直线交
    friend vector<point> cirxline(const circle &c, const line &l)
    {
        double dx = l.t.x - l.s.x, dy = l.t.y - l.s.y;
        double A = dx * dx + dy * dy;
        double B = 2 * dx * (l.s.x - c.o.x) + 2 * dy * (l.s.y - c.o.y);
        double C = sqr(l.s.x - c.o.x) + sqr(l.s.y - c.o.y) - sqr(c.r);
        double delta = B * B - 4 * A * C;
        vector<point> res;
        if(sgn(delta) >= 0) //or delta > -eps ?
        {
            double w1 = (-B - mysqrt(delta)) / (2 * A);
            double w2 = (-B + mysqrt(delta)) / (2 * A);
            res.push_back(l.s + w1 * (l.t - l.s));
            res.push_back(l.s + w2 * (l.t - l.s));
        }
        return res;
    }
    //扇形面积 a->b
    double sectorarea(const point &a, const point &b) const
    {
        double theta = atan2(a.y, a.x) - atan2(b.y, b.x);
        while (theta < 0) theta += 2 * pi;
        while (theta > 2 * pi) theta -= 2 * pi;
        theta = min(theta, 2 * pi - theta);
        return sgn(det(a, b)) * theta * r * r / 2.0; //此处上海交大的板子有误，已修正
    }
    //与线段AB的交点计算面积 a->b
    double calcarea(const point &a, const point &b) const
    {
        vector<point> p = cirxseg(*this, line(a, b));
        bool ina = sgn((a - o).norm() - r) < 0;
        bool inb = sgn((b - o).norm() - r) < 0;
        if (ina)
        {
            if (inb) return det(a - o, b - o) / 2;
            else return det(a - o, p[0] - o) / 2 + sectorarea(p[0] - o, b - o);
        }
        else
        {
            if (inb) return det(p[0] - o, b - o) / 2 + sectorarea(a - o, p[0] - o);
            else
            {
                if (p.size() == 2)
                    return sectorarea(a - o, p[0] - o) + sectorarea(p[1] - o, b - o)
                           + det(p[0] - o, p[1] - o) / 2;
                else
                    return sectorarea(a - o, b - o);
            }
        }
    }
    //圆与多边形交，结果可以尝试+eps，要注意多边形点的顺序可能会引发正负号问题
    friend double cirxpolygon(const circle &c, const polygon &a)
    {
        int n = a.p.size();
        double ans = 0;
        for(int i = 0; i < n; i++)
        {
            if(sgn(det(a.p[i] - c.o, a.p[next(i)] - c.o)) == 0)
                continue;
            ans += c.calcarea(a.p[i], a.p[next(i)]);
        }
        return ans;
    }
    //点在圆内，不包含边界
    bool pointin(const point &p)
    {
        return sgn((p - o).norm() - r) < 0;
    }
};
//三点求圆
circle getcircle3(const point &p0, const point &p1, const point &p2)
{
    double a1 = p1.x - p0.x, b1 = p1.y - p0.y, c1 = (a1 * a1 + b1 * b1) / 2;
    double a2 = p2.x - p0.x, b2 = p2.y - p0.y, c2 = (a2 * a2 + b2 * b2) / 2;
    double d = a1 * b2 - a2 * b1;
    point o(p0.x + (c1 * b2 - c2 * b1) / d, p0.y + (a1 * c2 - a2 * c1) / d);
    return circle(o, (o - p0).norm());
}
//直径上两点求圆
circle getcircle2(const point &p0, const point &p1)
{
    point o((p0.x + p1.x) / 2, (p0.y + p1.y) / 2);
    return circle(o, (o - p0).norm());
}
//最小圆覆盖 用之前可以随机化random_shuffle
circle mincircover(vector<point> &a)
{
    int n = a.size();
    circle c(a[0], 0);
    for (int i = 1; i < n; i++)
        if (!c.pointin(a[i]))
        {
            c.o = a[i];
            c.r = 0;
            for (int j = 0; j < i; j++)
                if (!c.pointin(a[j]))
                {
                    c = getcircle2(a[i], a[j]);
                    for (int k = 0; k < j; k++)
                        if (!c.pointin(a[k]))
                            c = getcircle3(a[i], a[j], a[k]);
                }
        }
    return c;
}
int main()
{
    return 0;
}
