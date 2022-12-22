#include "minishell.h"

void	execute_cmd_start(t_cblock *t_cmd, t_env *env, t_msvar **mvar, int k)
{
	int		n;
	int		j;
	t_msvar	*tmp;
	int		i;

	i = k;
	tmp = *mvar;
	tmp->cmd_path = ft_split(ft_getenv("PATH", env), ':');
	n = tmp->cmd_num;
	tmp->pid = fork();
	if (tmp->pid == 0)
	{
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
		if (strcmp(tmp->cmd[0], "echo") == 0)
			echo_fn(tmp, env, mvar, i);
		else if (strcmp(tmp->cmd[0], "export") == 0)
		{
			ft_elstprint_exp(env);
			exit(1);
		}
		else if (strcmp(tmp->cmd[0], "pwd") == 0)
			pwdfn(tmp, env, mvar, i);		
		else if (strcmp(tmp->cmd[0], "env ") == 0)
		{
			ft_elstprint(env);
			exit(1);
		}
		else
		{
			execute_cmd(tmp, env, mvar, i);
		}
	}
	else
		exit (1);
}

void	execute_cmd(t_cblock *temp, t_env *env, t_msvar **mvar, int i)
{
	char	**ev;
	t_msvar	*tmp;

	(void) i;
	(void)*env;
	tmp = *mvar;
	tmp->cmd = get_cmd(mvar, temp->cmd[0]);
	if (!tmp->cmd)
	{
		if (ft_strrchr(temp->cmd[0], '/'))
			ft_putstr_fd(" : No such file or directory\n", 2);
		else
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putstr_fd(temp->cmd[0],2);
			ft_putstr_fd("\n", 2);
		}
		exit(1);
	}
	ev = env_to_str(g_msv.env_list);
//print_str(temp->cmd);

	if (execve((*mvar)->cmd, temp->cmd, ev) == -1)
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(temp->cmd[0], 2);
		perror("error_test:");
     g_msv.exit_status=errno;
   clean_exit();
	}
}
void print_str(char **str)
{
    int i;
    i=0;
    printf("\n----------------------\n");
    while(str[i])
    {
        printf("*****%s*****\n",str[i++]);

    }
}