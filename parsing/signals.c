/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:19:38 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/25 14:34:50 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	siginthandler1(int sig_num)
{
	(void) sig_num;
		g_msv.exit_status = 1;
	if (g_msv.in_proc_active && !g_msv.in_heredoc)
	{
		g_msv.exit_status = 131;
		write(1, "Quit: 3\n", 9);
	}
	else //if (g_msv.in_heredoc)
		{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 2);
		}
	// else
	// 	write(1, "\033[1;35mminishell $ \033[0m", 24);
}

void	siginthandler(int sig_num)
{
	(void) sig_num;
	g_msv.exit_status = 1;
	if (g_msv.in_proc_active)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_msv.exit_status = 130;
	}
	else if (g_msv.in_heredoc)
	{
		g_msv.in_heredoc = 0;
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 2);
		 write(1, "\n", 1);
	}
	else
	{
		rl_on_new_line();
			rl_redisplay();
			write(2, "  \n", 3);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			// rl_on_new_line();
			// rl_redisplay();
			// ft_putstr_fd("  \b\b", 2);
			// write(1, "\n", 1);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
}
