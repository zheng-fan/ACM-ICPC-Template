double simpson(double a,double b)
{
    double c = a + (b-a)/2;
    return (f(a)+4*f(c)+f(b))*(b-a)/6;
}
double asr(double a,double b,double epss,double A)
{
    double c = a+(b-a)/2;
    double L = simpson(a,c), R = simpson(c,b);
    if (fabs(L+R-A) <= 15*epss) return L+R+(L+R-A)/15;
    return asr(a,c,epss/2,L) + asr(c,b,epss/2,R);
}
double solve(double l,double r)
{
    return asr(l,r,eps,simpson(l,r));
}
