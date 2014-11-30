char a[50][15]= {"","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen","twenty"};
char b[50][15]= {"","ten","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
char c[50][15]= {"","thousand","million","billion"};
void gao(int n)
{
    int t=n/100,t1=n/10%10,t2=n%10,t3=n%100;
    if (t) printf("%s hundred",a[t]);
    if (t3)
    {
        if (t) printf(" and ");
        if (t3<=20) printf("%s",a[t3]);
        else
        {
            printf("%s",b[t3/10]);
            if (t2) printf("-%s",a[t2]);
        }
    }
}
int main()
{
    int n;
    while(scanf("%d",&n),n!=-1)
    {
        if (n==0)
        {
            puts("zero");
            continue;
        }
        int q[5];
        int x=-1;
        while(n) q[++x]=n%1000,n/=1000;
        for (int i=x; i>=0; i--)
            if (q[i])
            {
                gao(q[i]);
                if (i) printf(" %s",c[i]);
                int flag=0;
                for (int j=i-1;j>=0;j--)
                    if (q[j]) flag=1;
                if (flag) printf(", ");
            }
        puts("");
    }
    return 0;
}
