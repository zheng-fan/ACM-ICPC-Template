const int MAXN=105;
int a[MAXN][MAXN],b[MAXN];
void gauss(int n,int a[][MAXN],int b[])
{
    for (int i=1; i<=n; i++)
    {
        int k;
        for (int j=i; j<=n; j++)
            if (a[j][i])
            {
                k=j;
                break;
            }
        for (int j=1; j<=n; j++)
            swap(a[i][j],a[k][j]);
        swap(b[i],b[k]);
        for (int j=1; j<=n; j++)
            if (i!=j&&a[j][i])
            {
                for (k=1; k<=n; k++)
                    a[j][k]^=a[i][k];
                b[j]^=b[i];
            }
    }
}
