/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:05:07 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/24 04:33:24 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_split_elements(void)
{
	while (g_msv.rline[g_msv.i++])
	{
		if (g_msv.parse_error)
			return ;
		if (g_msv.parse_error == 1)
			break ;
		if (g_msv.rline[g_msv.i] == '\'')
			parse_quote_block();
		else if (g_msv.rline[g_msv.i] == '"')
			parse_dquote_block();
		else if (g_msv.rline[g_msv.i] == '$')
			parse_dollar_block();
		else if (g_msv.rline[g_msv.i] == '>')
			parse_gt_block();
		else if (g_msv.rline[g_msv.i] == '<')
			parse_lt_block();
		else if (g_msv.rline[g_msv.i] == '|')
			parse_pipe_block();
	}
	g_msv.w_len = 0;
}

void	parse_count_pipe(void)
{
	while (g_msv.rline[g_msv.i])
	{
		if (g_msv.parse_error)
			return ;
		if (g_msv.rline[g_msv.i] == '\'')
			parse_split_q();
		else if (g_msv.rline[g_msv.i] == '"')
			parse_split_dq();
		else if (g_msv.rline[g_msv.i] == '>')
			parse_gt_block();
		else if (g_msv.rline[g_msv.i] == '<')
			parse_lt_block();
		else if (g_msv.rline[g_msv.i] == '|')
			parse_pipe_block();
		g_msv.i++;
	}
}

void	expand(void)
{
	t_cblock	*cbd;
	int			ic;

	if (g_msv.parse_error)
		return ;
	cbd = g_msv.cmd_block_arr;
	ic = -1;
	while (cbd[g_msv.i].cmd[++ic])
		cbd[g_msv.i].cmd[ic] \
			= ft_strjoinchr(parse_expand(g_msv.i, cbd[g_msv.i].cmd[ic]), '\0');
	ic = -1;
	while (cbd[g_msv.i].input[++ic])
		cbd[g_msv.i].input[ic] \
			= ft_strjoin(parse_expand_io(g_msv.i, cbd[g_msv.i].input[ic]), "");
	ic = -1;
	while (cbd[g_msv.i].output[++ic])
		cbd[g_msv.i].output[ic] \
			= ft_strjoin(parse_expand_io(g_msv.i, cbd[g_msv.i].output[ic]), "");
}

void	heredoc()
{
	t_cblock	*cbd;
	char		*line;
	char		*doc;
	int i = -1;
	int hfd[2];
	int lsthd = 0;
	char *fbuff = calloc(1024,1);
	pipe(hfd);

	cbd = g_msv.cmd_block_arr;
	//print_str(cbd[g_msv.i].input);
	while (cbd[g_msv.i].input[++i])
	{
		//	printf("hi all ---%s\n",cbd[g_msv.i].input[i]);
		if (cbd[g_msv.i].input[i][0] == '<' && cbd[g_msv.i].input[i][1] == '<')
		{
			g_msv.in_heredoc = 1;
			lsthd = i + 1;
			doc = ft_strdup(&cbd[g_msv.i].input[i][2]);
			close(hfd[0]);
			pipe(hfd);
			while (1)
			{
															// write(1, "QPCK: 8\n", 9);

				line = readline("\033[1;35m> \033[0m");
											// write(1, "QPCK: 7\n", 9);
				if(line && g_msv.in_heredoc)
				{							
					// write(1, "QPCK: 6\n", 9);

					if (!ft_strncmp(doc, line, ft_strlen(line) + 1))
						break ;
					ft_putendl_fd(line, hfd[1]);
				}
				else
				{
							// write(1, "QPCK: 4\n", 9);

					lsthd = 0;
					close(hfd[1]);
										g_msv.in_heredoc = 1;

					return ;
				}
			}
		}
	}
	if(lsthd--)
	{
							g_msv.in_heredoc = 0;

		fbuff = ft_itoa(hfd[0]);
		close(hfd[1]);
		cbd[g_msv.i].input[lsthd] = ft_strjoin("<<", fbuff);
		// printf("test ----%s",cbd[g_msv.i].input[lsthd]);

	}
}

void	parse(void)
{
	t_cblock	*cbd;

	if (g_msv.parse_error)
		return ;
	parse_count_pipe();

	g_msv.cmd_arr = ft_split(g_msv.rline, 2);
	g_msv.i = -1;
	g_msv.cmd_block_arr = calloc(sizeof(t_cblock), g_msv.num_pipe + 1);
	cbd = g_msv.cmd_block_arr;
	while (g_msv.cmd_arr[++g_msv.i])
	{
		if (g_msv.i >= 1)
			cbd[g_msv.i - 1].next = &cbd[g_msv.i];
		init_t_cblock(&cbd[g_msv.i]);
		g_msv.temp = g_msv.cmd_arr[g_msv.i];
		g_msv.cmd_arr[g_msv.i] = ft_strtrim(g_msv.cmd_arr[g_msv.i], " ");
		free(g_msv.temp);
		tblock_counter(&cbd[g_msv.i], g_msv.cmd_arr[g_msv.i]);
		cbd[g_msv.i].input = ft_split(cbd[g_msv.i].input_h, 2);
		cbd[g_msv.i].output = ft_split(cbd[g_msv.i].output_h, 2);
		cbd[g_msv.i].cmd = ft_split(cbd[g_msv.i].cmd_h, 2);
		expand();
		heredoc();
		if (g_msv.in_heredoc)
			break ;
		printf("input : %d -- output : %d  --command : %d\n",
			cbd[g_msv.i].input_ctr,
			cbd[g_msv.i].output_ctr,
			cbd[g_msv.i].cmd_ctr);
	}
}