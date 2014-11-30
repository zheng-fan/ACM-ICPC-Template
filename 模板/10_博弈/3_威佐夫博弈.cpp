int wzf(int n, int m)
{
    if(n > m)
        swap(n, m);
    int k = m-n;
    int a = (k * (1.0 + sqrt(5.0))/2.0);
    if(a == n)
        return 0;
    else
        return 1;
}
int main()
{
    int a,b;
    while(scanf("%d%d",&a,&b),a|b)
    {
        if (wzf(a,b))
        {
            puts("1");
            if(a>b)
                swap(a,b);
            //第一种
            int k=b-a;
            double q=(1+sqrt(5.0))/2;
            int ak=k*q;
            //特殊情况
            if(a==0)
                puts("0 0");
            //同时减
            if(a>=ak)
                printf("%d %d\n",ak,ak+k);
            for (int i=1; i<=b; i++)
            {
                //b减一点
                if(a==(int)(i*q)&&b>a+i)
                    printf("%d %d\n",a,a+i);
                //b减很多
                if(a==(int)(i*q)+i)
                    printf("%d %d\n",a-i,a);
                //a减一点
                if(b==(int)(i*q)+i&&b-i<a)
                    printf("%d %d\n",b-i,b);
            }
            //第二种
            //同时减
            for(int i=a-1,j=b-1; i>=0,j>=0; i--,j--)
                if(wzf(i,j)==0)
                {
                    cout<<i<<' '<<j<<endl;
                    break;
                }
            //a减一点
            for(int i=a-1; i>=0; i--)
                if(wzf(i,b)==0)
                {
                    cout<<i<<' '<<b<<endl;
                    break;
                }
            for(int i=b-1; i>=0; i--)
                if(wzf(i,a)==0)
                {
                    //b减很多
                    if (i<a)
                        cout<<i<<' '<<a<<endl;
                    //b减一点
                    else
                        cout<<a<<' '<<i<<endl;
                }

        }
        else
            puts("0");
    }
    return 0;
}
