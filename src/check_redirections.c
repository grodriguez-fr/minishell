#include "../headers/minishell.h"

int file_in(char **files)
{
    int fd;
    int i;

    i = 0;
    while (files && files[i])
    {
        fd = open(files[i], O_RDONLY);
        if (fd == -1) 
            return (perror("Erreur lors de l'ouverture du fichier"), 0);
        close(fd);
        i++;
    }
    return (1);
}

int file_out(char **files)
{
    int fd;
    int i;

    i = 0;
    while (files && files[i])
    {
        fd = open(files[i], O_WRONLY | O_CREAT | O_APPEND);
        if (fd == -1)
            return (perror("Erreur lors de l'ouverture du fichier"), 0);
        close (fd);
        i++;
    }
    return (1);
}

int check_redirection(t_exec *current)
{
    if (!file_out(current->files_out))
        return (0);
    if (!file_in(current->files_in))
        return (0);
    if (!file_out(current->files_out_a))
        return (0);
    //file_in
    //file_out_append
    //heredoc
    return (1);
}
