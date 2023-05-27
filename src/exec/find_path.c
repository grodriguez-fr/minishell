#include "../../headers/minishell.h"

void	free_split(char **splited)
{
	int	i;

	if (splited)
	{
		i = 0;
		while (splited[i])
			free(splited[i++]);
		free(splited);
	}
}

char	*get_env_value(t_mini *mini, char *key)
{
	t_env_p *current;

	current = mini->env;
	while (current)
	{
		if (!ft_memcmp(current->key, key, ft_strlen(key)) && \
            !ft_memcmp(current->key, key, ft_strlen(current->key)))
			return (current->value);	
		current = current->next;
	}
	return (NULL);
}

char	*find_in_path(char *path, char *cmd_name)
{
	DIR			*dir;
	struct dirent	*entry;

	dir = opendir(path);
	if (dir == NULL)
		return (NULL);

	entry = readdir(dir);
	while (entry)
	{
		if (!ft_memcmp(entry->d_name, cmd_name, ft_strlen(cmd_name)) \
			       	&& !ft_memcmp(entry->d_name, cmd_name, ft_strlen(entry->d_name)))
			return (closedir(dir), path);
		entry = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

char	*path_name(char *path, char *cmd_name)
{
	char	*res;
	char	*inter;

	inter = ft_strjoin(path, "/");
	if (!inter)
		return (NULL);
	res = ft_strjoin(inter, cmd_name);
	return (free(inter), res);
}

char	*find_path(t_mini *mini, char *cmd_name)
{
	char	**splited_env;
	char	*paths;
	char	*res;
	int 	i;

	paths = get_env_value(mini, "PATH");
    if (!paths)
    {
        return (NULL);
    }
	splited_env = ft_split(paths, ':');
	i = 0;
	while(splited_env && splited_env[i])
	{
		if (find_in_path(splited_env[i], cmd_name))
		{
			res = path_name(splited_env[i], cmd_name);
			return (free_split(splited_env), res);
		}
		i++;
	}
	return (free_split(splited_env), NULL);
}
