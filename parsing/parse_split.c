/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:25:16 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/12 16:36:26 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

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
	char	c;

	c = DELIMIT;
	if (output)
	{
		output = ft_strjoin(output, &c);
		output = ft_strjoin(output, ft_substr(str, start, i - start));
	}
	else
		output = ft_strdup(ft_substr(str, start, i - start));
	//printf(" string : %s\n",output);

	return(output);
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
			i++;
			if (str[i] == '<')
				i++;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
				i++;
			tcb->input_h = tb_join(str, tcb->input_h, start, i);
			tcb->input_ctr++;
		}
		else if (str[i] == '>')
		{
			// printf("2>start : %s\n",str+i);
			i++;
			if (str[i] == '>')
				i++;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
				i++;
			tcb->output_h = tb_join(str, tcb->output_h, start, i);
			tcb->output_ctr++;
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
			// printf("4>start : %s\n",str+i);
			i++;
			while (str[i] && str[i] != '"')
				i++;
			i++;
			// printf("4>end : %s\n",str+i);
			tcb->cmd_h = tb_join(str, tcb->cmd_h, start, i);
			tcb->cmd_ctr++;
		}
		else
		{
			// printf("5 - i : %d - %c\n", i, str[i]);
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