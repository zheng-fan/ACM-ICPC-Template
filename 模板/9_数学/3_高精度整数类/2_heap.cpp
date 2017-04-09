const int ra=10;
int ten[4]= {1,ra,ra*ra,ra*ra*ra};
int radix=ra*ra*ra*ra;
const int NV=1000;
struct integer
{
    int *d=NULL;
    integer():integer(0) {}
    ~integer()
    {
        delete []d;
    }
    ///将数组分配在堆上后，默认的赋值运算符只会复制指针，在析构时会出现问题，因此需要重载
    ///但应尽量避免赋值操作，以免导致效率损失
    integer &operator =(const integer &a)
    {
        memcpy(d,a.d,(a.d[0]+1)*sizeof(int));
        memset(d+d[0]+1,0,(NV-d[0]-1)*sizeof(int));
        return *this;
    }
    integer(int x)
    {
        d=new int[NV];
        for (int i=0; i<NV; i++) d[i]=0;
        if (!x) d[0]=1;
        while(x)
        {
            d[++d[0]]=x%radix;
            x/=radix;
        }
    }
    integer(long long x)
    {
        d=new int[NV];
        for (int i=0; i<NV; i++) d[i]=0;
        if (!x) d[0]=1;
        while(x)
        {
            d[++d[0]]=x%radix;
            x/=radix;
        }
    }
    integer(const char s[])
    {
        d=new int[NV];
        int len=strlen(s),i,j,k;
        d[0]=(len-1)/4+1;
        for (i=1; i<NV; i++)
            d[i]=0;
        for (i=len-1; i>=0; i--)
        {
            j=(len-i-1)/4+1;
            k=(len-i-1)%4;
            d[j]+=ten[k]*(s[i]-'0');
        }
        while(d[0]>1&&d[d[0]]==0) d[0]--;
    }
    string tostring()
    {
        string s;
        int i,j,temp;
        for (i=3; i>=1; i--) if (d[d[0]]>=ten[i]) break;
        temp=d[d[0]];
        for (j=i; j>=0; j--)
        {
            s+=(char) (temp/ten[j]+'0');
            temp%=ten[j];
        }
        for (i=d[0]-1; i>0; i--)
        {
            temp=d[i];
            for (j=3; j>=0; j--)
            {
                s+=(char) (temp/ten[j]+'0');
                temp%=ten[j];
            }
        }
        return s;
    }
    void output()
    {
        int k=d[0];
        ///for int d[]
        printf("%d",d[k--]);
        while(k) printf("%04d",d[k--]);
        putchar('\n');
    }
} d,mid1[15];
bool operator <(const integer &a,const integer &b)
{
    if (a.d[0]!=b.d[0]) return a.d[0]<b.d[0];
    for (int i=a.d[0]; i>0; i--)
        if (a.d[i]!=b.d[i])
            return a.d[i]<b.d[i];
    return 0;
}
integer operator +(const integer &a,const integer &b)
{
    integer c;
    c.d[0]=max(a.d[0],b.d[0]);
    int i,x=0;
    for (i=1; i<=c.d[0]; i++)
    {
        x+=a.d[i]+b.d[i];
        c.d[i]=x%radix;
        x/=radix;
    }
    while(x)
    {
        c.d[++c.d[0]]=x%radix;
        x/=radix;
    }
    return c;
}
integer operator -(const integer &a,const integer &b)
{
    integer c;
    c.d[0]=a.d[0];
    int i,x=0;
    for (i=1; i<=c.d[0]; i++)
    {
        x+=radix+a.d[i]-b.d[i];
        c.d[i]=x%radix;
        x=x/radix-1;
    }
    while(c.d[0]>1&&c.d[c.d[0]]==0) c.d[0]--;
    return c;
}
integer operator *(const integer &a,const integer &b)
{
    integer c;
    c.d[0]=a.d[0]+b.d[0];
    int i,j,x=0;
    for (i=1; i<=a.d[0]; i++)
    {
        x=0;
        for (j=1; j<=b.d[0]; j++)
        {
            x=a.d[i]*b.d[j]+x+c.d[i+j-1];
            c.d[i+j-1]=x%radix;
            x/=radix;
        }
        c.d[i+b.d[0]]=x;
    }
    while(c.d[0]>1&&c.d[c.d[0]]==0) c.d[0]--;
    return c;
}
integer operator *(const integer &a,const long long &k)
{
    integer c;
    c.d[0]=a.d[0];
    int i;
    long long x=0;
    for (i=1; i<=a.d[0]; i++)
    {
        x+=a.d[i]*k;
        c.d[i]=x%radix;
        x/=radix;
    }
    while(x>0)
    {
        c.d[++c.d[0]]=x%radix;
        x/=radix;
    }
    while(c.d[0]>1&&c.d[c.d[0]]==0) c.d[0]--;
    return c;
}
long long rem;
integer operator /(const integer &a,const long long &k)
{
    integer c;
    c.d[0]=a.d[0];
    long long x=0;
    for (int i=a.d[0]; i>=1; i--)
    {
        x+=a.d[i];
        c.d[i]=x/k;
        x%=k;
        rem=x;
        x*=radix;
    }
    while(c.d[0]>1&&c.d[c.d[0]]==0) c.d[0]--;
    return c;
}
bool smaller(const integer &a,const integer &b,int delta)
{
    if (a.d[0]+delta!=b.d[0]) return a.d[0]+delta<b.d[0];
    for (int i=a.d[0]; i>0; i--)
        if (a.d[i]!=b.d[i+delta])
            return a.d[i]<b.d[i+delta];
    return 1;
}
void Minus(integer &a,const integer &b,int delta)
{
    int i,x=0;
    for (i=1; i<=a.d[0]-delta; i++)
    {
        x+=radix+a.d[i+delta]-b.d[i];
        a.d[i+delta]=x%radix;
        x=x/radix-1;
    }
    while(a.d[0]>1&&a.d[a.d[0]]==0) a.d[0]--;
}
integer operator /(const integer &a,const integer &b)
{
    integer c;
    d=a;
    int i,j,temp;
    mid1[0]=b;
    for (i=1; i<=13; i++) mid1[i]=mid1[i-1]*2;
    for (i=a.d[0]-b.d[0]; i>=0; i--)
    {
        temp=8192;
        for (j=13; j>=0; j--)
        {
            if (smaller(mid1[j],d,i))
            {
                Minus(d,mid1[j],i);
                c.d[i+1]+=temp;
            }
            temp/=2;
        }
    }
    c.d[0]=max(1,a.d[0]-b.d[0]+1); ///for int d[]
    while(c.d[0]>1&&c.d[c.d[0]]==0) c.d[0]--;
    return c;
}
bool operator ==(const integer &a,const integer &b)
{
    if (a.d[0]!=b.d[0]) return 0;
    for (int i=1; i<=a.d[0]; i++)
        if (a.d[i]!=b.d[i])
            return 0;
    return 1;
}
void init(int b) ///将大数切换至任意<=10进制
{
    for (int i=1; i<=3; i++)
        ten[i]=ten[i-1]*b;
    radix=b*b*b*b;
}
