const int NV=1005;
int g[NV][NV];
int path[NV][NV];
void init(int n,int m)
{
    for (int i=1; i<=n; i++)
        for (int j=1; j<=n; j++)
        {
            g[i][j]=inf;
            if (i==j) g[i][j]=0;
        }
    for (int i=1; i<=m; i++)
    {
        int u,v,l;
        scanf("%d%d%d",&u,&v,&l);
        if (l<g[u][v]) g[u][v]=l;
        if (l<g[v][u]) g[v][u]=l;
    }
}
void floyd_warshall(int n)
{
    for (int k=1; k<=n; k++)
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++)
                if (g[i][k]!=inf&&g[k][j]!=inf&&g[i][k]+g[k][j]<g[i][j])
                    g[i][j]=g[i][k]+g[k][j],path[i][j]=path[i][k];
}
void out(int u,int v)
{
    int tmp=u;
    printf("%d",u);
    while(tmp!=v)
    {
        printf("-->%d",path[tmp][v]);
        tmp=path[tmp][v];
    }
}
