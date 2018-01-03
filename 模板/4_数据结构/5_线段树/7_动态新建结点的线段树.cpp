///这题是区间与1异或，区间求和
#define lson l,m,DL[rt]
#define rson m+1,r,DR[rt]
const int NV = 100005*32*4;
struct seg
{
    int sum[NV],add[NV],DL[NV],DR[NV];
    int cnt;
    seg()
    {
        cnt=1;
        sum[1]=add[1]=0;
        DL[1]=DR[1]=-1;
    }
    int newnode(int l,int r)
    {
        cnt++;
        sum[cnt]=add[cnt]=0;
        DL[cnt]=DR[cnt]=-1;
        return cnt;
    }
    void PushUp(int rt)
    {
        sum[rt]=sum[DL[rt]]+sum[DR[rt]];
    }
    void PushDown(int rt,int m)
    {
        if (add[rt])
        {
            add[DL[rt]] ^= add[rt];
            add[DR[rt]] ^= add[rt];
            sum[DL[rt]] = (m - (m >> 1))-sum[DL[rt]];
            sum[DR[rt]] = (m >> 1)-sum[DR[rt]];
            add[rt] = 0;
        }
    }
    void update(int L,int R,int c,int l,int r,int rt=1)
    {
        if (L <= l && r <= R)
        {
            add[rt]^=1;
            sum[rt] = (r - l + 1)-sum[rt];
            return ;
        }
        int m = ((long long)l + r) >> 1; ///long long is important here!!!
        if (DL[rt]==-1) DL[rt]=newnode(l,m);
        if (DR[rt]==-1) DR[rt]=newnode(m+1,r);
        PushDown(rt, r - l + 1);
        if (L <= m) update(L, R, c, lson);
        if (m < R) update(L, R, c, rson);
        PushUp(rt);
    }
    int query(int L,int R,int l,int r,int rt=1)
    {
        if (L <= l && r <= R)
        {
            return sum[rt];
        }
        int m = ((long long)l + r) >> 1; ///long long is important here!!!
        if (DL[rt]==-1) DL[rt]=newnode(l,m);
        if (DR[rt]==-1) DR[rt]=newnode(m+1,r);
        PushDown(rt, r - l + 1);
        int ret = 0;
        if (L <= m) ret += query(L, R, lson);
        if (m < R) ret += query(L, R, rson);
        return ret;
    }
} s;
