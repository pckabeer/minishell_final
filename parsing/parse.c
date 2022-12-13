/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:05:07 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/13 20:03:08 by kpanikka         ###   ########.fr       */
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
		cbd[g_msv.i].cmd[ic] = parse_expand(g_msv.i, cbd[g_msv.i].cmd[ic]);
	ic = -1;
	while (cbd[g_msv.i].input[++ic])
		cbd[g_msv.i].input[ic] \
			= parse_expand_io(g_msv.i, cbd[g_msv.i].input[ic]);
	ic = -1;
	while (cbd[g_msv.i].output[++ic])
		cbd[g_msv.i].output[ic] \
			= parse_expand_io(g_msv.i, cbd[g_msv.i].output[ic]);
}

void	parse(void)
{
	t_cblock	*cbd;

	if (g_msv.parse_error)
		return ;
	parse_count_pipe();
	g_msv.cmd_arr = ft_split(g_msv.rline, 2);
	g_msv.i = -1;
	printf("num pipes : %d \n", g_msv.num_pipe + 1);
	g_msv.cmd_block_arr = calloc(sizeof(t_cblock), g_msv.num_pipe + 1);
	cbd = g_msv.cmd_block_arr;
	while (g_msv.cmd_arr[++g_msv.i])
	{
		if(g_msv.i>1)
			cbd[g_msv.i-1].next = &cbd[g_msv.i];
		init_t_cblock(&cbd[g_msv.i]);
		g_msv.cmd_arr[g_msv.i] = ft_strtrim(g_msv.cmd_arr[g_msv.i], " ");
		tblock_counter(&cbd[g_msv.i], g_msv.cmd_arr[g_msv.i]);
		cbd[g_msv.i].input = ft_split(cbd[g_msv.i].input_h, 2);
		cbd[g_msv.i].output = ft_split(cbd[g_msv.i].output_h, 2);
		cbd[g_msv.i].cmd = ft_split(cbd[g_msv.i].cmd_h, 2);
		expand();
	}
}