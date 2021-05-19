# include "ft_mem.h"

void    *ft_memrev(void *p, size_t len)
{
    size_t i;
    char c;
    unsigned char *up;

    i = 0;
    c = 0;
    up = (unsigned char *)p;
    len -= 1;
    while (i < len)
    {
        c = up[i];
        up[i++] = up[len];
        up[len--] = c;
    }
    return (p);
}
