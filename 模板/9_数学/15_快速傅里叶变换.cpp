#include<complex>
const int NV=100005;
complex<double> epsilon[NV],repsilon[NV],buffera[NV],bufferb[NV],ffttemp[NV];
void init_epsilon(int n)
{
    for (int i=0; i<n; i++)
    {
        epsilon[i]=complex<double>(cos(2*pi*i/n),sin(2*pi*i/n));
        repsilon[i]=conj(epsilon[i]);
    }
}
void fft(int n, complex<double> *buffer, int offset, int step, complex<double> *epsilon)
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
void fftmul(int n,double a[],double b[],double ans[])
{
    ///因为乘出来是2n-1个项
    n=2*n-1;
    ///high bit
    n|=n>>1;
    n|=n>>2;
    n|=n>>4;
    n|=n>>8;
    n|=n>>16;
    n++;
    ///注意a和b要memset或者补零
    init_epsilon(n); ///n不变就可以不用重新init
    for (int i=0; i<n; i++) buffera[i]=a[i],bufferb[i]=b[i];
    fft(n,buffera,0,1,epsilon);
    fft(n,bufferb,0,1,epsilon);
    for (int i=0; i<n; i++) buffera[i]*=bufferb[i];
    fft(n,buffera,0,1,repsilon);
    for (int i=0; i<n; i++) ans[i]=buffera[i].real()/n;
}
