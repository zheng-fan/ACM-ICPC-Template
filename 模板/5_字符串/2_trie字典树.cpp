const int NS=1005*25;
int c[NS][128];
struct trie
{
//    int val[NS];
    int cnt[NS];
    int sz;
    trie()
    {
        sz=1;
        memset(c[0],0,sizeof(c[0]));
        memset(cnt,0,sizeof(cnt));
    }
    void insert(char s[],int v=0)
    {
        int u=0;
        for (int i=0; s[i]; i++)
        {
            if (!c[u][s[i]])
            {
                memset(c[sz],0,sizeof(c[sz]));
//                val[sz]=0;
                c[u][s[i]]=sz++;
            }
            u=c[u][s[i]];
            cnt[u]++;
        }
//        val[u]=v;
    }
    int query(char s[])
    {
        int u=0,n=strlen(s);
        for (int i=0; i<n; i++)
        {
            if (!c[u][s[i]]||u!=0&&cnt[u]<=1)
                return i;
            u=c[u][s[i]];
        }
        return n;
//        return cnt[u];
    }
};
