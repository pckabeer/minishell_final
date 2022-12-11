/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:25:16 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/11 12:05:43 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	parse_quote_block(t_msvar *msv)
{
	msv->i++;
	while (msv->rline[msv->i] != '\'' && msv->rline[msv->i] != '\0')
	{
		msv->w_len++;
		msv->i++;
	}
	if (msv->rline[msv->i] == '\'')
	{
		msv->temp = ft_substr(msv->rline, msv->i - msv->w_len, (msv->w_len));
		ft_dlstadd_back(&msv->block_list, ft_dlstnew(msv->temp, 0, 0, '\''));
		msv->w_count++;
	}
	else
		msv->parse_error = 2;
}

void	parse_dquote_block(t_msvar	*msv)
{
	msv->i++;
	msv->temp = ft_calloc(2, 1);
	while (msv->rline[msv->i] != '"' && msv->rline[msv->i] != '\0')
	{
		if (msv->rline[msv->i] == '$')
		{
			msv->b_temp = parse_dollar_block(msv);
			if (msv->b_temp)
				ft_strlcat(msv->output, msv->b_temp, 32767);
			printf(" -- %s\n",msv->output);
			//free(msv->b_temp);
		}
		else
		{
			msv->temp[0] = msv->rline[msv->i];
			ft_strlcat(msv->output, msv->temp, 32767);
			msv->i++;
		}
	}
	free(msv->temp);
	if (msv->rline[msv->i] == '"')
		ft_dlstadd_back(&msv->block_list, ft_dlstnew(msv->output, 0, 0, '\"'));
	else
		msv->parse_error = 3;
}

/**
*  parse_dollar_block
* * parses the dollar block and fetches the value from the key parsed 
* * to the env_list 
*   @msv: struct with all the variables
* ! the function cannot use ft_get_word,because <"$USER"hi > is a valid input
* ! and ft_get_word would return "USER"hi instead try parsing msv->rline[i++]
*  return: value for the key
*/
char	*parse_dollar_block(t_msvar *msv)
{
	int		len;

	msv->i++;
	msv->b_temp = ft_get_dword(msv->rline + msv->i);
	len = ft_strlen(msv->b_temp);
	printf("%s\n", msv->b_temp);
	msv->i += len;
	msv->w_len += len;
	if (msv->b_temp[len - 1] == '"')
	{
		msv->b_temp[len - 1] = '\0';
		msv->b_temp = ft_getenv(msv->b_temp, msv->env_list);
		msv->b_temp[len - 1] = '"';
	}
	else
		msv->b_temp = ft_getenv(msv->b_temp, msv->env_list);
	return (msv->b_temp);
}

/**
 * parse_nospl_block
 * * parses the block without any special characters
 *  @msv: struct with all the variables
 */
void	parse_nospl_block(t_msvar *msv)
{
	(void)*msv;
	return ;
}