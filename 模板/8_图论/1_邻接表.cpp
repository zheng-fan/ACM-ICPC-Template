typedef int mytype;
const int NV=105;
const int NE=10005*2;
int he[NV],ecnt;
struct edge
{
    int v,next;
    mytype l;
} E[NE];
void adde(int u,int v,mytype l)
{
    E[++ecnt].v=v;
    E[ecnt].l=l;
    E[ecnt].next=he[u];
    he[u]=ecnt;
}
///初始化：
ecnt=0;
memset(he,-1,sizeof(he));
///调用：
for (int i=he[u]; i!=-1; i=E[i].next) ;
