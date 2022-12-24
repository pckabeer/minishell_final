/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:42:15 by skabeer           #+#    #+#             */
/*   Updated: 2022/12/24 03:55:00 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(t_msvar **mvar)
{
	t_msvar	*tmp;
	int		n;
	int		i;

	tmp = *mvar;
	n = tmp->cmd_num;
	if (n > 1)
	{
		tmp->fd = (int **)malloc(sizeof(int *) * n);
		if (!tmp->fd)
		{
			perror("error_test:");
			g_msv.exit_status=errno;
			clean_exit();
		}
		i = 0;
		while (i < n)
		{
			tmp->fd[i] = (int *)malloc(sizeof(int) * 2);
			if (!tmp->fd[i])
			{
				perror("error_test:");
     g_msv.exit_status=errno;
   clean_exit();
			}
			i++;
		}
	}
}

int	init_io(t_cblock *t_cmd, t_msvar **mvar)
{
	t_msvar	*tmp;
	int i;

	i = 0;

	tmp = *mvar;

	if(t_cmd->input)
	{
		while(t_cmd->input[i])
		{
			if(t_cmd->input[i][0] == '<')
			{
				tmp->f1=check_input(t_cmd->input[i]);
				if (tmp->f1 == -1)
			return (0);
			}
			else if(t_cmd->input[i][0] == '>')
			{
				tmp->f2 =check_output(t_cmd->input[i]);
				if (tmp->f2 == -1)
			return (0);
			}
			i++;
		}
		
}
return (1);
}
   /* {
	]
	
	if (t_cmd->output)
	{
		tmp->f2 = check_output(t_cmd->output);
		if (tmp->f2 == -1)
			return (0);
	}

	if (t_cmd->input)
	{
		tmp->f1 = check_input(t_cmd->input);
		if (tmp->f1 == -1)
			return (0);
	}
	return (1);
}*/

void	mvar_init(t_msvar **mvar)
{
	(*mvar)->f1 = -1;
	(*mvar)->f2 = -1;
	(*mvar)->cmd_num = (*mvar)->num_pipe + 1;
	//g_msv.exit_status=0;
}


void	execution(t_cblock *t_cmd, t_env *env, t_msvar *mvar)
{
	t_cblock	*tmp;
	int			i;
	int status;
		(void)env;
	//	print_str(t_cmd->input);
	//printf("\n------%d----\n",g_msv.exit_status);
	mvar_init(&mvar);
	create_pipe(&mvar);
	tmp = t_cmd;
	i = 0;
	
	
	while (tmp)
	{
		if (mvar->cmd_num > 1)
		{
			if (pipe(mvar->fd[i]) == -1)
			{
				perror("error_test:");
     g_msv.exit_status=errno;
  return ;
			}
		}
		mvar_init(&mvar);
		if(!init_io(tmp, &mvar))
		{
			g_msv.exit_status=errno;
			return;
		}


		if (mvar->cmd_num >= 1)
		{
		if ((strcmp(tmp->cmd[0], "export") == 0) && tmp->cmd[1])
		{
			export_fn(tmp);
			tmp = tmp->next;
			i++;
			continue ;
		}
		else if (strcmp(ft_strtrim(tmp->cmd[0]," "), "cd") == 0)
		{
			
			if (mvar->cmd_num == 1)
				cd_fn(tmp,env);
			tmp = tmp->next;
			i++;
			continue ;
		}
		else if(strcmp(tmp->cmd[0], "unset") == 0)
		{
			
			unset_fn(tmp,env);
			tmp = tmp->next;
			i++;
			continue ;
		}
		else if(strcmp(tmp->cmd[0], "exit") == 0)
		{
			exit(0);
		}

	//	print_str(tmp->cmd);
		//print_str(tmp->output);

		else
			execute_cmd_start(tmp, env, &mvar, i);
		}

	if ((mvar)->f1 > -1)
			close((mvar)->f1);
		if ((mvar)->f2 > -1)
			close((mvar)->f2);

	if (mvar->cmd_num > 1)
		{
			if (i > 0)
				close((mvar)->fd[i - 1][0]);
			close((mvar)->fd[i][1]);
			//printf("checking ----%d",i);
		}
	
		i++;
		tmp = tmp->next;
	}


	while (waitpid(-1, &(status), 0) > 0)
			;
		g_msv.exit_status=WEXITSTATUS(status);
	return ;
}




int ft_minusn(char *str)
{
	int	i;

	i = 0;
	str = ft_strtrim(str, " ");
	if(str[i++] == '-')
	{
		while (str[i])
		{
			if(str[i++] != 'n')
				return(0);
		}
		return(1);
	}
	return(0);
}
