/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:53:24 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/12 19:26:21 by kpanikka         ###   ########.fr       */
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

int	parse_split_gt(t_cblock *tcb, int i, int start, char *str)
{
	i++;
	if (str[i] == '>')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
		i++;
	tcb->output_h = tb_join(str, tcb->output_h, start, i);
	tcb->output_ctr++;
	return (i);
}

int	parse_split_lt(t_cblock *tcb, int i, int start, char *str)
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
	return (i);
}