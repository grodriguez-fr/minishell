#include "../../headers/minishell.h"

int set_pwd(t_mini *mini, char *new_pwd)
{
    char    *old_pwd;
    char    *buffer;

    old_pwd = ft_strdup(get_env_value(mini, "PWD"));
    buffer = ft_strjoin("PWD=", new_pwd);
    if (!replace_or_add(mini, buffer))
        return (free(buffer), 0);
    free(buffer);
    buffer = ft_strjoin("OLDPWD=", old_pwd);
    free(old_pwd);
    if (!replace_or_add(mini, buffer))
        return (free(buffer), 0);
    free(buffer);
    return (1);
}

int change_wd(t_mini *mini, char *new_pwd)
{
    char    *clean;
    int     ret;

    clean = get_clean_path(new_pwd);
    if (chdir(clean) == -1)
        return (free(clean), perror("minishell : cd"), 0);
    ret = set_pwd(mini, clean);
    return (free(clean), ret);
}

int change_relative(t_mini *mini, char *arg)
{
    int     ret;
    char    *buffer;
    char    *new_wd;

    buffer = ft_strjoin(get_env_value(mini, "PWD"), "/");
    new_wd = ft_strjoin(buffer, arg);
    ret = change_wd(mini, new_wd);
    return (free(buffer), free(new_wd), ret);
}

int cd(t_mini *mini, t_exec *ex)
{
    int ret;

    if (!ex->args[1])
        ret = change_wd(mini, get_env_value(mini, "HOME"));
    else if (!ft_strncmp(ex->args[1], "-", 1))
        ret = change_wd(mini, get_env_value(mini, "OLDPWD"));
    else if (ex->args[1][0] == '/')
        ret = change_wd(mini, ex->args[1]);
    else
        ret = change_relative(mini, ex->args[1]);
    return (ret);
} 
