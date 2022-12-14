#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include<string.h>

typedef struct cmdblock
{
    char **inputfile;
    char **outputfile;
    char **commad;
    struct cmdblock *next;
} cmd_block;

typedef struct env_block
{
    char *key;
    char *value;
    struct env_block *next;
} env_b;

int count_cmd(cmd_block *t_cmd);
int execution (cmd_block *t_cmd, char **t_env);
char	*ft_strjoin(char const *s1, char const *s2);
int check_input(char **process_file);
int check_output(char **process_file);
char *ft_strdup(const char *s1);
int ft_strlen(const char *st);
char	**ft_split(char const *str, char c);
char *ft_substr(const char *s, unsigned int start, size_t len);
#endif