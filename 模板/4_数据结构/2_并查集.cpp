int f[LEN],rk[LEN];
int finds(int x) //非递归
{
    int k,j,r;
    r=x;
    while(r!=f[r])
        r=f[r];
    k=x;
    while(k!=r)
    {
        j=f[k];
        f[k]=r;
        k=j;
    }
    return r;
}
int finds(int x) //递归
{
    return f[x]==x?x:f[x]=finds(f[x]);
}
void uni(int a,int b)
{
    a=finds(a);
    b=finds(b);
    if (a==b) return;
    if (rk[a]>rk[b]) f[b]=a;
    else
    {
        if (rk[a]==rk[b]) rk[b]++;
        f[a]=b;
    }
}
void init(int n)
{
    memset(rk,0,sizeof(rk));
    for (int i=1; i<=n; i++)
        f[i]=i;
}
