const int MAXN=105;
double a[MAXN][MAXN],b[MAXN]; ///要注意-0.000的情况 +eps
int gauss_elimination(int n,double a[][MAXN],double b[])
{
    int i,j,k,row;
    double mx,t;
    for(k=1; k<=n; k++)
    {
        for(mx=0,i=k; i<=n; i++)
            if (fabs(a[i][k])>fabs(mx))
                mx=a[row=i][k];
        if(fabs(mx)<eps)
            return 0;
        if(row!=k)
        {
            for(j=k; j<=n; j++)
                swap(a[k][j],a[row][j]);
            swap(b[k],b[row]);
        }
        for(j=k+1; j<=n; j++)
            for(a[k][j]/=mx,i=k+1; i<=n; i++)
                a[i][j]-=a[i][k]*a[k][j];
        for(b[k]/=mx,i=k+1; i<=n; i++)
            b[i]-=b[k]*a[i][k];
    }
    for(i=n; i>=1; i--)
        for(j=i+1; j<=n; j++)
            b[i]-=a[i][j]*b[j];
    return 1;
}
