/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:05:07 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/11 20:10:02 by kpanikka         ###   ########.fr       */
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
	while (msv->rline[msv->i++])
	{		
		if (msv->parse_error)
			return ;
		if (msv->rline[msv->i] == '\'')
			parse_quote_block(msv);
		else if (msv->rline[msv->i] == '"')
			parse_dquote_block(msv);
		else if (msv->rline[msv->i] == '>')
			parse_gt_block(msv);
		else if (msv->rline[msv->i] == '<')
			parse_lt_block(msv);
		else if (msv->rline[msv->i] == '|')
			parse_pipe_block(msv);
	}
}

void	parse(t_msvar *msv)
{
	parse_count_pipe(msv);
	if (msv->parse_error)
		return ;
	msv->cmd_arr = ft_split(msv->rline, 2);
	msv->i = -1;
	printf("num pipes : %d \n", msv->num_pipe + 1);
	msv->cmd_block_arr = calloc(sizeof(t_cblock),msv->num_pipe + 1);
	//malloc(sizeof(t_cblock) * (msv->num_pipe + 1));
	while (msv->cmd_arr[++msv->i])
	{
		init_t_cblock(&msv->cmd_block_arr[msv->i]);
		tblock_counter(&msv->cmd_block_arr[msv->i], msv->cmd_arr[msv->i]);
		printf("input : %d -- output : %d  --command : %d\n", msv->cmd_block_arr[msv->i].input_ctr, msv->cmd_block_arr[msv->i].output_ctr ,msv->cmd_block_arr[msv->i].cmd_ctr);
		// printf("%d -- %s\n", msv->i, msv->cmd_arr[msv->i]);
	}
}