int main()
{
    int t[500][500];
    int n;
    while(cin>>n)
    {
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++)
                scanf("%d",&t[i][j]);
        int a[500][500]= {};
        int mx=0;
        for (int i=1; i<=n; i++)
        {
            for (int j=1; j<=n; j++)
                a[i][j]+=t[i][j]+a[i-1][j];
            for (int j=1; j<=i; j++)
            {
                int sum=0;
                for (int k=1; k<=n; k++)
                {
                    if (sum<0)
                        sum=a[i][k]-a[j-1][k];
                    else
                        sum+=a[i][k]-a[j-1][k];
                    mx=max(mx,sum);
                }
            }
        }
        printf("%d\n",mx);
    }
    return 0;
}
