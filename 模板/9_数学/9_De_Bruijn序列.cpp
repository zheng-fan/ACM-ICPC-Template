void db(int n,int k,vector<int> &v,int a[],int t=1,int p=1)
{
    if (t>n)
    {
        if (n%p==0)
            for (int i=1; i<=p; i++)
                v.push_back(a[i]);
    }
    else
    {
        a[t]=a[t-p];
        db(n,k,v,a,t+1,p);
        for (int i=a[t-p]+1; i<k; i++)
        {
            a[t]=i;
            db(n,k,v,a,t+1,t);
        }
    }
}
vector<int> de_bruijn(int n,int k)
{
    vector<int> v;
    int a[n*k];
    memset(a,0,sizeof(a));
    db(n,k,v,a);
    return v;
}
