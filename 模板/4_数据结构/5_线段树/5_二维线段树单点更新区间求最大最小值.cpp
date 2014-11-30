const int NV=1005;
struct Nodey
{
    int l,r;
    int Max,Min;
};
int locy[NV],locx[NV];
struct Nodex
{
    int l,r;
    Nodey sty[NV*4];
    void build(int _l,int _r,int i=1)
    {
        sty[i].l = _l;
        sty[i].r = _r;
        sty[i].Max = -inf;
        sty[i].Min = inf;
        if(_l == _r)
        {
            locy[_l] = i;
            return;
        }
        int mid = (_l + _r)/2;
        build(_l,mid,i<<1);
        build(mid+1,_r,(i<<1)|1);
    }
    int queryMin(int _l,int _r,int i=1)
    {
        if(sty[i].l == _l && sty[i].r == _r)
            return sty[i].Min;
        int mid = (sty[i].l + sty[i].r)/2;
        if(_r <= mid)return queryMin(_l,_r,i<<1);
        else if(_l > mid)return queryMin(_l,_r,(i<<1)|1);
        else return min(queryMin(_l,mid,i<<1),queryMin(mid+1,_r,(i<<1)|1));
    }
    int queryMax(int _l,int _r,int i=1)
    {
        if(sty[i].l == _l && sty[i].r == _r)
            return sty[i].Max;
        int mid = (sty[i].l + sty[i].r)/2;
        if(_r <= mid)return queryMax(_l,_r,i<<1);
        else if(_l > mid)return queryMax(_l,_r,(i<<1)|1);
        else return max(queryMax(_l,mid,i<<1),queryMax(mid+1,_r,(i<<1)|1));
    }
} stx[NV*4];
int n;
void build(int l,int r,int i=1)
{
    stx[i].l = l;
    stx[i].r = r;
    stx[i].build(1,n);
    if(l == r)
    {
        locx[l] = i;
        return;
    }
    int mid = (l+r)/2;
    build(l,mid,i<<1);
    build(mid+1,r,(i<<1)|1);
}
void modify(int x,int y,int val)
{
    int tx = locx[x];
    int ty = locy[y];
    stx[tx].sty[ty].Min = stx[tx].sty[ty].Max = val;
    for(int i = tx; i; i >>= 1)
        for(int j = ty; j; j >>= 1)
        {
            if(i == tx && j == ty)continue;
            if(j == ty)
            {
                stx[i].sty[j].Min = min(stx[i<<1].sty[j].Min,stx[(i<<1)|1].sty[j].Min);
                stx[i].sty[j].Max = max(stx[i<<1].sty[j].Max,stx[(i<<1)|1].sty[j].Max);
            }
            else
            {
                stx[i].sty[j].Min = min(stx[i].sty[j<<1].Min,stx[i].sty[(j<<1)|1].Min);
                stx[i].sty[j].Max = max(stx[i].sty[j<<1].Max,stx[i].sty[(j<<1)|1].Max);
            }
        }
}
int queryMin(int x1,int x2,int y1,int y2,int i=1)
{
    if(stx[i].l == x1 && stx[i].r == x2)
        return stx[i].queryMin(y1,y2);
    int mid = (stx[i].l + stx[i].r)/2;
    if(x2 <= mid)return queryMin(x1,x2,y1,y2,i<<1);
    else if(x1 > mid)return queryMin(x1,x2,y1,y2,(i<<1)|1);
    else return min(queryMin(x1,mid,y1,y2,i<<1),queryMin(mid+1,x2,y1,y2,(i<<1)|1));
}
int queryMax(int x1,int x2,int y1,int y2,int i=1)
{
    if(stx[i].l == x1 && stx[i].r == x2)
        return stx[i].queryMax(y1,y2);
    int mid = (stx[i].l + stx[i].r)/2;
    if(x2 <= mid)return queryMax(x1,x2,y1,y2,i<<1);
    else if(x1 > mid)return queryMax(x1,x2,y1,y2,(i<<1)|1);
    else return max(queryMax(x1,mid,y1,y2,i<<1),queryMax(mid+1,x2,y1,y2,(i<<1)|1));
}
