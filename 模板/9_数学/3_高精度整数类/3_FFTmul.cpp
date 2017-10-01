///由于使用万进制，NV可以除以4。但又由于答案长度是原来的2倍，再加上补到2的某次方的最坏情况是到2倍，因此NV的大小跟数的十进制长度相同即可。
#include<complex>
complex<long double> epsilon[NV],repsilon[NV],buffera[NV],bufferb[NV],ffttemp[NV];
void init_epsilon(int n)
{
    for (int i=0; i<n; i++)
    {
        epsilon[i]=complex<long double>(cos(2*pi*i/n), sin(2*pi*i/n));
        repsilon[i]=conj(epsilon[i]);
    }
}
void fft(int n, complex<long double> *buffer, int offset, int step, complex<long double> *epsilon)
{
    if(n==1) return;
    int m=n>>1;
    fft(m,buffer,offset,step<<1,epsilon);
    fft(m,buffer,offset+step,step<<1,epsilon);
    for(int k=0; k<m; k++)
    {
        int pos=2*step*k;
        ffttemp[k]=buffer[pos+offset]+epsilon[k*step]*buffer[pos+offset+step];
        ffttemp[k+m]=buffer[pos+offset]-epsilon[k*step]*buffer[pos+offset+step];
    }
    for(int i=0; i<n; i++)
        buffer[i*step+offset]=ffttemp[i];
}
integer fftmul(const integer &a,const integer &b)
{
    ///high bit
    int n=max(a.d[0],b.d[0]);
    ///1
    n=2*n-1;
    ///2
    n|=n>>1;
    n|=n>>2;
    n|=n>>4;
    n|=n>>8;
    n|=n>>16;
    n++;
    ///似乎也可以1、2调换但1变成n=2*n
    init_epsilon(n);
    for (int i=0; i<n; i++) buffera[i]=a.d[i+1],bufferb[i]=b.d[i+1];
    fft(n,buffera,0,1,epsilon);
    fft(n,bufferb,0,1,epsilon);
    for (int i=0; i<n; i++) buffera[i]*=bufferb[i];
    fft(n,buffera,0,1,repsilon);
    integer ans;
    ans.d[0]=0;
    long long intrem=0;
    for (int i=0; i<n; i++)
    {
        long long x=buffera[i].real()/n+0.5;
        x+=intrem;
        ans.d[++ans.d[0]]=x%radix;
        intrem=x/radix;
    }
    while(ans.d[0]>1&&ans.d[ans.d[0]]==0) ans.d[0]--;
    return ans;
}
