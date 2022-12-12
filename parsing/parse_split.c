/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:25:16 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/12 19:25:13 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

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
		{
		// 	i++;
		// 	if (str[i] == '<')
		// 		i++;
		// 	while (str[i] && str[i] == ' ')
		// 		i++;
		// 	while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
		// 		i++;
		// 	tcb->input_h = tb_join(str, tcb->input_h, start, i);
		// 	tcb->input_ctr++;
			i = parse_split_lt(tcb, i, start, str);
		}
		else if (str[i] == '>')
		{
			// i++;
			// if (str[i] == '>')
			// 	i++;
			// while (str[i] && str[i] == ' ')
			// 	i++;
			// while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
			// 	i++;
			// tcb->output_h = tb_join(str, tcb->output_h, start, i);
			// tcb->output_ctr++;
			i = parse_split_gt(tcb, i, start, str);
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
			tcb->cmd_h = tb_join(str, tcb->cmd_h, start, i);
			tcb->cmd_ctr++;
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			i++;
			tcb->cmd_h = tb_join(str, tcb->cmd_h, start, i);
			tcb->cmd_ctr++;
		}
		else
		{
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
				i++;
			while (str[i] && str[i] == ' ')
				i++;			
			tcb->cmd_h = tb_join(str, tcb->cmd_h, start, i);
			tcb->cmd_ctr++;
		}
		if (str[i] == '\0')
			break ;
	}
}
