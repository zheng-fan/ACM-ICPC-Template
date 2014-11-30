const int CN=20;
long long c[CN][CN]= {};
void cinit()
{
    for(int i=0; i<CN; i++)
    {
        c[i][0]=c[i][i]=1;
        for(int j=1; j<i; j++)
            c[i][j]=c[i-1][j]+c[i-1][j-1];
    }
}
