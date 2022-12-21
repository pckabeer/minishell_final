/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 01:32:26 by skabeer           #+#    #+#             */
/*   Updated: 2022/12/21 16:07:10 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int count_cmd1(t_env *t_cmd)
{
	t_env *tmp;
	tmp = t_cmd;
	int i;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return i;
}

char **env_to_str(t_env *env)
{
    char **str;
    char *s;
    char *temp;
    int n;
    int i;

    n = count_cmd1(env);
    str = (char **)malloc(sizeof(char *) * n+1);
        if (!str)
           {
			perror("error_test:");
     g_msv.exit_status=errno;
   clean_exit();
		   }

     i = 0;
    while (i < n )
    {
        s = ft_strjoin(env->key," = ");
        temp = s;
        s = ft_strjoin(s,env->value);
        *(str+i) = (char *)malloc(sizeof(char)*(strlen(s)+1));
        str[i]=ft_strdup(s);
      //  printf("\n------------env---------\n");
      //  printf("%s\n",str[i]);
        free(temp);
        free(s);
env=env->next;
        i++;
    }
	str[i]=NULL;

return(str);
}
/*
t_env	*load_env1(char **env)
{
	int		i;
	char	*value;
	char	*temp;
	t_env	*env_lst;

	i = 0;
	while (env[i])
	{
		temp = ft_get_word(env[i], '=');
		value = ft_strdup(env[i] + ft_strlen(temp) + 1);
		env_lst = ft_elstnew(temp, value);
		if (env_lst)
			ft_elstadd_back(&msv->env_list, env_lst);
		else
			clean_exit(msv);
		i++;
	}
    return(env_lst);
}*/