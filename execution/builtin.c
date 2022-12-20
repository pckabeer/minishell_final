#include "minishell.h"

void	pwdfn(t_cblock *tmp, t_env *env, t_msvar **mvar, int i)
{
	(void)tmp;
	(void)i;
	(void)mvar;
	printf("%s", ft_getenv("PWD", env));
	exit(1);
}

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

int	cd_fn(t_cblock *tmp)
{
	if (chdir(ft_strtrim(tmp->cmd[1]," ")) != 0) 
		perror("cd error");
	return (0);
}

int	export_fn(t_cblock *tmp)
{
	export_env(ft_strtrim(tmp->cmd[1], " "), ft_strtrim(tmp->cmd[2], " "));
	return (1);
}

