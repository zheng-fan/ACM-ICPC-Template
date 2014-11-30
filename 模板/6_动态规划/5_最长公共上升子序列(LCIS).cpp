const int LEN=1005;
int dp[LEN][LEN],path[LEN][LEN],res;
int a[LEN],b[LEN];
int n,m,ai,aj;
int lcis()
{
    memset(dp,0,sizeof(dp));
    res=0;
    for (int i=1; i<=n; i++)
    {
        int mx=0,t;
        for (int j=1; j<=m; j++)
        {
            dp[i][j]=dp[i-1][j];
            path[i][j]=-1;
            if (a[i]>b[j]&&mx<dp[i-1][j]) mx=dp[i-1][j],t=j;
            if (a[i]==b[j]) dp[i][j]=mx+1,path[i][j]=t;
            if(res<dp[i][j])
            {
                res=dp[i][j];
                ai=i;
                aj=j;
            }
        }
    }
    return res;
}
int ans[LEN];
void getans()
{
    int num=res;
    while(num)
    {
        if (path[ai][aj]!=-1)
        {
            ans[num--]=b[aj];
            aj=path[ai][aj];
        }
        ai--;
    }
}
