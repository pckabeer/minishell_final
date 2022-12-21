#include "minishell.h"


void	echo_fn(t_cblock *tmp, t_env *env, t_msvar **mvar, int i)
{
	int j;
	
	j = 1;
	(void)env;
	(void)mvar;
	i = ft_minusn(tmp->cmd[1]);
	printf("%d\n",i);
	while (tmp->cmd[j + i])
		ft_putstr_fd(tmp->cmd[i+j++], 1);	
	if(!i)
			ft_putchar_fd('\n', 1);
	
	exit(1);
}
void	pwdfn(t_cblock *tmp, t_env *env, t_msvar **mvar, int i)
{
	(void)tmp;
	(void)i;
	(void)mvar;
	printf("-------------");
	printf("%s", ft_getenv("PWD", env));
	exit(1);
}

int	cd_fn(t_cblock *tmp,t_env *env)
{

	char *str;
	char *cwd;
	cwd = (char *)malloc(sizeof(char)*1028);

	str = NULL;
	if((tmp->cmd[1])==NULL)
	{
		str = ft_getenv("HOME", env);
	if(str == NULL)
	{
		printf("error");
		return(1);
		clean_exit();
	}
	}
	else
	{
		str=ft_strtrim(tmp->cmd[1]," ");
	}
	
	if(str != NULL)
	if (chdir(str) != 0) 
		perror("cd error");
	
	if (getcwd(cwd, 1028) == NULL)
    {
		perror("error_test:");
     g_msv.exit_status=errno;
   clean_exit();
	}
    else
		export_env("PWD", cwd);     //printf("current working directory is: %s\n", cwd);
		return (0);
}

int	export_fn(t_cblock *tmp)
{
	export_env(ft_strtrim(tmp->cmd[1], " "), ft_strtrim(tmp->cmd[2], " "));
	return (1);
}