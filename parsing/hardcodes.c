/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hardcodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:37:39 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/25 10:52:23 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Codes when not able to solve a argument
*		g_msv.h_code = 1 , gives a safe way to the execution through parsing
*/
void ft_hardcoder()
{
	g_msv.h_code = 0;
}