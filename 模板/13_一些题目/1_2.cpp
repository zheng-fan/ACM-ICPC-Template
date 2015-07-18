inline int readint()
{
    char c = getchar();
    while (!isdigit(c)) c = getchar();
    int x = 0;
    while (isdigit(c))
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

inline long long readlong()
{
    char c = getchar();
    while (!isdigit(c)) c = getchar();
    long long x = 0;
    while (isdigit(c))
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

#define FOR(i, n) for (int i = 0; i < (int)(n); i++)
#define REP(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define CIR(i, a, b) for (int i = (int)(b); i >= (int)(a); i--)
#define PII pair<int, int>
#define FI first
#define SE second
#define MP make_pair
#define PB push_back
#define SZ(v) v.size();
#define ALL(v) v.begin(), v.end()
#define CLR(v, a) memset(v, a, sizeof(v));
#define IT iterator
#define LL long long
#define DB double
#define PI 3.1415926
#define INF 1000000000

#define N 80005
#define M N * 60

int dep[N], W[N], top[N], idx[N], size[N], fa[N], id;
int son[N], head[N], to[N << 1], next[N << 1];
int n, E, it;
int test;

void init()
{
    for (int i = 1; i <= n; i++)
    {
        head[i] = -1, son[i] = 0, dep[i] = 0;
    }
    id = 0;
    E = 0, it = 1;
}

void addEdge(int u, int v)
{
    to[E] = v, next[E] = head[u], head[u] = E++;
    to[E] = u, next[E] = head[v], head[v] = E++;
}

void dfs(int u, int p)
{
    fa[u] = p;
    size[u] = 1, son[u] = 0;

    for (int i = head[u]; i != -1; i = next[i])
    {
        int v = to[i];

        if (v != p)
        {
            dep[v] = dep[u] + 1;
            dfs(v, u);
            if (size[v] > size[son[u]]) son[u] = v;
            size[u] += size[v];
        }
    }
}

void dfs(int u, int p, int tu)
{

    idx[u] = ++id, top[u] = tu;
    if (son[u]) dfs(son[u], u, tu);
    for (int i = head[u]; i != -1; i = next[i])
    {
        int v = to[i];
        if (v == p || son[u] == v) continue;
        dfs(v, u, v);
    }
}

int lca(int u, int v)
{
    int tu = top[u], tv = top[v];
    while (tu != tv)
    {
        if (dep[tu] < dep[tv])
        {
            swap(tu, tv);
            swap(u, v);
        }
        u = fa[tu], tu = top[u];
    }

    if (dep[u] > dep[v]) swap(u, v);
    return u;
}

int root[N], r[M], v[M], ch[M][2], sz[M];

#define lch ch[rt][0]
#define rch ch[rt][1]

inline void push_up(int rt)
{
    sz[rt] = sz[lch] + sz[rch] + 1;
}

inline int cmp(int rt, int x)
{
    if (v[rt] == x) return -1;
    else if (x < v[rt])
        return 0;
    else
        return 1;
}

void rotate(int& rt, int d)
{
    int t = ch[rt][d ^ 1];
    ch[rt][d ^ 1] = ch[t][d];
    ch[t][d] = rt;
    push_up(rt);
    push_up(t);
    rt = t;
}

void insert(int&rt, int x)
{
    if (!rt)
    {
        rt = it++;
        sz[rt] = 1;
        lch = rch = 0;
        v[rt] = x;
        r[rt] = rand();
    }
    else
    {
        int d = x < v[rt] ? 0 : 1;
        insert(ch[rt][d], x);
        if (r[ch[rt][d]] > r[rt])
            rotate(rt, d ^ 1);
    }
    push_up(rt);
}

int kth(int rt, int k)
{
    int  t = sz[rch] + 1;
    if (k == t)
        return v[rt];
    else if (k < t)
        return kth(rch, k);
    else
        return kth(lch, k - t);
}

int upper(int rt, int val)
{
    if (!rt) return 0;
    int res = 0;
    if (v[rt] == val)
    {
        res++;
        res += upper(lch, val);
        res += upper(rch, val);
    }
    else if (val < v[rt])
    {
        res += sz[rch] + 1;
        res += upper(lch, val);
    }
    else
    {
        res += upper(rch, val);
    }
    return res;
}

void remove(int& rt, int x)
{
    int d = cmp(rt, x);
    if (d == -1)
    {
        if (lch && rch)
        {
            int d2 = r[lch] > r[rch] ? 0 : 1;
            rotate(rt, d2 ^ 1);
            remove(ch[rt][d2 ^ 1], x);
            push_up(rt);
        }
        else
        {
            rt = lch ? lch : rch;
        }
    }
    else
    {
        remove(ch[rt][d], x);
        push_up(rt);
    }
}

int gao(int L, int R, int val)
{
    int res = 0;
    int p = R;
    while (p)
    {
        res += upper(root[p], val);
        p -= p & (-p);
    }

    p = L - 1;

    while (p)
    {
        res -= upper(root[p], val);
        p -= p & (-p);
    }

    return res;
}

int solve(int u, int v, int val)
{
    int res = 0;
    int tu = top[u], tv = top[v];
    while (tu != tv)
    {
        if (dep[tu] < dep[tv])
        {
            swap(tu, tv);
            swap(u, v);
        }
        res += gao(idx[tu], idx[u], val);
        u = fa[tu], tu = top[u];
    }

    if (dep[u] > dep[v]) swap(u, v);
    res += gao(idx[u], idx[v], val);

    return res;
}

void modify(int u, int val)
{
    if (W[u] == val) return;

    int p = idx[u];
    while (p <= n)
    {
        remove(root[p], W[u]);
        insert(root[p], val);
        p += p & (-p);
    }

    remove(root[N - 1], W[u]);
    insert(root[N - 1], val);
    W[u] = val;
}

int query(int u, int v, int k)
{
    int pa = lca(u, v);
    int temp = dep[u] + dep[v] - 2 * dep[pa] + 1;
    if (k > temp) return -1;
    int L = 1, R = n;

    while (L <= R)
    {
        int mid = L + R >> 1;
        int tmp = kth(root[N - 1], mid);

        if (solve(u, v, tmp) >= k)
            R = mid - 1;
        else
            L = mid + 1;
    }

    return kth(root[N - 1], L);
}

int main()
{
    int k, a, b, m;
    while (~scanf("%d%d", &n, &m))
    {
        REP(i, 1, n) scanf("%d", &W[i]);

        init();

        FOR (i, N) root[i] = 0;

        FOR (i, n - 1)
        {
            scanf("%d%d", &a, &b);
            addEdge(a, b);
        }

        dfs(1, -1);
        dfs(1, -1, 1);

        REP(i, 1, n)
        {
            int p = idx[i];
            insert(root[N - 1], W[i]);
            while (p <= n)
            {
                insert(root[p], W[i]);
                p += p & (-p);
            }
        }

        FOR (i, m)
        {
            scanf("%d%d%d", &k, &a, &b);
            if (k == 0)
                modify(a, b);
            else
            {
                int res = query(a, b, k);
                if (res == -1)
                    puts("invalid request!");
                else
                    printf("%d\n", res);
            }

        }
    }
    return 0;
}
