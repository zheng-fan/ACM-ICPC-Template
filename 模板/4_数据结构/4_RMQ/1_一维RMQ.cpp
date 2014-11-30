const int NV=50005;
const int NVB=20;
int mx[NVB][NV],mn[NVB][NV],a[NV];
void init(int data[],int n)
{
    int k=log2(n);
    for (int i=1; i<=n; i++)
        mx[0][i]=mn[0][i]=data[i];
    for (int i=1; i<=k; i++)
        for (int j=1; j+(1<<i)-1<=n; j++)
        {
            mx[i][j]=max(mx[i-1][j],mx[i-1][j+(1<<i>>1)]);
            mn[i][j]=min(mn[i-1][j],mn[i-1][j+(1<<i>>1)]);
        }
}
int query(int l,int r,int flag)
{
    int k=log2(r-l+1);
    if (flag) return max(mx[k][l],mx[k][r-(1<<k)+1]);
    else return min(mn[k][l],mn[k][r-(1<<k)+1]);
}
