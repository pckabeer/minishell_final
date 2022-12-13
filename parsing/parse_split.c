/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:25:16 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/13 13:41:39 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_split_q(void)
{
	g_msv.i++;
	while (g_msv.rline[g_msv.i] != '\'' && g_msv.rline[g_msv.i] != '\0')
		g_msv.i++;
	if (g_msv.rline[g_msv.i] != '\'')
		g_msv.parse_error = 2;
}

void	parse_split_dq(void)
{
	g_msv.i++;
	while (g_msv.rline[g_msv.i] != '"' && g_msv.rline[g_msv.i] != '\0')
		g_msv.i++;
	if (g_msv.rline[g_msv.i] != '"')
		g_msv.parse_error = 3;
}

void	init_t_cblock(t_cblock *tcb)
{
	tcb->cmd = NULL;
	tcb->input = NULL;
	tcb->output = NULL;
	tcb->cmd_h = "";
	tcb->input_h = "";
	tcb->output_h = "";
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

	if (g_msv.parse_error)
		return ;
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
