/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:05:07 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/12 18:47:29 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_split_elements(t_msvar *msv)
{
	while (msv->rline[msv->i++])
	{			
		if (msv->parse_error)
			return ;
		if (msv->parse_error == 1)
			break ;
		if (msv->rline[msv->i] == '\'')
			parse_quote_block(msv);
		else if (msv->rline[msv->i] == '"')
			parse_dquote_block(msv);
		else if (msv->rline[msv->i] == '$')
			parse_dollar_block(msv);
		else if (msv->rline[msv->i] == '>')
			parse_gt_block(msv);
		else if (msv->rline[msv->i] == '<')
			parse_lt_block(msv);
		else if (msv->rline[msv->i] == '|')
			parse_pipe_block(msv);
	}
		msv->w_len = 0;
}

void	parse_count_pipe(t_msvar *msv)
{
	while (msv->rline[msv->i])
	{		
		if (msv->parse_error)
			return ;
		if (msv->rline[msv->i] == '\'')
			parse_split_q(msv);
		else if (msv->rline[msv->i] == '"')
			parse_split_dq(msv);
		else if (msv->rline[msv->i] == '>')
			parse_gt_block(msv);
		else if (msv->rline[msv->i] == '<')
			parse_lt_block(msv);
		else if (msv->rline[msv->i] == '|')
			parse_pipe_block(msv);
		msv->i++;
	}
}

void	parse(t_msvar *msv)
{
	int ic;
	//t_msvar *msv = msv1;
	t_cblock *cbd = msv->cmd_block_arr;
	parse_count_pipe(msv);
	if (msv->parse_error)
		return ;
	msv->cmd_arr = ft_split(msv->rline, 2);
	msv->i = -1;
	printf("num pipes : %d \n", msv->num_pipe + 1);
	cbd = calloc(sizeof(t_cblock),msv->num_pipe + 1);
	//malloc(sizeof(t_cblock) * (msv->num_pipe + 1));
	while (msv->cmd_arr[++msv->i])
	{
		init_t_cblock(&cbd[msv->i]);
		msv->cmd_arr[msv->i]= ft_strtrim(msv->cmd_arr[msv->i]," ");
		tblock_counter(&cbd[msv->i], msv->cmd_arr[msv->i]);
		cbd[msv->i].input = ft_split(cbd[msv->i].input_h, 2);
		cbd[msv->i].output = ft_split(cbd[msv->i].output_h, 2);
		cbd[msv->i].cmd = ft_split(cbd[msv->i].cmd_h, 2);
		ic = 0;
		while (cbd[msv->i].cmd[ic])
		{
			printf("-- %s \n",cbd[msv->i].cmd[ic]);
			ic++;
		}

		
		printf("input : %d -- output : %d  --command : %d\n", cbd[msv->i].input_ctr, cbd[msv->i].output_ctr ,cbd[msv->i].cmd_ctr);
		// printf("%d -- %s\n", msv->i, msv->cmd_arr[msv->i]);
	}
}