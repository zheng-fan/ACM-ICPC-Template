///欧几里得求最大公约数
__gcd(a,b);
///对[0,n)建堆
make_heap(a,a+n);
///将n-1插入到[0,n-1)的堆中
push_heap(a,a+n);
///将1从[0,n)的堆中取出到n
pop_heap(a,a+n);
///对[0,n)的堆进行排序
sort_heap(a,a+n);
///翻转容器内元素
reverse(v.begin(),v.end());
///对容器中的key计数
count(v.begin(),v.end(),key);
///对容器中符合pred条件的元素计数
count_if(v.begin(),v.end(),pred),bool pred(type a);
///删除容器中值为的key元素，返回end()迭代器
remove(v.begin(),v.end(),key);
v.erase(remove(v.begin(),v.end(),key),v.end());
///删除容器中符合pred条件的元素，返回end()迭代器
remove_if(v.begin(),v.end(),pred),bool pred(type a);
///对容器中元素排重，返回end()迭代器。符合pred的视为相同
unique(v.begin(),v.end());
unique(v.begin(),v.end(),pred),bool pred(type a,type b);
v.erase(unique(v.begin(),v.end()),v.end());
///遍历容器找到值为key元素，返回迭代器，找不到则返回end()
find(v.begin(),v.end(),key);
///生成下一个全排列，有则返回1，无则返回0
next_permutation(v.begin(),v.end());
///生成上一个全排列，有则返回1，无则返回0
prev_permutation(v.begin(),v.end());
///可以插入value，而不会破坏容器顺序的第一个位置（插入后其和其后数后移）。指向键值>=key的第一个元素
lower_bound(v.begin(),v.end(),key);
///可以插入value，而不会破坏容器顺序的最后一个位置（插入后其和其后数后移）。指向键值>key的第一个元素
upper_bound(v.begin(),v.end(),key);
///将容器内元素按pred条件分开，pred为1的在前，返回分开处end()迭代器
partition(v.begin(),v.end(),pred);
stable_partition(v.begin(),v.end(),pred);
///求两个容器内积，返回sum+内积
inner_product(v1.begin(),v1.end(),v2.begin(),sum);
///对容器内元素求和，返回sum+和
accumulate(v.begin(),v.end(),sum);
///返回容器内元素的最大/最小值
max_element(v.begin(),v.end());
min_element(v.begin(),v.end());
///重新排列容器内的元素，找到第n小的元素，并把它放在iter_of_nth的位置上，使得在它之前没有大于它的元素，在它之后没有小于它的元素（iter_of_nth隐含着n的值）
nth_element(v.begin(),iter_of_nth,v.end());
///将容器内元素都赋值为key
fill(v.begin(),v.end(),key);
///交换区间 [__first,__middle) [__middle,__last)
rotate(__first,__middle,__last);
///打乱容器内元素的排列顺序
random_shuffle(v.begin(),v.end());
///将字符串以base进制转换成long，并通过ed得到一个char *指向后面未被识别的第一个字符
long strtol(const char *s, char **ed, int base);
///将字符串str1用str2中的字符分隔开。第一次调用传入str1，以后传入NULL。全部分隔完时返回NULL
char *strtok(char *str1, const char *str2);
/**
    char str[] = "now # is the $time for all # good men to co$$me to the # aid of the$ir country";
    char delims[] = "#$";
    char *result = NULL;
    result = strtok(str, delims);
    while(result != NULL)
    {
        printf("result is \"%s\"\n", result);
        result = strtok(NULL, delims);
    }
    运行结果：
    result is "now "
    result is " is the "
    result is "time for all "
    result is " good men to co"
    result is "me to the "
    result is " aid of the"
    result is "ir country"
**/
