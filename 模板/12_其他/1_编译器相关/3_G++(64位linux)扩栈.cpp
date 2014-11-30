///只在会爆栈的函数前后使用汇编语句会更安全
///但要注意避免使用局部变量保存函数返回值
long rsp;
int main()
{
    int SIZE_OF_STACK = 256 << 20; // 256MB
    char *p = (char*)malloc(SIZE_OF_STACK) + SIZE_OF_STACK;
    __asm__("movq %%rsp, %0" :: "m"(rsp));
    __asm__("movq %0, %%rsp" :: "r"(p));

    //程序体

    __asm__("movq %0, %%rsp\n" :: "m"(rsp));
    return 0;
}
