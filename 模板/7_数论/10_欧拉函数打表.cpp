const int MAXN=10005;
long long phi[MAXN];
void getphi()
{
    for (int i=1; i<MAXN; i++)
        phi[i]=i;
    for (int i=2; i<MAXN; i++)
        if (phi[i]==i)
            for (int j=i; j<MAXN; j+=i)
                phi[j]=phi[j]/i*(i-1);
}
