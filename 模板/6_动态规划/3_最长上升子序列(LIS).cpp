///O(n^2)
int dp[5000]= {};
dp[1]=1;
for (int i=2; i<=n; i++)
{
    int mx=0;
    for (int j=1; j<i; j++)
        if (a[j]<a[i])
            mx=max(mx,dp[j]);
    dp[i]=mx+1;
}
int mx=0;
for (int i=1; i<=n; i++)
    mx=max(mx,dp[i]);

///O(nlogn)
int dp[5000]= {};
dp[1]=a[1];
int ans=1;
for (int i=2; i<=n; i++)
{
    if (a[i]>=dp[ans]) dp[++ans]=a[i];
    else *lower_bound(dp+1,dp+ans+1,a[i])=a[i];
}
