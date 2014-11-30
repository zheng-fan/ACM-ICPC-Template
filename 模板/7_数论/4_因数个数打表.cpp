int y[500005]= {};
void getfactor(int n)
{
    int x=sqrt(n);
    for (int i=1; i<=x; i++)
    {
        for (int j=i+1; j*i<=n; j++)
            y[i*j]+=2;
        y[i*i]++;
    }
}
