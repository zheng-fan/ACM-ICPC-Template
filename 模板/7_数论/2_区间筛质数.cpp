const int NP=100005;
int ispri[NP]= {},prime[NP],pcnt=0;
void getprime()
{
    ispri[0]=ispri[1]=1;
    for (long long i=2; i<NP; i++)
        if (ispri[i]==0)
        {
            prime[++pcnt]=i;
            for (long long j=i*i; j<NP; j+=i)
                ispri[j]=1;
        }
}
const int NI=1000005;
int iispri[NI],iprime[NI],icnt;
void igetprime(int l,int r)
{
    memset(iispri,0,sizeof(iispri));
    if (l<2) l=2;
    for (int i=1; i<=pcnt&&(long long)prime[i]*prime[i]<=r; i++)
    {
        int s=l/prime[i]+(l%prime[i]>0);
        if (s==1)s=2;
        for (long long j=s; j*prime[i]<=r; j++)
            if(j*prime[i]>=l)
                iispri[j*prime[i]-l]=1;
    }
    icnt=0;
    for(int i=0; i<=r-l; i++)
        if(!iispri[i])
            iprime[++icnt]=i+l;
}
