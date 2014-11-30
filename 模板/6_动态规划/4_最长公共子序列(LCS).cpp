const int LEN=1005;
int dp[LEN][LEN],res;
int a[LEN],b[LEN];
int n,m;
int lcs()
{
    memset(dp,0,sizeof(dp));
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
            if (a[i]==b[j]) dp[i][j]=dp[i-1][j-1]+1;
            else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
    return res=dp[n][m];
}
int ans[LEN];
void getans()
{
    int num=res;
    for (int i=n,j=m; i>=1&&j>=1;)
        if (a[i]==b[j])
        {
            ans[num--]=a[i];
            i--;
            j--;
        }
        else
        {
            if (dp[i-1][j]>dp[i][j-1]) i--;
            else j--;
        }
}
