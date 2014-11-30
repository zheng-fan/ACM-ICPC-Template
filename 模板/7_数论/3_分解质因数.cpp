int a[1000000]= {},pcnt=0;
void pdec(int n)
{
    int x=sqrt(n);
    for (int i=1; prime[i]<=x; i++)
        if (n%prime[i]==0)
        {
            a[++pcnt]=prime[i];
            n/=prime[i];
            i--;
        }
    if (n!=1)
        a[++pcnt]=n;
}
