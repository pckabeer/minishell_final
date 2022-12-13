/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spl_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:13:22 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/13 13:23:46 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_gt_block(void)
{
	if (g_msv.rline[g_msv.i + 1] == '>')
	{
		g_msv.i++;
		if (g_msv.rline[g_msv.i + 1] == '>')
		{
			g_msv.i++;
			g_msv.parse_error = 4;
		}
	}
}

void	parse_lt_block(void)
{
	if (g_msv.rline[g_msv.i + 1] == '<')
	{
		g_msv.i++;
		if (g_msv.rline[g_msv.i + 1] == '<')
		{
			g_msv.i++;
			g_msv.parse_error = 5;
		}
	}
}

void	parse_pipe_block(void)
{
	if (g_msv.rline[g_msv.i + 1] == '|')
	{
			g_msv.i++;
			g_msv.parse_error = 6;
	}
	else
	{
		g_msv.rline[g_msv.i] = 2 ;
		g_msv.num_pipe++;
	}
}
