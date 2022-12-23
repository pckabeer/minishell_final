/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:12:36 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/24 03:40:06 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# define DELIMIT 2
# include <fcntl.h>

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

/*
* ! The struct s_dlist is a doubly linked list
	content is the data stored in the node
	next is the pointer to the next node
	prev is the pointer to the previous node
		len_quote is the length of the quote used for >> or << redirection 
	it will be 1 else for all it is 0
	cmd_seq is the command sequence number for the command 0 for no command 
		1 for first command 2 for second command and 
		so on till command 7 for exit
		after 7 the program will check if the command is there in the system  
		and then execute it or give an error
	is_opti is a flag to check if the command is a option or not
*/

typedef struct s_dlist
{
	char				*content;
	char				quote;
	int					len_quote;
	int					cmd_seq;
	int					is_option;
	struct s_dlist		*next;
	struct s_dlist		*prev;
}						t_dlist;

typedef struct cmd_block
{
	char				**input;
	char				**output;
	char				**cmd;
	char				*input_h;
	char				*output_h;
	char				*cmd_h;
	int					input_ctr;
	int					output_ctr;
	int					cmd_ctr;
	int					err_flag;
	char				delimit;
	struct cmd_block	*next;

}						t_cblock;

/*
	cmd_num is the number to find which command 
	eg echo = 1 
		...
*/
typedef struct minishellvariables
{
	char				*rline;
	char				**cmd_arr;
	int					i;
	char				*output;
	int					cmd_num;
	int					num_pipe;
	int					parse_error;
	int					exit_flag;
	int					w_count;
	int					w_len;
	t_dlist				*block_list;
	t_env				*env_list;
	char				*temp;
	char				*b_temp;
	char				delimit;
	t_cblock			*cmd_block_arr;
	int					pid;
	int					**fd;
	int					f1;
	int					f2;
	char				**cmd_path;
	char				*cmd;
	int					exit_status;
	int					in_heredoc;
	int					in_proc_active;
}						t_msvar;

t_msvar					g_msv;
void					parse(void);
void					parse_error(void);
void					parse_gt_block(void);
void					parse_lt_block(void);
void					parse_pipe_block(void);
void					parse_quote_block(void);
void					parse_dquote_block(void);
void					parse_split_q(void);
void					parse_split_dq(void);
char					*parse_dollar_block(void);
void					parse_nospl_block(void);

void					load_env(char **env);
char					*ft_getenv(char *str, t_env *env_list);

void					clean_exit(void);
// void	ft_exec(void);
void					ft_exec(void);
void					ft_exec_echo(void);

t_dlist					*ft_dlstnew(char *data, int cmd_seq, int len_q, char q);
void					ft_dlstadd_back(t_dlist **lst, t_dlist *new1);
void					ft_dlstadd_front(t_dlist **lst, t_dlist *new1);
int						ft_dlstsize(t_dlist *lst);
void					ft_dlstclear(t_dlist **lst);
t_dlist					*ft_dlstlast(t_dlist *lst);
int						ft_dlstprt(t_dlist *lst);

t_env					*ft_elstnew(char *key, char *value);
void					ft_elstadd_back(t_env **lst, t_env *new1);
void					ft_elstadd_front(t_env **lst, t_env *new1);
int						ft_elstsize(t_env *lst);
void					ft_elstclear(t_env **lst);
t_env					*ft_elstlast(t_env *lst);
int						ft_elstprint(t_env *lst);

char					*ft_get_word(char *str, char ch);
char					*ft_get_dword(char *str);
char					*ft_get_dword_(char *str);

void					ft_exec_pwd(t_msvar *lst);
void					ft_exec_env(t_msvar *lst);
void					ft_exec_exit(void);
// void ft_exec_cd(t_msvar *lst);
void					ft_exec_cd(t_msvar *lst);
char					*ft_substr2(char *s, unsigned int start, size_t len);

void					tblock_counter(t_cblock *tcb, char *str);
void					init_t_cblock(t_cblock *tcb);
char					*tb_join(char *str, char *output, int start, int i);
int						parse_split_lt(t_cblock *tbc, int i, int start,
							char *str);
int						parse_split_gt(t_cblock *tbc, int i, int start,
							char *str);
int						parse_split_qh(t_cblock *tcb, int i, int start,
							char *str);
int						parse_split_dqh(t_cblock *tcb, int i, int start,
							char *str);
int						parse_split_h(t_cblock *tcb, int i, int start,
							char *str);

char					*parse_expand(int i, char *str);
char					*parse_expand_io(int i, char *str);
char					*ft_strjoinchr(char *str, char ch);

//*****************dir.c******************//
int						getDirList(char *str);
int						ls(t_msvar *lst);

//***********export.c****************//
void					ft_exec_export(t_msvar *lst);

//***************Execution**************//
int						count_cmd(t_cblock *t_cmd);
void						execution(t_cblock *t_cmd, t_env *env, t_msvar *mvar);
char					*ft_strjoin(char const *s1, char const *s2);
int						check_input(char *process_file);
int						check_output(char *process_file);

t_env					*load_env1(char **env);
char					**env_to_str(t_env *env);

char					*get_cmd(t_msvar **mvar, char *cmd);
void					export_env(char *key, char *value);
void					unset_env(char *key);

void					execute_cmd_start(t_cblock *t_cmd, t_env *env,
							t_msvar **mvar, int k);
void					execute_cmd_redirect(t_cblock *tmp, t_env *env,
							t_msvar **mvar, int i);
void					execute_cmd(t_cblock *temp, t_env *env, t_msvar **mvar,
							int i);
void					pwdfn(t_cblock *tmp, t_env *env, t_msvar **mvar, int i);
void					echo_fn(t_cblock *tmp, t_env *env, t_msvar **mvar,
							int i);
int						cd_fn(t_cblock *tmp, t_env *env);
int						export_fn(t_cblock *tmp);
int						ft_minusn(char *str);
int						ft_elstprint_exp(t_env *lst);
void					unset_fn(t_cblock *tmp,t_env *env);
void					unset_env(char *key);

void					siginthandler1(int sig_num);
void					siginthandler(int sig_num);

/******temp_util**************/

void					print_str(char **str);
#endif