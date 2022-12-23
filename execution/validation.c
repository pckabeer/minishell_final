#include "minishell.h"

/*char	*check_cmd(char *cmd_path, char *cmd, t_list *pipex)
{
	init_list(pipex);
	if (cmd[0] == '/')
	{
		while (cmd[pipex->i] != '/' && cmd[pipex->i] != '\0')
			pipex->i++;
		pipex->cmd_check = ft_substr(cmd, 1, (pipex->i - 1));
		pipex->n = ft_strrchr(cmd_path, '/');
		pipex->i = (pipex->n - cmd_path) + 1;
		pipex->j = 0;
		while (cmd_path[pipex->i++] != '\0')
			pipex->j++;
		pipex->i = (pipex->n - cmd_path) + 1;
		pipex->path_check = ft_substr(cmd_path, pipex->i, pipex->j);
		if (ft_strcmp(pipex->cmd_check, pipex->path_check) == 0)
		{
			pipex->n = ft_strrchr(cmd_path, '/');
			pipex->i = pipex->n - cmd_path;
			pipex->tmp = ft_substr(cmd_path, 0, pipex->i);
		}
		free(pipex->cmd_check);
		free(pipex->path_check);
	}
	return (pipex->tmp);
}
*/
char	*get_cmd(t_msvar **mvar, char *cmd)
{
	char	*tmp;
	int		i;
t_msvar *temp;
temp  = *mvar;
	i = 0;
    cmd=ft_strtrim(cmd," ");
  

 if (cmd[0] == '/')
 {
        tmp =  ft_strdup(cmd);
		if (access(tmp, X_OK) == 0)
			return (tmp);     
       free(tmp);

 }
        else
        {
		if(temp->cmd_path)
{
	while (temp->cmd_path[i])
	{
		temp->temp = NULL;
       
        tmp = ft_strjoin(temp->cmd_path[i], "/");
        temp->temp = tmp;
        tmp = ft_strjoin(tmp, cmd);
        if (temp->temp)
			free(temp->temp);
		if (access(tmp, X_OK) == 0)
			return (tmp);     
       free(tmp);
		i++;
    }  
}  
		}
	return (NULL);
}
