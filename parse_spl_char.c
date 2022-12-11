/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spl_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:13:22 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/11 12:52:35 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_gt_block(t_msvar *msv)
{
	if (msv->rline[msv->i + 1] == '>')
	{
		msv->i++;
		if (msv->rline[msv->i + 1] == '>')
		{
			msv->i++;
			msv->parse_error = 4;
		}
	}
}

void	parse_lt_block(t_msvar *msv)
{
	if (msv->rline[msv->i + 1] == '<')
	{
		msv->i++;
		if (msv->rline[msv->i + 1] == '<')
		{
			msv->i++;
			msv->parse_error = 5;
		}
	}
}

void	parse_pipe_block(t_msvar *msv)
{
	if (msv->rline[msv->i + 1] == '|')
	{
			msv->i++;
			msv->parse_error = 6;
	}
	else
	{
		msv->rline[msv->i] = 2 ;
		msv->num_pipe++;
	}
}
