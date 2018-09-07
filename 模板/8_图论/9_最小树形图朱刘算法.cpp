typedef int mytype;
const int NV=1005;
const int NE=NV*NV;
struct edge
{
    int u,v;
    mytype l;
} E[NE];
int pre[NV],ID[NV],vis[NV];
mytype In[NV];
void init(int m)
{
    for(int i=1; i<=m; i++)
        scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].l);
}
mytype Directed_MST(int root,int NV,int NE)
{
//    memset(pre,0,sizeof(pre));
    mytype ret = 0;
    while(1)
    {
        //1.找最小入边
        for(int i=1; i<=NV; i++)
            In[i] = inf;
        for(int i=1; i<=NE; i++)
        {
            int u = E[i].u;
            int v = E[i].v;
            if(E[i].l < In[v] && u != v)
            {
                pre[v] = u;
                In[v] = E[i].l;
            }
        }
        for(int i=1; i<=NV; i++)
        {
            if(i == root)
                continue;
            if(fabs(In[i]-inf)<eps)
                return -1;//除了根以外有点没有入边,则根无法到达它
        }
        //2.找环
        int cntnode = 0;
        memset(ID,-1,sizeof(ID));
        memset(vis,-1,sizeof(vis));
        In[root] = 0;
        for(int i=1; i<=NV; i++) //标记每个环
        {
            ret += In[i];
            int v = i;
            while(vis[v] != i && ID[v] == -1 && v != root)
            {
                vis[v] = i;
                v = pre[v];
            }
            if(v != root && ID[v] == -1)
            {
                ID[v] = ++cntnode;
                for(int u = pre[v] ; u != v ; u = pre[u])
                    ID[u] = cntnode;
            }
        }
        if(cntnode == 0)
            break;//无环
        for(int i=1; i<=NV; i++)
            if(ID[i] == -1)
                ID[i] = ++cntnode;
        //3.缩点,重新标记
        for(int i=1; i<=NE; i++)
        {
            int v = E[i].v;
            E[i].u = ID[E[i].u];
            E[i].v = ID[E[i].v];
            if(E[i].u != E[i].v)
            {
                E[i].l -= In[v];
            }
        }
        NV = cntnode;
        root = ID[root];
    }
    return ret;
}
bool judge(mytype ans)
{
    return fabs(ans+1)>eps;
}
