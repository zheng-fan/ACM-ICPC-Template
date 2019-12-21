///以1为起始
const int NV=200005;
template<typename T>
struct SBT
{
    int sz[NV];
    T K[NV];
    int lc[NV];
    int rc[NV];
    int rt,tsz;
    void clear()
    {
        tsz=0;
        lc[0]=rc[0]=0;
        sz[0]=0;
        rt=0;
    }
    SBT()
    {
        clear();
    }
    int Size()
    {
        return sz[rt];
    }
    bool empty()
    {
        return rt==0;
    }
    void Build(int s,int e)
    {
        Build(rt,s,e);
    }
    bool Find(T key)
    {
        return Find(rt,key);
    }
    void Insert(T key)
    {
        Insert(rt,key);
    }
    void Delete(T key)
    {
        Delete(rt,key);
    }
    T DeleteSelect(int k)
    {
        return DeleteSelect(rt,k);
    }
    void DeleteLess(T key)
    {
        DeleteLess(rt,key);
    }
    void DeleteGreater(T key)
    {
        DeleteGreater(rt,key);
    }
    int Rank(T key)
    {
        return Rank(rt,key);
    }
    T Select(int k)
    {
        return Select(rt,k);
    }
    T pred(T key)
    {
        return pred(rt,key);
    }
    T succ(T key)
    {
        return succ(rt,key);
    }
    void inorder()
    {
        inorder(rt);
    }
    T getMin()
    {
        int t=rt;
        while (lc[t]) t=lc[t];
        return K[t];
    }
    T getMax()
    {
        int t=rt;
        while (rc[t]) t=rc[t];
        return K[t];
    }
    T DeleteMax()
    {
        int t=rt;
        if(rc[rt]==0)
        {
            rt=lc[rt];
            return K[t];
        }
        while (rc[rc[t]])
        {
            sz[t]--;
            t=rc[t];
        }
        sz[t]--;
        T ret=K[rc[t]];
        rc[t]=lc[rc[t]];
        return ret;
    }
    T DeleteMin()
    {
        int t=rt;
        if(lc[rt]==0)
        {
            rt=rc[rt];
            return K[t];
        }
        while (lc[lc[t]])
        {
            sz[t]--;
            t=lc[t];
        }
        sz[t]--;
        T ret=K[lc[t]];
        lc[t]=rc[lc[t]];
        return ret;
    }
private:
    void Build(int &rt,int s,int e)
    {
        if(s>e) return;
        int mid=(s+e)/2;
        rt=++tsz;
        K[rt]=mid;
        lc[rt]=0;
        rc[rt]=0;
        sz[rt]=e-s+1;
        if(s==e) return;
        Build(lc[rt],s,mid-1);
        Build(rc[rt],mid+1,e);
    }
    bool Find(int &rt,T key)
    {
        if (rt==0) return false;
        else if (key<K[rt]) return Find(lc[rt],key);
        else return K[rt]==key||Find(rc[rt],key);
    }
    void Insert(int &rt,T key)
    {
        if (rt==0)
        {
            rt=++tsz;
            lc[rt]=rc[rt]=0;
            sz[rt]=1;
            K[rt]=key;
            return;
        }
        sz[rt]++;
        if (key<K[rt]) Insert(lc[rt],key);
        else Insert(rc[rt],key);
        maintain(rt,!(key<K[rt]));
    }
    T Delete(int &rt,T key)
    {
        sz[rt]--;
        if ((K[rt]==key)||(key<K[rt]&&lc[rt]==0)||(K[rt]<key&&rc[rt]==0))
        {
            T ret=K[rt];
            if (lc[rt]==0||rc[rt]==0)
                rt=lc[rt]+rc[rt];
            else K[rt]=Delete(lc[rt],K[rt]+1);
            return ret;
        }
        else
        {
            if (key<K[rt]) return Delete(lc[rt],key);
            else return Delete(rc[rt],key);
        }
    }
    void DeleteLess(int &rt,T key)
    {
        if (rt==0) return;
        if (K[rt]<key)
        {
            rt=rc[rt];
            DeleteLess(rt,key);
        }
        else
        {
            DeleteLess(lc[rt],key);
            sz[rt]=1+sz[lc[rt]]+sz[rc[rt]];
        }
    }
    void DeleteGreater(int &rt,T key)
    {
        if (rt==0) return;
        if (K[rt]>key)
        {
            rt=lc[rt];
            DeleteGreater(rt,key);
        }
        else
        {
            DeleteGreater(rc[rt],key);
            sz[rt]=1+sz[lc[rt]]+sz[rc[rt]];
        }
    }
    int Rank(int &rt,T key)
    {
        if (K[rt]==key) return sz[lc[rt]]+1;
        else if (key<K[rt]) return Rank(lc[rt], key);
        else return sz[lc[rt]]+1+Rank(rc[rt],key);
    }
    T Select(int &rt,int k)
    {
        if (sz[lc[rt]]+1==k) return K[rt];
        else if (k>sz[lc[rt]]) return Select(rc[rt],k-1-sz[lc[rt]]);
        else return Select(lc[rt],k);
    }
    T DeleteSelect(int &rt,int k)
    {
        sz[rt]--;
        if (sz[lc[rt]]+1==k)
        {
            T ret=K[rt];
            if (lc[rt]==0||rc[rt]==0) rt=lc[rt]+rc[rt];
            else K[rt]=Delete(lc[rt],K[rt]+1);
            return ret;
        }
        else if (k>sz[lc[rt]]) return DeleteSelect(rc[rt],k-1-sz[lc[rt]]);
        else return DeleteSelect(lc[rt],k);
    }
    T pred(int &rt,T key)
    {
        if (rt==0) return key;
        else if (key>K[rt])
        {
            T ret=pred(rc[rt],key);
            if(ret==key) return K[rt];
            return ret;
        }
        else return pred(lc[rt],key);
    }
    T succ(int &rt,T key)
    {
        if (rt==0) return key;
        else if (K[rt]>key)
        {
            T ret=succ(lc[rt],key);
            if (ret==key) return K[rt];
            return ret;
        }
        else return succ(rc[rt],key);
    }
    void zag(int &rt)  //LeftRotate
    {
        int t=rc[rt];
        rc[rt]=lc[t];
        lc[t]=rt;
        sz[t]=sz[rt];
        sz[rt]=1+sz[lc[rt]]+sz[rc[rt]];
        rt=t;
    }
    void zig(int &rt)  //RightRotate
    {
        int t=lc[rt];
        lc[rt]=rc[t];
        rc[t]=rt;
        sz[t]=sz[rt];
        sz[rt]=1+sz[lc[rt]]+sz[rc[rt]];
        rt=t;
    }
    void maintain(int &rt,bool flag)
    {
        if (rt==0) return;
        if (!flag)
        {
            if (sz[lc[lc[rt]]]>sz[rc[rt]]) zig(rt);
            else if (sz[rc[lc[rt]]]>sz[rc[rt]])
            {
                zag(lc[rt]);
                zig(rt);
            }
            else return;
        }
        else
        {
            if (sz[rc[rc[rt]]]>sz[lc[rt]]) zag(rt);
            else if (sz[lc[rc[rt]]]>sz[lc[rt]])
            {
                zig(rc[rt]);
                zag(rt);
            }
            else return;
        }
        maintain(lc[rt],false);
        maintain(rc[rt],true);
        maintain(rt,false);
        maintain(rt,true);
    }
    void inorder(int &rt)
    {
        if(rt==0) return;
        else
        {
            inorder(lc[rt]);
            cout<<"rt:"<<rt<<" key:"<<K[rt]<<" size:"<<sz[rt]<<endl;
            inorder(rc[rt]);
        }
    }
};
struct node
{
    int key,id;
    node(int key=0,int id=0):key(key),id(id) {}
    bool operator <(node b)
    {
        return key<b.key;
    }
    bool operator >(node b)
    {
        return key>b.key;
    }
    bool operator ==(node b)
    {
        return key==b.key;
    }
    node operator +(int K)
    {
        return node(key+K,id);
    }
};
