void rotate(int &x,int &y,int &n,int &m,int t)
{
    t%=4;
    while(t--)
    {
        swap(x,y);
        y=n-y+1;
        swap(n,m);
    }
}

void rotate(int &x,int &y,int &n,int &m,int t)
{
    int a,b;
    if (t==1)
        a=y,b=n-x+1;
    if (t==2)
        a=n-x+1,b=m-y+1;
    if (t==3)
        a=m-y+1,b=x;
    if (t) x=a,y=b;
    if (t&&t!=2) swap(n,m);
}
