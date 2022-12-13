/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:25:16 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/13 13:23:46 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	parse_quote_block(void)
{
	g_msv.i++;
	while (g_msv.rline[g_msv.i] != '\'' && g_msv.rline[g_msv.i] != '\0')
	{
		g_msv.w_len++;
		g_msv.i++;
	}
	if (g_msv.rline[g_msv.i] == '\'')
	{
		g_msv.temp = ft_substr(g_msv.rline, g_msv.i - g_msv.w_len, (g_msv.w_len));
		ft_dlstadd_back(&g_msv.block_list, ft_dlstnew(g_msv.temp, 0, 0, '\''));
		g_msv.w_count++;
	}
	else
		g_msv.parse_error = 2;
}

void	parse_dquote_block(void)
{
	g_msv.i++;
	g_msv.temp = ft_calloc(2, 1);
	while (g_msv.rline[g_msv.i] != '"' && g_msv.rline[g_msv.i] != '\0')
	{
		if (g_msv.rline[g_msv.i] == '$')
		{
			g_msv.b_temp = parse_dollar_block();
			if (g_msv.b_temp)
				ft_strlcat(g_msv.output, g_msv.b_temp, 32767);
			printf(" -- %s\n",g_msv.output);
			//free(msv.b_temp);
		}
		else
		{
			g_msv.temp[0] = g_msv.rline[g_msv.i];
			ft_strlcat(g_msv.output, g_msv.temp, 32767);
			g_msv.i++;
		}
	}
	free(g_msv.temp);
	if (g_msv.rline[g_msv.i] == '"')
		ft_dlstadd_back(&g_msv.block_list, ft_dlstnew(g_msv.output, 0, 0, '\"'));
	else
		g_msv.parse_error = 3;
}

/**
*  parse_dollar_block
* * parses the dollar block and fetches the value from the key parsed 
* * to the env_list 
*   @msv: struct with all the variables
* ! the function cannot use ft_get_word,because <"$USER"hi > is a valid input
* ! and ft_get_word would return "USER"hi instead try parsing msv.rline[i++]
*  return: value for the key
*/
char	*parse_dollar_block(void)
{
	int		len;

	g_msv.i++;
	g_msv.b_temp = ft_get_dword(g_msv.rline + g_msv.i);
	len = ft_strlen(g_msv.b_temp);
	printf("%s\n", g_msv.b_temp);
	g_msv.i += len;
	g_msv.w_len += len;
	if (g_msv.b_temp[len - 1] == '"')
	{
		g_msv.b_temp[len - 1] = '\0';
		g_msv.b_temp = ft_getenv(g_msv.b_temp, g_msv.env_list);
		g_msv.b_temp[len - 1] = '"';
	}
	else
		g_msv.b_temp = ft_getenv(g_msv.b_temp, g_msv.env_list);
	return (g_msv.b_temp);
}

/**
 * parse_nospl_block
 * * parses the block without any special characters
 *  @msv: struct with all the variables
 */
void	parse_nospl_block(void)
{
	return ;
}