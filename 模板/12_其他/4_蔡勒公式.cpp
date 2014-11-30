int zeller(int y,int m,int d,int flag)
{
    if (m==1||m==2)
        y--,m+=12;
    int c=y/100;
    y%=100;
    int w=((c/4-2*c+y+y/4+13*(m+1)/5+d-1)%7+7)%7;
    if (flag) return (w+3)%7;
    return w;
}
