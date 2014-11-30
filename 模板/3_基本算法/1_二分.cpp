///二分（单调增）
double l=0,r=100,mid;
while(r-l>eps)
{
    mid=(l+r)/2;
    if (f(mid)>0)
        r=mid;
    else
        l=mid;
}

///二分（精确binary_search）
int l=0,r=10000,mid;
while(l<=r)
{
    mid=l+r>>1;
    if (a[mid]>key)
        r=mid-1;
    else if (a[mid]<key)
        l=mid+1;
    else
        break;
}
if (a[mid]==key);

///二分（lower_bound）
int l=0,r=10000,mid;
while(l<r)
{
    mid=l+r>>1;
    if (a[mid]>=key)
        r=mid;
    else if (a[mid]<key)
        l=mid+1;
}
if (a[l]==key);
