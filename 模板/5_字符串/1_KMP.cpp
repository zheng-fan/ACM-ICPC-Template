const int LEN=1000005;
int next[LEN];
char s[LEN];
char sub[LEN];
void getnext(char sub[],int next[],int len2)
{
    int i=0,j=-1;
    next[0]=-1;
    while(i<len2)
    {
        if (j==-1||sub[i]==sub[j])
            i++,j++,next[i]=j;
        else j=next[j];
    }
}
int kmp(char s[],char sub[],int len1,int len2,int next[])
{
    int i=0,j=0;
    while(i<len1&&j<len2)
    {
        if (j==-1||s[i]==sub[j])
            i++,j++;
        else j=next[j];
    }
    if (j>=len2) return i-len2;
    else return -1;
}
