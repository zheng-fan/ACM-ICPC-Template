const int LEN=100005;
unsigned long long f[LEN],r[LEN],pw[LEN];
int len;
void init(char *s)
{
    pw[0]=1;
    len=1;
    f[0]=s[0];
    for (int i=1; s[i]; i++)
        f[i] = f[i-1] * 131 + s[i],len++,pw[i]=pw[i-1]*131;
    r[len-1]=s[len-1];
    for (int i=len-2; i>=0; i--)
        r[i] = r[i+1] * 131 + s[i];
}
unsigned long long fwd(int i,int j)
{
    if (i<0||j>=len) return 0;
    if (i==0) return f[j];
    return f[j]-f[i-1]*pw[j-i+1];
}
unsigned long long rev(int i,int j)
{
    if (i<0||j>=len) return 0;
    if (j==len-1) return r[i];
    return r[i]-r[j+1]*pw[j-i+1];
}
