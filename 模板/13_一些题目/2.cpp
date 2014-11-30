for (int i=0; i<m; i++)
{
    ///TODO: adde
    int x,y;
    char c1,c2;
    scanf("%d%c%d%c",&x,&c1,&y,&c2);
    x++,y++;
    if (c1=='h'&&c2=='h')
    {
        adde(x+n,y);
        adde(y+n,x);
    }
    else if (c1=='h'&&c2=='w')
    {
        adde(x+n,y+n);
        adde(y,x);
    }
    else if (c1=='w'&&c2=='h')
    {
        adde(x,y);
        adde(y+n,x+n);
    }
    else
    {
        adde(x,y+n);
        adde(y,x+n);
    }
}
