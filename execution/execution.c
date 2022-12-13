#include "minishell.h"
void create_pipe(t_msvar **mvar)
{
    t_msvar *tmp;

    tmp = *mvar;
    int n = tmp->cmd_num;

    int i;

    if (n > 1)
    {
        tmp->fd = (int **)malloc(sizeof(int *) * n);
        if (!tmp->fd)
            perror("error_load:");

        i = 0;

        while (i < n)
        {
            tmp->fd[i] = (int *)malloc(sizeof(int) * 2);
            if (!tmp->fd[i])
                perror("error_load:");
            i++;
        }
    }
}
void execute_cmd(t_cblock *temp, t_env *env, t_msvar **mvar, int i)
{
    char **ev;
    // (void)mvar;
    (void)i;

    t_msvar *tmp;
    //   int status;

    tmp = *mvar;
    // printf("\nexecution exe start------%s---%s------\n",temp->cmd[0],temp->cmd[1]);

    tmp->cmd = get_cmd(mvar, temp->cmd[0]);
    if (!tmp->cmd)
    {
        // ft_putstr_fd( temp->cmd[0],2);
        if (ft_strrchr(temp->cmd[0], '/'))
            ft_putstr_fd(" : No such file or directory\n", 2);
        else
            ft_putstr_fd(" : command not found\n", 2);
        exit(1);
    }

    ev = env_to_str(env);
    if (execve((*mvar)->cmd, temp->cmd, ev) == -1)
    {
        ft_putstr_fd("\n", 2);
        ft_putstr_fd(temp->cmd[0], 2);
        perror("cmd_error:");
        // printf("Commande invalide : %s\n", tmp->commad[0]);
        //       fflush(stdout);//vide le buffer

        exit(0);
        // return -1;
    }
}
void pwdfn(t_cblock *tmp, t_env *env, t_msvar **mvar, int i)
{
    (void)tmp;
    (void)i;
    (void)mvar;
    printf("%s", ft_getenv("PWD", env));
    exit(1);
}

void echo_fn(t_cblock *tmp, t_env *env, t_msvar **mvar, int i)
{
    (void)env;
    (void)mvar;
    (void)i;
    ft_putstr_fd(tmp->cmd[1], 1);
    exit(1);
    // int i;
  /*  i = 0;
    while (tmp->cmd[1][i])
    {
        write(1, &(tmp->cmd[1][i]), 1);
        i++;
    }*/
}

int export_fn(t_cblock *tmp, t_env *env_list, t_msvar **mvar, int i)
{
    t_env *env_lst;
    (void)i;
    (void)env_list;
    // ft_elstprint(env_list);
    while ((*mvar)->env_list)
    {
        if (ft_strncmp(tmp->cmd[1], (*mvar)->env_list->key, 32767) == 0)
        {
            (*mvar)->env_list->value = ft_strdup(tmp->cmd[2]);

            // exit (1);
            return 1;
        }

        (*mvar)->env_list = ((*mvar)->env_list)->next;
    }

    env_lst = ft_elstnew(tmp->cmd[1], tmp->cmd[2]);
    if (env_lst)
        ft_elstadd_back(&((*mvar)->env_list), env_lst);

    return 1;
}
void execute_cmd_redirect(t_cblock *tmp, t_env *env, t_msvar **mvar, int i)
{
    //(void) i;
   
    if (strcmp(tmp->cmd[0], "echo ") == 0)
    {
      //  ft_putstr_fd("11111", 2);
        echo_fn(tmp, env, mvar, i);
    }
    else if (strcmp(tmp->cmd[0], "pwd ") == 0)
    {
        pwdfn(tmp, env, mvar, i);
    }
    else if (strcmp(tmp->cmd[0], "export ") == 0)
    {
        export_fn(tmp, env, mvar, i);
        exit(1);
    }
    else
    {
        execute_cmd(tmp, env, mvar, i);
    }
}

void execute_cmd_start(t_cblock *t_cmd, t_env *env, t_msvar **mvar, int k)
{
    // printf("\nexecution start\n");
    int n;
    int j;
    t_msvar *tmp;
    //   int status;
    int i;
    i = k;
    tmp = *mvar;
    tmp->cmd_path = ft_split(ft_getenv("PATH", env), ':');
    n = tmp->cmd_num;
    tmp->pid = fork();
    if (tmp->pid == 0)
    {
        // printf("\nexecution child start\n");
        i = k;
        j = k - 1;

        if ((tmp->f1 > -1))
            dup2(tmp->f1, 0);
        else if ((j) > -1)
            dup2(tmp->fd[j][0], 0);

        if (tmp->f2 > -1)
            dup2(tmp->f2, 1);
        else if (n > 1 && k != (n - 1))
            dup2(tmp->fd[i][1], 1);

        execute_cmd_redirect(t_cmd, env, mvar, i);
    }
}
int init_io(t_cblock *t_cmd, t_msvar **mvar)
{
    t_msvar *tmp;
    tmp = *mvar;

    if (t_cmd->input)
    {
        tmp->f1 = check_input(t_cmd->input);
        if (tmp->f1 == -1)
            return 0;
    }

    if (t_cmd->output)
    {

        tmp->f2 = check_output(t_cmd->output);

        if (tmp->f2 == -1)
            return 0;
    }

    return 1;
}
void mvar_init(t_msvar **mvar)
{
    (*mvar)->f1 = -1;
    (*mvar)->f2 = -1;
    (*mvar)->cmd_num = (*mvar)->num_pipe + 1;
}
int execution(t_cblock *t_cmd, t_env *env, t_msvar *mvar)
{
    // printf("\n11111111111\n");
    t_cblock *tmp;
    int i;
    (void)env;
    // ft_putnbr_fd(mvar->cmd_num,1);
    mvar_init(&mvar);

    create_pipe(&mvar);

    tmp = t_cmd;
    //  ft_putstr_fd(tmp->cmd[0],1);
    i = 0;
    while (tmp)
    {
        if (mvar->cmd_num > 1)
        {
            if (pipe(mvar->fd[i]) == -1)
            {
                perror("error_test:");
                return 1;
            }
        }

        mvar_init(&mvar);

        init_io(tmp, &mvar);

        execute_cmd_start(tmp, env, &mvar, i);

        while (waitpid(0, 0, 0) < 0)
            ;
        // waitpid((*mvar)-> pid [i], &status, 0);
        // write(2, "44444\n", 6);

        if (mvar->cmd_num > 1)
        {
            if (i > 0)
                close((mvar)->fd[i - 1][0]);
            close((mvar)->fd[i][1]);
        }
        if ((mvar)->f1 > -1)
            close((mvar)->f1);
        if ((mvar)->f2 > -1)
            close((mvar)->f2);
        i++;
        //  fflush(stdout);
        //     ft_putstr_fd(tmp->cmd[0],1);
        tmp = tmp->next;
    }
    return 0;
}
/*

int main(int n, char **av, char **env)
{
    (void)av;
    (void)n;
    t_cblock t_cmd;
    t_cblock t_cmd1;
   // t_cblock t_cmd2;
    t_msvar mvar;
    t_env *t_env;
    //   t_cmd=NULL;

    //	init_minishell(&msv);
    //load_env(&msv, env);

    init_minishell(&mvar);
     load_env(&mvar, env);
  // ft_elstprint(mvar.env_list);

    t_env = NULL;


    t_cmd.input = NULL;
  t_cmd.input = ft_split("abc.txt", ' ');
 t_cmd.output = NULL;
//  t_cmd.output = ft_split("out123.txt", ' ');
    t_cmd.cmd = ft_split("export USER 10", ' ');



t_cmd.next = NULL;
   t_cmd1.input =NULL;
    t_cmd1.output = NULL;
    t_cmd1.cmd = ft_split("printenv", ' ');
    t_cmd1.next = NULL;


 //    t_cmd.next = &t_cmd1;

//t_cmd2.input = NULL;
  //   t_cmd2.output = NULL;
   //   t_cmd2.cmd = ft_split("/usr/bin/wc -l", ' ');


    //t_cmd.next = &t_cmd1;
    //t_cmd1.next = &t_cmd2;
 //t_cmd2.next = NULL;


    execution(&t_cmd, (mvar.env_list),&(mvar));
   //  execution(&t_cmd1, (mvar.env_list),&(mvar));
}*/