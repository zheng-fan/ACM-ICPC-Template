const int LEN = 100005;
char s[LEN], sub[LEN];
int next[LEN], ret[LEN];
void exkmp(char *a, char *b, int M, int N, int *next, int *ret)
{
    int i, j, k;
    //得到A关于A的后缀的最长公共前缀，存在next数组中
    for (j = 0; 1 + j < M && a[j] == a[1 + j]; j++) ;
    next[1] = j;
    k = 1;
    for (i = 2; i < M; i++)
    {
        int len = k + next[k], L = next[i - k];
        if (L < len - i) next[i] = L;
        else
        {
            for (j = max(0, len - i); i + j < M && a[j] == a[i + j]; j++) ;
            next[i] = j;
            k = i;
        }
    }
    //得到A关于B的后缀的最长公共前缀，存在ret数组中
    for (j = 0; j < N && j < M && a[j] == b[j]; j++) ;
    ret[0] = j;
    k = 0;
    for (i = 1; i < N; i++)
    {
        int len = k + ret[k], L = next[i - k];
        if (L < len - i) ret[i] = L;
        else
        {
            for (j = max(0, len - i); j < M && i + j < N && a[j] == b[i + j]; j++) ;
            ret[i] = j;
            k = i;
        }
    }
}
