int SIZE_OF_STACK = 256 << 20; // 256MB
char *p = (char*)malloc(SIZE_OF_STACK) + SIZE_OF_STACK;
__asm__("movl %0, %%esp\n" :: "r"(p));
