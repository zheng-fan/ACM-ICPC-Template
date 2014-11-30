int dfs(int pos, int s, bool e) //e==1表示满了（当前pos之前的数位都相同）
{
    if (pos==-1) return s==target_s; //返回 当前状态==目标状态
    if (~f[pos][s] && !e ) return f[pos][s]; //如果值已经算过并且没满则返回记录的值
    int ans = 0;
    int u = e ? bit[pos] : 9; //9可以相应改成进制
    for (int i = 0; i <= u; ++i)
        ans += dfs(pos-1, new_s(s, i), e&&i==u); //new_s表示新的状态。另外，“肯定不符合目标状态”的状态可以直接continue掉
    return e ? ans : f[pos][s]=ans; //如果满了就直接返回，否则记录再返回
}
int solve(int n)
{
    memset(f,-1,sizeof(f));
    int pos=-1;
    while(n)
    {
        bit[++pos]=n%10; //10为进制
        n/=10;
    }
    return dfs(pos,0,1); //初始状态
}

int f[20][5];
int bit[20];
int dfs(int pos, int s, bool e)
{
    if (pos==-1) return s==0||s==1;
    if (~f[pos][s]&&!e) return f[pos][s];
    int ans=0;
    int u=e?bit[pos]:9;
    for (int i=0; i<=u; ++i)
    {
        if(i==4||s==1&&i==2)
            continue;
        ans+=dfs(pos-1,i==6,e&&i==u);
    }
    return e?ans:f[pos][s]=ans;
}
int solve(int n)
{
    memset(f,-1,sizeof(f));
    int pos=-1;
    while(n)
    {
        bit[++pos]=n%10;
        n/=10;
    }
    return dfs(pos,0,1);
}
