int N;
int c[2005][2005];
inline int lowbit(int t)
{
    return t&(-t);
}
void update(int x,int y,int v)
{
    for (int i=x; i<=N; i+=lowbit(i))
        for (int j=y; j<=N; j+=lowbit(j))
            c[i][j]+=v;
}
int query(int x,int y)
{
    int s=0;
    for (int i=x; i>0; i-=lowbit(i))
        for (int j=y; j>0; j-=lowbit(j))
            s+=c[i][j];
    return s;
}
int sum(int x,int y,int xx,int yy)
{
    x--,y--;
    return query(xx,yy)-query(xx,y)-query(x,yy)+query(x,y);
}

int N;
long long c[130][130][130]= {};
inline int lowbit(int t)
{
    return t&(-t);
}
void update(int x,int y,int z,long long v)
{
    for (int i=x; i<=N; i+=lowbit(i))
        for (int j=y; j<=N; j+=lowbit(j))
            for (int k=z; k<=N; k+=lowbit(k))
                c[i][j][k]+=v;
}
long long query(int x,int y,int z)
{
    long long s=0;
    for (int i=x; i>0; i-=lowbit(i))
        for (int j=y; j>0; j-=lowbit(j))
            for (int k=z; k>0; k-=lowbit(k))
                s+=c[i][j][k];
    return s;
}
long long sum(int x,int y,int z,int xx,int yy,int zz)
{
    x--,y--,z--;
    return query(xx,yy,zz)
           -query(x,yy,zz)-query(xx,y,zz)-query(xx,yy,z)
           +query(x,y,zz)+query(xx,y,z)+query(x,yy,z)
           -query(x,y,z);
}
