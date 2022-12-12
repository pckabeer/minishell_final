/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:25:16 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/12 19:42:08 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_split_q(t_msvar *msv)
{
	msv->i++;
	while (msv->rline[msv->i] != '\'' && msv->rline[msv->i] != '\0')
		msv->i++;
	if (msv->rline[msv->i] != '\'')
		msv->parse_error = 2;
}

void	parse_split_dq(t_msvar	*msv)
{
	msv->i++;
	while (msv->rline[msv->i] != '"' && msv->rline[msv->i] != '\0')
		msv->i++;
	if (msv->rline[msv->i] != '"')
		msv->parse_error = 3;
}

void	init_t_cblock(t_cblock *tcb)
{
	tcb->cmd = NULL;
	tcb->input = NULL;
	tcb->output = NULL;
	tcb->cmd_h = NULL;
	tcb->input_h = NULL;
	tcb->output_h = NULL;
	tcb->output_ctr = 0;
	tcb->input_ctr = 0;
	tcb->cmd_ctr = 0;
	//tcb->delimit = (char) 2;
}

char	*tb_join(char *str, char *output, int start, int i)
{
	char	*tmp;

	tmp = calloc(2, 1);
	tmp[0] = 2;
	if (output)
	{
		output = ft_strjoin(output, tmp);
		output = ft_strjoin(output, ft_substr(str, start, (i - start)));
	}
	else
		output = ft_strdup(ft_substr(str, start, (i - start)));
	return (output);
}

void	tblock_counter(t_cblock *tcb, char *str)
{
	int	i;
	int	start;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
				i++;
		start = i;
		if (str[i] == '<')
			i = parse_split_lt(tcb, i, start, str);
		else if (str[i] == '>')
			i = parse_split_gt(tcb, i, start, str);
		else if (str[i] == '\'')
			i = parse_split_qh(tcb, i, start, str);
		else if (str[i] == '"')
			i = parse_split_dqh(tcb, i, start, str);
		else
			i = parse_split_h(tcb, i, start, str);
		if (str[i] == '\0')
			break ;
	}
}
