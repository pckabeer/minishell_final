/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:53:24 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/24 04:13:17 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_split_gt(t_cblock *tcb, int i, int start, char *str)
{
	i++;
	if (str[i] == '>')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
		i++;

	tcb->input_h = tb_join(str, tcb->input_h, start, i);
					printf("hi all <---%s\n",tcb->input_h);
	tcb->input_ctr++;
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
	// printf("Variables : str - %s, start - %d, i - %d \n",str,start,i);
	tcb->input_h = tb_join(str, tcb->input_h, start, i);					
	// printf("hi all <---%s\n",tcb->input_h);

	tcb->input_ctr++;
	return (i);
}

int	parse_split_qh(t_cblock *tcb, int i, int start, char *str)
{
	i++;
	while (str[i] && str[i] != '\'')
		i++;
	i++;
	tcb->cmd_h = tb_join(str, tcb->cmd_h, start, i);
	tcb->cmd_ctr++;
	return (i);
}

int	parse_split_dqh(t_cblock *tcb, int i, int start, char *str)
{
	i++;
	while (str[i] && str[i] != '"')
		i++;
	i++;
	tcb->cmd_h = tb_join(str, tcb->cmd_h, start, i);
	tcb->cmd_ctr++;
	return (i);
}

int	parse_split_h(t_cblock *tcb, int i, int start, char *str)
{
	i++;
	while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	tcb->cmd_h = tb_join(str, tcb->cmd_h, start, i);
	tcb->cmd_ctr++;
	return (i);
}

int	parse_split_dlr(t_cblock *tcb, int i, int start, char *str)
{
	char *new_str;

	printf("i = %d\n", i);
	if (!str[i+1])
		return (0);
	while (str[i] && str[i] == ' ')
		i++;
	if (ft_strnstr(str + start, "?\"'$>< ", 1))
		i++;//return (++i);
	new_str = ft_strnstr(str+start, "?\"'$>< ", ft_strlen(str+start));
	if (new_str)
		i += ft_strlen((const char *)(new_str - (str+start)));
	else
		i += ft_strlen(str+start);
	printf("i = %d, str = %s, start = %d\n", i, str, start);
	tcb->cmd_h = tb_join(str, tcb->cmd_h, start, i);
	printf("tcb->cmd_h = %s\n", tcb->cmd_h);
	tcb->cmd_ctr++;
	return (i);
}
