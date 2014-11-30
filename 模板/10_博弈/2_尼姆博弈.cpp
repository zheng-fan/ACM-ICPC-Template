int sg(int n,int numsg[])
{
    int ans = 0;
    for(int i=1; i <= n; i++)
        ans ^= numsg[i];
    if(ans == 0)
        printf("No\n");
    else
    {
        printf("Yes\n");
        for(int i = 1; i <= n; i++)
        {
            int x = ans ^ numsg[i];
            if(x < numsg[i])
                printf("%d %d\n", numsg[i], x);
        }
    }
}
