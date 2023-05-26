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
    //verifie si c'est bien un directory valide
    if (access(new_pwd, F_OK))
        return (perror("cd"), 0);
    return (set_pwd(mini, new_pwd));
}

int change_relative(t_mini *mini, char *arg)
{
    int     ret;
    char    *buffer;
    char    *new_wd;

    printf("chemin relatif\n");
    buffer = ft_strjoin(get_env_value(mini, "PWD"), "/");
    new_wd = ft_strjoin(buffer, arg);
    free(buffer);
    ret = change_wd(mini, new_wd);
    free(new_wd);
    return (ret);
}

int change_absolute(t_mini *mini, char *newpwd)
{
    int i;

    while (newpwd[i])
        i++;
    if (i >= 0 && newpwd[i - 1] == '/')
        newpwd[i - 1] = 0;
    return (change_wd(mini, newpwd));
}

int cd(t_mini *mini, t_exec *ex)
{
    int ret;

    if (!ex->args[1])
        ret = change_wd(mini, get_env_value(mini, "HOME"));
    else if (!ft_strncmp(ex->args[1], "-", 1))
        ret = change_wd(mini, get_env_value(mini, "OLDPWD"));
    else if (ex->args[1][0] == '/')
        ret = change_absolute(mini, ex->args[1]);
    else
        ret = change_relative(mini, ex->args[1]);
    //printf("cd from %s to %s\n", mini->env->value, ex->args[0]);
    return (ret);
} 
