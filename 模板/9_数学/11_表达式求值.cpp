char str1[1005], str2[1005];
int s1[1005], s2[1005];
int nei[300], wai[300]; //运算符优先级
int cust[1005]; //自定义变量
stack<int> optr;
stack<long long> opnd;
stack<int> neg;
bool flag;
long long calculate(long long x, long long y, char c)
{
    switch(c)
    {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        return x / y;
    case '^':
        long long tmp = 1;
        for(int i = 0; i < y; i++) tmp *= x;
        return tmp;
    }
}
char cmp(char a, char b)
{
    if(nei[a] > wai[b]) return '>';
    else if(nei[a] == wai[b]) return '=';
    return '<';
}
long long calc(int *s)
{
    flag=1;
    int i = 0;
    long long num;
    int sgn=0;
    while(s[i] != '#' || optr.top() != '#')
    {
        num = 0;
        if(!flag) return -1;
        if(s[i] >= '0' && s[i] <= '9')
        {
            while(s[i] >= '0' && s[i] <= '9')
            {
                num *= 10;
                num += s[i] - '0';
                i++;
            }
            opnd.push(num);
            sgn++;
        }
        else if(s[i] >= 300)
        {
            opnd.push(cust[s[i] - 300]);
            i++;
            sgn++;
        }
        else
        {
            if (s[i]=='(') neg.push(sgn),sgn=0;
            switch(cmp(optr.top(), s[i]))
            {
            case '<' :
                optr.push(s[i]);
                i++;
                break;
            case '=' :
                optr.pop();
                if (s[i]==')') sgn=neg.top()+1,neg.pop();
                i++;
                break;
            case '>' :
                if(opnd.empty())
                {
                    flag = false;
                    return -1;
                }
                long long ta = opnd.top();
                opnd.pop();
                if ((opnd.empty()||sgn==1)&&(optr.top()=='+'||optr.top()=='-'))
                {
                    if (optr.top()=='-') opnd.push(-ta);
                    else opnd.push(ta);
                    optr.pop();
                    break;
                }
                if(opnd.empty())
                {
                    flag = false;
                    return -1;
                }
                long long tb = opnd.top();
                opnd.pop();
                opnd.push(calculate(tb, ta, optr.top()));
                optr.pop();
                break;
            }
        }
    }
    return opnd.top();
}
void init()
{
    nei['+'] = 2,wai['+'] = 1;
    nei['-'] = 2,wai['-'] = 1;
    nei['*'] = 4,wai['*'] = 3;
    nei['/'] = 4,wai['/'] = 3;
    ///乘方自右向左结合，内外交换后可变成自左向右结合
    nei['^'] = 5,wai['^'] = 6;
    nei[')'] = 8,wai[')'] = 0;
    nei['('] = 0,wai['('] = 8;
    nei['#'] =-1,wai['#'] =-1;
}
void initstr(int *s,char *str)
{
    int len = 0;
    for(int i = 0; str[i]; i++)
    {
        if(!isspace(str[i]))
        {
            s[len++] = str[i];
            //在栈中计算时，超过300的数视为自定义数
            //cust数组从0开始
            ///'a'-'z'之间的数用cust数组的数计算
            if (isalpha(s[len-1])) s[len-1]+=-'a'+300;
        }
    }
    s[len++] = '#';
    s[len] = 0;
}
void initstack()
{
    while(!opnd.empty()) opnd.pop();
    while(!optr.empty()) optr.pop();
    optr.push('#');
}
int main()
{
    init();
    int t;
    scanf("%d\n", &t);
    srand(time(0));
    while(t--)
    {
        gets(str1);
        initstr(s1,str1);
        gets(str2);
        initstr(s2,str2);
        flag = 1;
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 26; j++) cust[j] = abs(rand()) % 100;
            initstack();
            long long t1 = calc(s1);
            initstack();
            long long t2 = calc(s2);
            if(t1 != t2)
            {
                flag = 0;
                break;
            }
        }
        if(flag) puts("YES");
        else puts("NO");
    }
    return 0;
}
