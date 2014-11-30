#define keyTree (ch[ch[rt][1]][0])
const int NV=100005;
struct SplayTree
{
    int sz[NV];
    int ch[NV][2];
    int pre[NV];
    int rt,top,tops;
    int stk[NV],que[NV];
    SplayTree():rt(0),top(0) {}
    void Rotate(int x,int c)
    {
        int y=pre[x];
        push_down(y);
        push_down(x);
        ch[y][!c]=ch[x][c];
        pre[ch[x][c]]=y;
        pre[x]=pre[y];
        if(pre[x]) ch[pre[y]][ch[pre[y]][1]==y]=x;
        ch[x][c]=y;
        pre[y]=x;
        push_up(y);
    }
    void Splay(int x,int f)
    {
        if (x==f) return;
        push_down(x);
        while(pre[x]!=f)
        {
            if(pre[pre[x]]==f)
                Rotate(x,ch[pre[x]][0]==x);
            else
            {
                int y=pre[x],z=pre[y];
                int t=(ch[z][0]==y);
                if(ch[y][t]==x) Rotate(x,!t),Rotate(x,t);
                else Rotate(y,t),Rotate(x,t);
            }
        }
        push_up(x);
        if(f==0) rt=x;
    }
    void Select(int k,int f)  //把第k位的数转到f下边
    {
        int x=rt;
        push_down(x);
        while(sz[ch[x][0]]!=k)
        {
            if(k<sz[ch[x][0]]) x=ch[x][0];
            else
            {
                k-=(sz[ch[x][0]]+1);
                x=ch[x][1];
            }
            push_down(x);
        }
        Splay(x,f);
    }
    void Erase(int x)  //把以x为祖先结点删掉放进内存池，回收内存
    {
        int father=pre[x];
        int head=0,tail=0;
        for (que[tail++]=x; head<tail; head++)
        {
            stk[tops++]=que[head];
            if(ch[que[head]][0]) que[tail++]=ch[que[head]][0];
            if(ch[que[head]][1]) que[tail++]=ch[que[head]][1];
        }
        ch[father][ch[father][1]==x]=0;
        push_up(father);
    }
    int Find(int c)
    {
        int x=rt;
        while(x)
        {
            if (c==val[x])
            {
                Splay(x,rt);
                return x;
            }
            else if (c<val[x]) x=ch[x][0];
            else x=ch[x][1];
        }
        return 0;
    }
    void Insert(int c)
    {
        int p=rt;
        int *t=&p;
        int f=0;
        while(*t)
        {
            f=*t;
            if (c<val[*t]) t=&ch[*t][0];
            else t=&ch[*t][1];
        }
        int &x=*t;
        if (tops) x=stk[--tops];
        else x=++top;
        ch[x][0]=ch[x][1]=pre[x]=0;
        sz[x]=1;
        val[x]=sum[x]=c;
        pre[x]=f;
        while(f)
        {
            push_up(f);
            f=pre[f];
        }
        Splay(x,rt);
    }
    void Debug()
    {
        cout<<rt<<endl;
        Inorder(rt);
    }
    void Inorder(int x)
    {
        if(x)
        {
            Inorder(ch[x][0]);
            printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size=%2d ,val=%2d\n",x,ch[x][0],ch[x][1],pre[x],sz[x],val[x]);
            Inorder(ch[x][1]);
        }
    }

    //以下是题目的特定函数
    void newnode(int &x,int c)
    {
        if (tops) x=stk[--tops];
        else x=++top;
        ch[x][0]=ch[x][1]=pre[x]=0;
        sz[x]=1;
        ///题目特定
        val[x]=sum[x]=c;
        add[x]=0;
    }
    void push_down(int x) ///题目特定
    {
        if(add[x])
        {
            val[x]+=add[x];
            add[ch[x][0]]+=add[x];
            add[ch[x][1]]+=add[x];
            sum[ch[x][0]]+=(long long)sz[ch[x][0]]*add[x];
            sum[ch[x][1]]+=(long long)sz[ch[x][1]]*add[x];
            add[x]=0;
        }
    }
    void push_up(int x)
    {
        sz[x]=1+sz[ch[x][0]]+sz[ch[x][1]];
        ///题目特定
        sum[x]=val[x]+sum[ch[x][0]]+sum[ch[x][1]];
    }
    void build(int &x,int l,int r,int f)
    {
        if(l>r) return;
        int m=(l+r)>>1;
        newnode(x,num[m]); ///题目特定
        build(ch[x][0],l,m-1,x);
        build(ch[x][1],m+1,r,x);
        pre[x]=f;
        push_up(x);
    }
    void init(int n)
    {
        rt=top=0;
        //为了方便处理边界，加两个边界顶点
        newnode(rt,-1);
        newnode(ch[rt][1],-1);
        pre[top]=rt;
        sz[rt]=2;
        build(keyTree,1,n,ch[rt][1]);
        push_up(ch[rt][1]);
        push_up(rt);
    }
    void update(int l,int r,int c)
    {
        Select(l-1,0);
        Select(r+1,rt);
        ///题目特定
        add[keyTree]+=c;
        sum[keyTree]+=(long long)c*sz[keyTree];
    }
    long long query(int l,int r)
    {
        Select(l-1,0);
        Select(r+1,rt);
        return sum[keyTree];
    }
    ///题目特定变量
    int num[NV];
    int val[NV];
    int add[NV];
    long long sum[NV];
} sp;
int main()
{
    sp.Insert(5);
    sp.Insert(8);
    sp.Insert(2);
    sp.Insert(8);
    sp.Insert(6);
    sp.Insert(1);
    sp.Debug();
    cout<<sp.Find(8)<<endl;
    cout<<sp.Find(2)<<endl;
    cout<<sp.Find(5)<<endl;
    return 0;
}
