#include "minishell.h"

int ft_strstr(const char* haystack, const char* needle)
{
    const char *h;
    const char *n;
    int i;

    i = 0;
    while (haystack[i])
    {
        if (haystack[i] == *needle)
        {
            h = haystack;
            n = needle;
            while (*n && *h == *n)
            {
                h++;
                n++;
            }
            if (*n)
                return (i);
        }
        i++;
    }
    return (-1);
}
