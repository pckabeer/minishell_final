/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:12:03 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/24 22:17:28 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The function read_loop does a clean exit for the program 
*/
void	init_minishell(void)
{
	g_msv.rline = NULL;
	g_msv.cmd_num = 0;
	g_msv.num_pipe = 0;
	g_msv.parse_error = 0;
	g_msv.w_len = 0;
	g_msv.w_count = 0;
	g_msv.exit_flag = 0;
	g_msv.block_list = NULL;
	//g_msv.env_list = NULL;
	g_msv.output = ft_calloc(32767, 1);
	g_msv.temp = NULL;
	g_msv.b_temp = NULL;
	g_msv.i = 0;
	g_msv.cmd_arr = NULL;
	g_msv.delimit = DELIMIT;
	g_msv.in_heredoc = 0;
	g_msv.in_proc_active = 0;
}

/*
*  The function read_loop  reads line from the command line and then 
*  processes it
* 
*/

void	read_loop_helper(void)
{
	bool	flag;

	flag = true;
	if (flag)
	{
		g_msv.rline = readline("\033[1;35mminishell $ \033[0m");
							// write(1, "Quit: 3333\n", 9);
		flag = false;
	}
	if (g_msv.rline)
	{
		if (!ft_strlen(ft_strtrim(g_msv.rline, " ")))
			g_msv.parse_error = 121;

		if (ft_strlen(g_msv.rline))
			add_history(g_msv.rline);
	}
	else
		clean_exit();
	g_msv.temp = g_msv.rline;
	g_msv.rline = ft_strtrim(g_msv.temp, " ");
	free(g_msv.temp);
}

int	read_loop(void)
{
	while (1)
	{
		read_loop_helper();
		// continue ;

		parse();
		if (!g_msv.in_heredoc)
		{
			if (!g_msv.parse_error)
			{
				g_msv.in_proc_active = 1;

				execution(g_msv.cmd_block_arr, g_msv.env_list, &g_msv);
			}
			else
				parse_error();
		}
		g_msv.temp = g_msv.rline;
		free(g_msv.temp);
		free(g_msv.output);
		init_minishell();
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	signal(SIGQUIT, siginthandler1);
	signal(SIGINT, siginthandler);
	init_minishell();
	load_env(env);
	read_loop();
	return (0);
}
