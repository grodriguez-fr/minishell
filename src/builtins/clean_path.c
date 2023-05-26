#include "../../headers/minishell.h"

char*   get_clean_path(char* path)
{
    char    ** tokens;
    char    *new_path;
    char    *last_slash;
    int     i;


    tokens = ft_split(path, '/');
    new_path = (char*)malloc(ft_strlen(path) + 1);
    new_path[0] = 0;
    i = 0;
    while (tokens[i])
    {
        if (ft_strncmp(tokens[i], "..", 2) == 0 && \
            ft_strncmp(tokens[i], "..", ft_strlen(tokens[i])) == 0)
        {
            last_slash = ft_strrchr(new_path, '/');
            if (last_slash)
                *last_slash = 0;
        }
        else if (ft_strncmp(tokens[i], ".", 1) != 0 && \
            ft_strncmp(tokens[i], ".", ft_strlen(tokens[i])) == 0)
        {
            ft_strlcat(new_path, "/", ft_strlen(path) + 1);
            ft_strlcat(new_path, tokens[i], ft_strlen(path) + 1);
        }
        i++;
    }
    free_split(tokens);
    return (new_path);
}
