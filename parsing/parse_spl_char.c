/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spl_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:13:22 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/20 19:34:48 by kpanikka         ###   ########.fr       */
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
	int	flag_ps;
	int	j;

	flag_ps = 0;
	j = 0;
	while (g_msv.rline[g_msv.i + ++j] == ' ')
		flag_ps = 1;
	if (g_msv.rline[ft_strlen(g_msv.rline) - 1] == '|')
	{
		g_msv.parse_error = 7;
		return ;
	}
	if (!g_msv.i || (g_msv.rline[g_msv.i + j] == '|' && flag_ps))
			g_msv.echo parse_error = 7;
	else if (g_msv.rline[g_msv.i + j] == '|')
			g_msv.parse_error = 6;
	else
	{
		g_msv.rline[g_msv.i] = 2 ;
		g_msv.num_pipe++;
		return ;
	}
			g_msv.i++;
}


void	parse_space_block(void)
{
	while (g_msv.rline[g_msv.i + 1] == ' ')
	{
		g_msv.i++;
	}
	if(!g_msv.rline[g_msv.i + 1])
	{
			g_msv.i++;
			g_msv.parse_error = 7;
	}
}