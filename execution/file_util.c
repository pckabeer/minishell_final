#include "minishell.h"

int check_input(char **process_file)
{int i;
int fd=-2;

i=0;

    while(process_file[i])
    {
     // printf("%s\n",process_file[i]);

fd = open(process_file[i],O_RDONLY);
if(fd == -1)
{
    perror("error23232:");
    return -1;
}
i++;
}
//printf("------%d",i);
return fd;
    
}


int check_output(char **process_file)
{int i;
int fd=-2;
char *fname;

i=0;
    while(process_file[i])
    {
        if(process_file[i][0] == '>')
		{	
			fname = ft_substr(process_file[i],1,ft_strlen(process_file[i]-1));
			fd = open(fname, O_APPEND | O_RDWR);
			if(fd ==-1)
			fd = open(process_file[i], O_TRUNC | O_CREAT | O_RDWR, 0000644);
			if(fd == -1)
  			{
    			perror("error2:");
    			return fd;
			}
		}
		else
		fd = open(process_file[i], O_TRUNC | O_CREAT | O_RDWR, 0000644);
if(fd == -1)
  {
    perror("error2:");
    return fd;
}
i++;
}
return fd;
}