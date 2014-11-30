const int NV=1005;
const int NE=2000005;
int low[2*NV],dfn[2*NV],stk[2*NV],instk[2*NV],he[2*NV],belong[2*NV],sol[2*NV];
int idcnt,ecnt,ccnt,top;
vector<int> c[2*NV];
struct edge
{
    int v,next;
} E[2*NE];
void adde(int u,int v)
{
    E[++ecnt].v=v;
    E[ecnt].next=he[u];
    he[u]=ecnt;
}
int getvalue(int n,int x)
{
    int r=x>n?x-n:x;
    if (sol[r]==-1)
        return -1;
    return x>n?!sol[r]:sol[r];
}
void dfs(int u)
{
    low[u]=dfn[u]=++idcnt;
    stk[++top]=u;
    instk[u]=1;
    for (int i=he[u],v; i!=-1; i=E[i].next)
        if (!dfn[v=E[i].v])
        {
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if (instk[v])
            low[u]=min(low[u],dfn[v]);
    if (dfn[u]==low[u])
    {
        stk[top+1]=-1;
        for (++ccnt; stk[top+1]!=u; --top)
        {
            c[ccnt].push_back(stk[top]);
            instk[stk[top]]=0;
            belong[stk[top]]=ccnt;
        }
    }
}
bool two_sat(int n,int m)
{
    ecnt=idcnt=ccnt=top=0;
    for (int i=1; i<=2*n; i++)
    {
        he[i]=-1;
        dfn[i]=instk[i]=0;
        c[i].clear();
    }
    for (int i=1; i<=n; i++)
        sol[i]=-1;
    for (int i=0; i<m; i++)
    {
        ///TODO: adde
    }
    adde(1,n+1);
    for (int i=1; i<=2*n; i++)
        if (!dfn[i])
            dfs(i);
    for (int i=1; i<=n; i++)
        if (belong[i]==belong[i+n])
            return 0;
    for (int i=1; i<=ccnt; i++)
    {
        int val=1;
        for (int j=0; j<c[i].size(); j++)
        {
            int cur=c[i][j];
            if (getvalue(n,cur)==0)
                val=0;
            for (int k=he[cur]; k!=-1; k=E[k].next)
                if (getvalue(n,E[k].v)==0)
                    val=0;
            if (val==0)
                break;
        }
        for (int j=0; j<c[i].size(); j++)
            if (c[i][j]>n)
                sol[c[i][j]-n]=!val;
            else
                sol[c[i][j]]=val;
    }
    return 1;
}
