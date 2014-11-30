int a[500005],b[500005];
long long mergesort(int left,int right)
{
    if (left==right)
        return 0;
    long long cnt=0;
    int mid=(left+right)/2;
    cnt=mergesort(left,mid)+mergesort(mid+1,right);
    int i=left,j=mid+1,k=left;
    while(i<=mid&&j<=right)
        if(a[i]<=a[j])
            b[k++]=a[i++];
        else
        {
            b[k++]=a[j++];
            cnt+=(mid-i+1);
        }
    while(i<=mid)
        b[k++]=a[i++];
    while(j<=right)
        b[k++]=a[j++];
    for(i=left; i<=right; i++)
        a[i]=b[i];
    return cnt;
}
