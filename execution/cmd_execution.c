#include "minishell.h"

void	execute_cmd_start(t_cblock *t_cmd, t_env *env, t_msvar **mvar, int k)
{
	int		n;
	int		j;
	t_msvar	*tmp;
	int		i;

	i = k;
	tmp = *mvar;
	env = g_msv.env_list;

	
	tmp->cmd_path = ft_split(ft_getenv("PATH", env), ':');

	
	n = tmp->cmd_num;
	tmp->pid = fork();
	if (tmp->pid == 0)
	{
	//	printf("\n*****%d*******",k);
		i = k;
		j = k - 1;
		if ((tmp->f1 > -1))
			dup2(tmp->f1, 0);
		else if ((j) > -1)
			dup2(tmp->fd[j][0], 0);
		if (tmp->f2 > -1)
			dup2(tmp->f2, 1);
		else if (n > 1 && k != (n - 1))
			dup2(tmp->fd[i][1], 1);
		execute_cmd_redirect(t_cmd, env, mvar, i);
	}

}

void	execute_cmd_redirect(t_cblock *tmp, t_env *env, t_msvar **mvar, int i)
{
	if (tmp->cmd)
	{
		//ft_putstr_fd(tmp->cmd[0],2);
		tmp->cmd[0]= ft_strtrim(tmp->cmd[0]," ");

		if (strcmp(tmp->cmd[0], "echo") == 0)
			echo_fn(tmp, env, mvar, i);
		else if (strcmp(tmp->cmd[0], "export") == 0)
		{
			ft_elstprint_exp(env);
			exit(1);
		}
		else if (strcmp(tmp->cmd[0], "pwd") == 0)
			pwdfn(tmp, env, mvar, i);		
		else if (strcmp(tmp->cmd[0], "env") == 0)
		{
			ft_elstprint(env);
		//	ft_putstr_fd("\n",1);
			exit(1);
		}
		else
		{
			execute_cmd(tmp, env, mvar, i);
		}
	}
	else
		return ;
}

void	execute_cmd(t_cblock *temp, t_env *env, t_msvar **mvar, int i)
{
	char	**ev;
	t_msvar	*tmp;

	(void) i;
	(void)*env;
	tmp = *mvar;
	if(temp->cmd[0][0]=='.')
	{
		tmp->cmd=temp->cmd[0];
	}
	else
	tmp->cmd = get_cmd(mvar, temp->cmd[0]);
	if (!tmp->cmd)
	{
	//perror("test");
	
	//g_msv.exit_status=errno;
	//printf("--------------%d--------",g_msv.exit_status);
		if (ft_strrchr(temp->cmd[0], '/') )
			ft_putstr_fd(" : No such file or directory-----\n", 2);
		else
		{   
			ft_putstr_fd("command not found: ", 2);
			ft_putstr_fd(temp->cmd[0],2);
			ft_putstr_fd("\n", 2);
		}
		exit(127);
	}
	ev = env_to_str(g_msv.env_list);
//print_str(ev);

	if (execve((*mvar)->cmd, temp->cmd, ev) == -1)
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(temp->cmd[0], 2);
		perror("error_test:");
     g_msv.exit_status=errno;
	 exit(EXIT_FAILURE);
  // clean_exit();
	}
}
void print_str(char **str)
{
    int i;
    i=0;
   // printf("\n----------------------\n");
   if(str)
   {
    while(str[i])
    {
		ft_putnbr_fd(i,2);
		// printf("-- %s - len %zu\n", str[i], ft_strlen(str[i]));
		ft_putendl_fd(str[i++],2);

    }
   }
}