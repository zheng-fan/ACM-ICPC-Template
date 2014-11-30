const int NN=1005;
const int NM=1005;
unsigned long long hash[NN][NM],pw1[NM],pw2[NN],seed1=131,seed2=1313;
void init(char s[][NM],int n,int m)
{
    int mx=max(n,m);
    pw1[0]=pw2[0]=1;
    for (int i=1; i<=m; i++)
        pw1[i]=pw1[i-1]*seed1;
    for (int i=1; i<=n; i++)
        pw2[i]=pw2[i-1]*seed2;
    hash[0][1]=hash[1][0]=hash[0][0]=0;
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=m; j++)
            hash[i][j] = hash[i][j-1] * seed1 + s[i][j];
        for (int j=1; j<=m; j++)
            hash[i][j] = hash[i-1][j] * seed2 + hash[i][j];
    }
}
unsigned long long query(int x,int y,int xx,int yy,int n,int m)
{
    if (x<1||x>n||xx<1||x>n||y<1||y>m||yy<1||yy>m||x>xx||y>yy)
        return 0;
    unsigned long long t1,t2;
    t1=hash[xx][y-1]-hash[x-1][y-1]*pw2[xx-x+1];
    t2=hash[xx][yy]-hash[x-1][yy]*pw2[xx-x+1];
    return t2-t1*pw1[yy-y+1];
}
