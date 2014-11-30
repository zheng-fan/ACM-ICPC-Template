inline void RD(int &ret)
{
    char c;
    do c=getchar();
    while(c<'0'||c>'9');
    ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
        ret=ret*10+(c-'0');
}
inline void OT(int a)
{
    if(a>=10) OT(a/10);
    putchar(a%10+'0');
}
//负数
inline void RD(int &ret)
{
    char c;
    int sgn;
    while(c!='-'&&(c<'0'||c>'9')) c=getchar();
    sgn=(c=='-')?-1:1;
    ret=(c=='-')?0:(c-'0');
    while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
    ret*=sgn;
}
