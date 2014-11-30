double romberg(double l,double r,double epss=eps)
{
    vector<double> t;
    double h=r-l,last,curr;
    int k=1,i=1;
    t.push_back(h*(f(l)+f(r))/2);
    do
    {
        last=t.back();
        curr=0;
        double x=l+h/2;
        for (int j=0; j<k; j++)
        {
            curr+=f(x);
            x+=h;
        }
        curr=(t[0]+h*curr)/2;
        double k1=4.0/3,k2=1.0/3;
        for (int j=0; j<i; j++)
        {
            double temp=k1*curr-k2*t[j];
            t[j]=curr;
            curr=temp;
            k2/=4*k1-k2;
            k1=k2+1;
        }
        t.push_back(curr);
        k*=2;
        h/=2;
        i++;
    }
    while(fabs(last-curr)>epss);
    return t.back();
}
