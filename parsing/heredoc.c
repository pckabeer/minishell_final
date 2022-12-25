/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:55:35 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/25 15:13:19 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freehdoc(char *doc, char *fbuff)
{
	if (doc)
		free(doc);
	if (fbuff)
		free(fbuff);
}

void	hdoc_reader(char *doc, char *fbuff, int *i)
{
	(void)fbuff;
	g_msv.lsthdoc = *i + 1;
	g_msv.in_heredoc = 1;
	close(g_msv.hfd[0]);
	pipe(g_msv.hfd);
	while (1)
	{
		g_msv.hdline = readline("\033[1;35m> \033[0m");
		if (g_msv.hdline && g_msv.in_heredoc)
		{
			if (!ft_strncmp(doc, g_msv.hdline, ft_strlen(g_msv.hdline) + 1))
				break ;
			ft_putendl_fd(g_msv.hdline, g_msv.hfd[1]);
		}
		else
		{
			g_msv.lsthdoc = 0;
			close(g_msv.hfd[1]);
			g_msv.in_heredoc = 1;
			freehdoc(NULL, fbuff);
			return ;
		}
	}
}

char	*hdoc_close(char *fbuff)
{
	char	*temp;

	g_msv.in_heredoc = 0;
	temp = fbuff;
	fbuff = ft_itoa(g_msv.hfd[0]);
	free(temp);
	close(g_msv.hfd[1]);
	return (ft_strjoin("<<", fbuff));
}

void	heredoc_init(void)
{
	g_msv.lsthdoc = 0;
	pipe(g_msv.hfd);
}

void	heredoc(void)
{
	t_cblock	*cbd;
	int			i;

	i = -1;
	heredoc_init();
	cbd = g_msv.cmd_block_arr;
	while (cbd[g_msv.i].input[++i])
	{
		if (cbd[g_msv.i].input[i][0] == '<' && cbd[g_msv.i].input[i][1] == '<')
		{
			g_msv.b_temp = ft_strdup(&cbd[g_msv.i].input[i][2]);
			hdoc_reader(g_msv.b_temp, g_msv.fbuff, &i);
			if (!g_msv.lsthdoc)
				return ;
		}
	}
	if (g_msv.lsthdoc--)
	{
		g_msv.temp = cbd[g_msv.i].input[g_msv.lsthdoc];
		cbd[g_msv.i].input[g_msv.lsthdoc] = hdoc_close(g_msv.fbuff);
		freehdoc(g_msv.b_temp, g_msv.temp);
	}
}
