vector<unsigned long> gray(int n)
{
    vector<unsigned long> res;
    for (unsigned long i=0; i<(1<<n); i++)
        res.push_back(i^(i>>1));
    return res;
}
int main()
{
    vector<unsigned long> v=gray(8);
    for (int i=0; i<v.size(); i++)
        cout<<bitset<8>(v[i])<<endl;
    return 0;
}
