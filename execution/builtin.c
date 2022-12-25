#include "minishell.h"

void	echo_fn(t_cblock *tmp, t_env *env, t_msvar **mvar, int i)
{
	int	j;
	int	op;

	j = 1;
	(void)env;
	(void)mvar;
	(void)i;
	//ft_putstr_fd(tmp->cmd[j], 1);
	/*if(i >0)
	{
		close(g_msv.fd[i-1][1]);
	}*/
	op = 0;
	while (tmp->cmd[j])
	{
		if (ft_minusn(tmp->cmd[j]))
			op = 1;
		else
			break ;
		j++;
	}
	while (tmp->cmd[j])
	{
		if (tmp->cmd[j][0] != 2)
			ft_putstr_fd(tmp->cmd[j], 1);
		//ft_putchar_fd('-',1);
		j++;
	}
	if (!op)
		ft_putchar_fd('\n', 1);
	exit(EXIT_SUCCESS);
}

void	pwdfn(t_cblock *tmp, t_env *env, t_msvar **mvar, int i)
{
	(void)tmp;
	(void)i;
	(void)mvar;
	printf("%s\n", ft_getenv("PWD", env));
	exit(1);
}

int	cd_fn(t_cblock *tmp, t_env *env)
{
	char	*str;
	char	*cwd;

	cwd = (char *)malloc(sizeof(char) * 1028);
	str = NULL;
	if ((tmp->cmd[1]) == NULL)
	{
		str = ft_getenv("HOME", env);
		if (str == NULL)
		{
			printf("error");
			return (1);
			clean_exit();
		}
	}
	else
		str = ft_strtrim(tmp->cmd[1], " ");
	if (str != NULL)
		if (chdir(str) != 0)
			perror("cd error");
	if (getcwd(cwd, 1028) == NULL)
	{
		perror("error_test:");
		g_msv.exit_status = errno;
		clean_exit();
	}
	else
		export_env("PWD", cwd);
	return (0);
}

int	check_key_name(char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
		|| str[i] == '_')
	{
		i++;
		while (str[i])
		{
			if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z') || str[i] == '_' || (str[i] >= '0'
					&& str[i] <= '9'))
				i++;
			else
			{
				return (0);
			}
		}
		return (1);
	}
	else
	{
		return (0);
	}
}

int	export_fn(t_cblock *tmp)
{
	char	*str;
	char	*key;
	char	*val;
	int		i;
	int		n;

	i = 1;
	while (tmp->cmd[i])
	{
		val = NULL;
		if (tmp->cmd[i][0] == '=')
		{
			ft_putstr_fd("export : ", 1);
			ft_putchar_fd('`', 1);
			ft_putstr_fd(tmp->cmd[i], 1);
			ft_putchar_fd('\'', 1);
			ft_putstr_fd(": not a valid identifier\n", 1);
			i++;
			continue ;
		}
		else if (ft_strchr(tmp->cmd[i], '='))
		{
			str = ft_strchr(tmp->cmd[i], '=');
			n = ft_strlen(tmp->cmd[i]) - ft_strlen(str);
			key = ft_substr(tmp->cmd[i], 0, n);
			val = ft_substr(str, 1, ft_strlen(str) - 1);
			if (check_key_name(key))
			{
				if (val)
					export_env(key, val);
				else
					export_env(key, "");
			}
			else
			{
				ft_putstr_fd("export : ", 1);
				ft_putchar_fd('`', 1);
				ft_putstr_fd(tmp->cmd[i], 1);
				ft_putchar_fd('\'', 1);
				ft_putstr_fd(": not a valid identifier\n", 1);
			}
			i++;
		}
		else
		{
			if (!check_key_name(tmp->cmd[i]))
			{
				ft_putstr_fd("export : ", 1);
				ft_putchar_fd('`', 1);
				ft_putstr_fd(tmp->cmd[i], 1);
				ft_putchar_fd('\'', 1);
				ft_putstr_fd(": not a valid identifier\n", 1);
			}
			i++;
		}
	}
	//export_env(ft_strtrim(tmp->cmd[1], " "), ft_strtrim(tmp->cmd[2], " "));
	return (1);
}

void	unset_fn(t_cblock *tmp, t_env *env)
{
	if (tmp->cmd[1] && ft_getenv(tmp->cmd[1], env))
	{
		unset_env(tmp->cmd[1]);
	}

	return ;
}