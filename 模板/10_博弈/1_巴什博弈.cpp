int bash(int n, int m)
{
    if(n%(m+1) != 0)
        return 1;
    else
        return 0;
}int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if (bash(n,m))
        {
            if (n>m)
                printf("%d",n%(m+1));
            else
            {
                printf("%d",n);
                for (int i=n+1; i<=m; i++)
                    printf(" %d",i);
            }
            puts("");
        }
        else
            puts("none");
    }
    return 0;
}
