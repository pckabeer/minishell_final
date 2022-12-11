/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:25:16 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/12 01:28:44 by kpanikka         ###   ########.fr       */
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

// int	parse_count_q(char *str)
// {
// 	int i;
	
// 	i = 0;
// 	while (str[i] != '\'' && str[i] != '\0')
// 		i++;
// }

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
	tcb->output_ctr = 0;
	tcb->input_ctr = 0;
	tcb->cmd_ctr = 0;
}

void	tblock_counter(t_cblock *tcb, char *str)
{
	int	i;

	i = 0;
	
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
				i++;
		if (str[i] == '<')
		{
			printf("1");
			i++;
			if (str[i] == '<')
				i++;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
				i++;
			tcb->input_ctr++;
		}
		else if (str[i] == '>')
		{
			printf("2");
			i++;
			if (str[i] == '>')
				i++;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
				i++;
			tcb->output_ctr++;
		}
		else if (str[i] == '\'')
		{
			int j = i;
			char *tmp;
			i++;
			// printf("%s",ft_strchr((str+i),'\''));
			//tcb->cmd[0] =ft_substr(str,i,5);
			//printf("--- %s\n",tcb->cmd[0]);
			while (str[i] && str[i] != '\'')
				i++;
				tmp = ft_substr(str,j+1,i -j-1);
				printf("--- %s\n",tmp);
			i++;
			tcb->cmd_ctr++;
		}
		else if (str[i] == '"')
		{
			printf("4");
			i++;
			while (str[i] && str[i] != '"')
				i++;
			i++;
			tcb->cmd_ctr++;
		}
		else
		{
			printf("5 - i : %d - %c\n", i, str[i]);
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
				i++;
			while (str[i] && str[i] == ' ')
				i++;
			tcb->cmd_ctr++;
		}
		//printf("\n");
		if (str[i] == '\0')
			break ;
		//i++;
	}
}