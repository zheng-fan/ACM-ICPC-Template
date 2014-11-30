const int NV=1005;
struct Nodey
{
    int l,r;
    int val;
};
int n;
int locx[NV],locy[NV];
struct Nodex
{
    int l,r;
    Nodey sty[NV*3];
    void build(int _l,int _r,int i=1)
    {
        sty[i].l = _l;
        sty[i].r = _r;
        sty[i].val = 0;
        if(_l == _r)
        {
            locy[_l] = i;
            return;
        }
        int mid = (_l + _r)>>1;
        build(_l,mid,i<<1);
        build(mid+1,_r,(i<<1)|1);
    }
    void add(int _l,int _r,int val,int i=1)
    {
        if(sty[i].l == _l && sty[i].r == _r)
        {
            sty[i].val += val;
            return;
        }
        int mid = (sty[i].l + sty[i].r)>>1;
        if(_r <= mid)add(_l,_r,val,i<<1);
        else if(_l > mid)add(_l,_r,val,(i<<1)|1);
        else
        {
            add(_l,mid,val,i<<1);
            add(mid+1,_r,val,(i<<1)|1);
        }
    }
} stx[NV*3];
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
    int mid = (l+r)>>1;
    build(l,mid,i<<1);
    build(mid+1,r,(i<<1)|1);
}
void add(int x1,int x2,int y1,int y2,int val,int i=1)
{
    if(stx[i].l == x1 && stx[i].r == x2)
    {
        stx[i].add(y1,y2,val);
        return;
    }
    int mid = (stx[i].l + stx[i].r)/2;
    if(x2 <= mid)add(x1,x2,y1,y2,val,i<<1);
    else if(x1 > mid)add(x1,x2,y1,y2,val,(i<<1)|1);
    else
    {
        add(x1,mid,y1,y2,val,i<<1);
        add(mid+1,x2,y1,y2,val,(i<<1)|1);
    }
}
int sum(int x,int y)
{
    int ret = 0;
    for(int i = locx[x]; i; i >>= 1)
        for(int j = locy[y]; j; j >>= 1)
            ret += stx[i].sty[j].val;
    return ret;
}
