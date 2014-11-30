void crt()
{
    int t;
    while(cin>>t)
    {
        int flag=1;
        long long n1,a1;
        if (t) scanf("%lld%lld",&n1,&a1),t--;
        while(t--)
        {
            long long n2,a2,k1,k2;
            scanf("%lld%lld",&n2,&a2);
            if (flag==0)
                continue;
            long long d=exgcd(n1,n2,k1,k2);
            if ((a2-a1)%d!=0)
                flag=0;
            if (flag)
            {
                k1=(k1*(a2-a1)/d%(n2/d)+n2/d)%(n2/d);
                long long a=n1*k1+a1;
                long long n=n1/d*n2;
                n1=n;
                a1=a;
            }
        }
        if (flag) return a1;
        else return -1;
    }
}
