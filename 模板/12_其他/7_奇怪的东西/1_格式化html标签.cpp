char str[500000];
inline void jump()
{
    char c;
    while(isspace(c=getchar())) ;
    ungetc(c,stdin);
}
inline string gtag()
{
    jump();
    str[0]=0;
    scanf("%[^>]",str);
    string s=str;
    s+=getchar();
    return s;
}
inline void ptag(string &s)
{
    puts(s.c_str());
}
inline string gstr()
{
    jump();
    str[0]=0;
    scanf("%[^ <\n]",str);
    return str;
}
inline void pstr(string &s)
{
    printf("%s",s.c_str());
}
inline int judge(string &s)
{
    if (s[1]=='/') return -1;
    int flag=0;
    for (int i=0; i<s.length(); i++)
    {
        if (s[i]=='\"') flag=!flag;
        if (flag==0&&s[i]=='/') return 0;
    }
    return 1;
}
inline void pspace(int x)
{
    for (int i=0; i<x; i++)
       putchar(' ');
}
inline bool ishtml(string &s)
{
    return s=="</html>";
}
void dostr(int k)
{
    string s=gstr();
    if (s!="")
    {
        pspace(k);
        pstr(s);
        while(1)
        {
            s=gstr();
            if (s=="") break;
            putchar(' ');
            pstr(s);
        }
        puts("");
    }
}
void solve()
{
    int k=0,x;
    while(1)
    {
        string s=gtag();
        x=judge(s);
        if (x==-1) pspace(k-1);
        else pspace(k);
        k+=x;
        if (ishtml(s))
        {
            ptag(s);
            break;
        }
        ptag(s);
        dostr(k);
    }
}
