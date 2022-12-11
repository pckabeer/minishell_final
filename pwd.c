/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:44:56 by aelsiddi          #+#    #+#             */
/*   Updated: 2022/11/25 10:35:31 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr2(char *s, unsigned int start, size_t	len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start || len < 1)
		str = (char *)malloc(sizeof(*s));
	else if (ft_strlen(s) - start < len)
		str = (char *)malloc((ft_strlen(s) - start + 1) * sizeof(*s));
	else
		str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			str[j++] = s[i];
		i++;
	}
	str[j] = 0;
	return (str);
}


void ft_exec_pwd(t_msvar *lst)
{
	t_env *temp;
	
	temp = lst->env_list;
	while(temp)
	{
		if(!(strncmp("PWD",temp->key,3)))
			ft_putstr_fd(temp->value,1);
		temp = temp->next;
	}
	ft_putchar_fd('\n',1);
	free(temp);
}

void ft_exec_env(t_msvar *lst)
{
	t_env *temp;
	
	temp = lst->env_list;
	while(temp)
	{
		ft_putstr_fd(temp->key,1);
		ft_putchar_fd('=',1);
		ft_putstr_fd(temp->value,1);
		ft_putchar_fd('\n',1);
		temp = temp->next;
	}
	free(temp);
}

void ft_exec_exit(void)
{
	exit(3);
}

void ft_exec_cd(t_msvar *lst)
{
	t_msvar *temp;
	t_env *temp2;

	temp = lst;
	char *holder = ft_substr2(temp->rline,3,(ft_strlen(temp->rline)-3));
	if(!(ft_strncmp(holder ,"..",ft_strlen(holder))))
	{
		printf("This should be replaced with root dir\n");
		opendir("");
	}
	temp2 =  lst->env_list;
	if (!(getDirList(holder)))
	{
		ft_putstr_fd("cd: no such file or directory: ",1);
		ft_putstr_fd(holder,1);
		printf("\n");
		return;
	}
	while(temp2)
	{
		if(!(strncmp("PWD",temp2->key,3)))
		{
			temp2->value = ft_strjoin(temp2->value,"/");
			temp2->value = ft_strjoin(temp2->value,holder);
		}
		temp2 = temp2->next;
	}
	ft_exec_pwd(lst);
}

