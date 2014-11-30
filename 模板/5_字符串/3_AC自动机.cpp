struct trie
{
    int next[500010][26],fail[500010],ed[500010];
    int root,L;
    int newnode()
    {
        for(int i = 0; i < 26; i++)
            next[L][i] = -1;
        ed[L++] = 0;
        return L-1;
    }
    void init()
    {
        L = 0;
        root = newnode();
    }
    void insert(char buf[])
    {
        int len = strlen(buf);
        int now = root;
        for(int i = 0; i < len; i++)
        {
            if(next[now][buf[i]-'a'] == -1)
                next[now][buf[i]-'a'] = newnode();
            now = next[now][buf[i]-'a'];
        }
        ed[now]++;
    }
    void build()
    {
        queue<int> q;
        fail[root] = root;
        for(int i = 0; i < 26; i++)
            if(next[root][i] == -1)
                next[root][i] = root;
            else
            {
                fail[next[root][i]] = root;
                q.push(next[root][i]);
            }
        while(!q.empty())
        {
            int now = q.front();
            q.pop();
            for(int i = 0; i < 26; i++)
                if(next[now][i] == -1)
                    next[now][i] = next[fail[now]][i];
                else
                {
                    fail[next[now][i]]=next[fail[now]][i];
                    q.push(next[now][i]);
                }
        }
    }
    int query(char buf[])
    {
        int len = strlen(buf);
        int now = root;
        int res = 0;
        for(int i = 0; i < len; i++)
        {
            now = next[now][buf[i]-'a'];
            int temp = now;
            while(temp != root)
            {
                res += ed[temp];
                ed[temp] = 0;
                temp = fail[temp];
            }
        }
        return res;
    }
    void Debug()
    {
        for(int i = 0; i < L; i++)
        {
            printf("id = %3d,fail = %3d,end = %3d,chi = [",i,fail[i],ed[i]);
            for(int j = 0; j < 26; j++)
                printf("%2d",next[i][j]);
            printf("]\n");
        }
    }
};
char buf[1000010];
trie ac;
int main()
{
    int t;
    int n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        ac.init();
        for(int i = 0; i < n; i++)
        {
            scanf("%s",buf);
            ac.insert(buf);
        }
        ac.build();
        scanf("%s",buf);
        printf("%d\n",ac.query(buf));
    }
    return 0;
}
