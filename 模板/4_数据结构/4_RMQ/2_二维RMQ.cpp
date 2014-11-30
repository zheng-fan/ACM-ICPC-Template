const int NV=255;
const int NVB=20;
int mx[NVB][NV][NV],mn[NVB][NV][NV],a[NV][NV],mxt,mnt;
void init(int data[][NV],int n)
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            mx[0][i][j]=mn[0][i][j]=data[i][j];
    for(int k=1; (1<<k)<=n; k++)
        for(int i=1; i<=n; i++)
            for(int j=1; j+(1<<k)-1<=n; j++)
            {
                mx[k][i][j]=max(mx[k-1][i][j],mx[k-1][i][j+(1<<k>>1)]);
                mn[k][i][j]=min(mn[k-1][i][j],mn[k-1][i][j+(1<<k>>1)]);
            }
}
///行，列，矩阵宽度
void query(int row,int col,int b)
{
    int k=log2(b);
    mxt=-1;
    mnt=inf;
    int l=col,r=col+b-1;
    for(int i=row; i<row+b; i++)
    {
        mxt=max(mxt,max(mx[k][i][l],mx[k][i][r-(1<<k)+1]));
        mnt=min(mnt,min(mn[k][i][l],mn[k][i][r-(1<<k)+1]));
    }
}
int main()
{
    int n,b,q;
    while(scanf("%d%d%d",&n,&b,&q)!=EOF)
    {
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                scanf("%d",&a[i][j]);
        init(a,n);
        while(q--)
        {
            int r,c;
            scanf("%d%d",&r,&c);
            query(r,c,b);
            printf("%d\n",mxt-mnt);
        }
    }
    return 0;
}
