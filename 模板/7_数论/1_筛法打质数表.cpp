const int NP=1000005;
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
