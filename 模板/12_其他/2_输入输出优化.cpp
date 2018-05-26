template<typename T> inline void RD(T &ret)
{
    char c;
    do c=getchar();
    while(c<'0'||c>'9');
    ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
        ret=ret*10+(c-'0');
}
template<typename T> inline void OT(T a)
{
    if(a>=10) OT(a/10);
    putchar(a%10+'0');
}
///有前导零的OT，主要在输出前要将输出数值加上lzexp
const int lznum=4;
const int lzexp=pow(10,lznum)+0.5;
template<typename T> inline void OT0(T a,int x=lznum-1)
{
    if(a>=10||x) OT0(a/10,x-1);
    putchar(a%10+'0');
}
///支持负数的RD
template<typename T> inline void RD(T &ret)
{
    char c=getchar();
    int sgn;
    while(c!='-'&&(c<'0'||c>'9')) c=getchar();
    sgn=(c=='-')?-1:1;
    ret=(c=='-')?0:(c-'0');
    while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
    ret*=sgn;
}
///吃掉空格与换行的getchar
inline char fzgetchar()
{
    char c;
    while(1)
    {
        c=getchar();
        if (c!=' '&&c!='\n') break;
    }
    return c;
}
///设置设置I/O缓存
setvbuf(stdin,new char[1<<20],_IOFBF,1<<20);
setvbuf(stdout,new char[1<<20],_IOFBF,1<<20);
