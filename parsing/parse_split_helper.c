/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:53:24 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/24 21:30:31 by kpanikka         ###   ########.fr       */
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
					// printf("hi all <---%s\n",tcb->input_h);
	tcb->input_ctr++;
	return (i);
}

int	parse_split_lt(t_cblock *tcb, int i, int start, char *str)
{
	char *temp;
	
	i++;
	if (str[i] == '<')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
		i++;
	temp = tcb->input_h;
	tcb->input_h = tb_join(str, tcb->input_h, start, i);					
	tcb->input_ctr++;
						// printf("hi all <---%s\n",tcb->input_h);

	// free(temp);
	return (i);
}

int	parse_split_qh(t_cblock *tcb, int i, int start, char *str)
{
	char *temp;
	
	i++;
	while (str[i] && str[i] != '\'')
		i++;
	i++;
	temp = tcb->cmd_h;
	
	tcb->cmd_h = tb_join(str, tcb->cmd_h, start, i);
	//ft_putendl_fd(tcb->cmd_h, 1);
	tcb->cmd_ctr++;
	// free(temp);
	return (i);
}

int	parse_split_dqh(t_cblock *tcb, int i, int start, char *str)
{
	char *temp;
	
	i++;
	while (str[i] && str[i] != '"')
		i++;
	i++;
	temp = tcb->cmd_h;
	tcb->cmd_h = tb_join(str, tcb->cmd_h, start, i);
	tcb->cmd_ctr++;
	// free(temp);
	return (i);
}

int	parse_split_h(t_cblock *tcb, int i, int start, char *str)
{
	char *temp;
	i++;
	while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	temp = tcb->cmd_h;
	tcb->cmd_h = tb_join(str, tcb->cmd_h, start, i);
	tcb->cmd_ctr++;
	// if(temp)
		//free(temp);
	return (i);
}

int	parse_split_dlr(t_cblock *tcb, int i, int start, char *str)
{
	char *new_str;

	new_str = "";
	i++;
	if (str[i])
	{	
		while (str[i] && str[i] == ' ')
			i++;
		if(!ft_strchr( "?\"'$>< ",str[i]))
		{
			new_str = ft_strstr(str + i, "\"'$>< ");
			if (new_str)
				i += (int)(new_str - (str + start));
			else
				i += (int) ft_strlen((str + start));
		}
	}
	new_str = tcb->cmd_h;
	tcb->cmd_h = tb_join(str, tcb->cmd_h, start, i);
	tcb->cmd_ctr++;
	return (i);
}
