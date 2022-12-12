/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:02:23 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/13 01:03:45 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void parse_expand(t_msvar *msv, int i, char *str)
{
	t_cblock	*cbd;
	char		*temp;
	int j;
	int k;

	temp = "";

	if (msv->parse_error)
		return ;
	j = 0;
	k = 0;
	i=0;
	cbd = msv->cmd_block_arr;
	//printf("-- %s \n", str);
	if(str[j] == '"')
	{
		j++;
		while (str[j] && str[j] != '"')
		{
			if (str[j] == '$')
			{
				j++;
				while (str[j] && str[j] != '"' && str[j] != ' ' && str[j] != '$')
				{
					k++;
					j++;
				}
				msv->b_temp = ft_get_dword(str + j - k);
				msv->b_temp = ft_getenv(msv->b_temp, msv->env_list);
				// printf("-- %s -- \n", msv->b_temp);
				if(msv->b_temp)
					temp = ft_strjoin(temp, msv->b_temp);
					// printf("%s", msv->b_temp);
				//printf("%s\n", temp);
				j--;
				k=0;
			}
			j++;
			if(str[j] != '$')
				temp = ft_strjoinchr(temp, str[j]);
			
			// printf("%c", str[j]);
			// printf("-- %c ", str[j]);
		}
	}
	 printf("%s\n", temp);
	if (str[j] == '$')
	{
		j++;
		while (str[j] && str[j] != '"' && str[j] != ' ' && str[j] != '$')
		{
			k++;
			j++;
		}
		msv->b_temp = ft_get_dword(str + j - k);
		msv->b_temp = ft_getenv(msv->b_temp, msv->env_list);
		if(msv->b_temp)
		printf("%s", msv->b_temp);
	//	j--;
		k=0;
	}
	while (str[j])
	{
		printf("-- %c \n", str[j++]);
	}
	//printf("%s\n", msv->cmd_block_arr[0].cmd[0]);

	// while (cbd[i].cmd[j])
	// {
	// 	while (cbd[i].cmd[j][k])
	// 	{
	// 		printf("%c", cbd[i].cmd[j][k]);
	// 		k++;
	// 	}
	// 	k = 0;
	// 	printf("\n");
	// 	j++;
	// }
	// cbd->cmd
}