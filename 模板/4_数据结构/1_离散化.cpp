int discrete(int data[],int n,int dis[],int idx[])
{
    int sub[n+1];
    memcpy(sub,data,sizeof(sub));
    sort(sub+1,sub+n+1);
    int m=unique(sub+1,sub+n+1)-sub-1;
    for(int i=1; i<=n; i++)
    {
        dis[i]=lower_bound(sub+1,sub+m+1,data[i])-sub;
        idx[dis[i]]=data[i];
    }
    return m;
}

const int NV=60005;
int m,data[NV];
int inithash(int n)
{
    sort(data+1,data+n+1);
    return unique(data+1,data+n+1)-data-1;
}
int hash(int x)
{
    return lower_bound(data+1,data+m+1,x)-data;
}
