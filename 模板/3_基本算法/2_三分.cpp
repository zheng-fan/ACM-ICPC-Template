///（极小值）
double left,right,mid1,mid2;
left=-1e7;
right=1e7;
while(fabs(left-right)>eps)
{
    mid1=(left+right)/2;
    mid2=(mid1+right)/2;
    if (f(mid1)<f(mid2))
        right=mid2;
    else
        left=mid1;
}
