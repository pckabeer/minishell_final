#include "minishell.h"


int check_input(char *process_file)
{
  
int fd=-2;
char *fname;

   if(process_file[1] == '<')
		{
                fname = ft_substr(process_file,2,ft_strlen(process_file));
                fd = ft_atoi(fname);
        }
        else
        {
            fname = ft_substr(process_file,1,ft_strlen(process_file));
fd = open(fname,O_RDONLY);
if(fd == -1)
{
   perror(fname);
     g_msv.exit_status=errno;
     return fd;
}
}
return fd;
}


int check_output(char *process_file)
{
int fd=-2;
//char *temp;
char *fname;


  
       // temp =ft_strdup(ft_strtrim(process_file[i]," "));
        if(process_file[1] == '>')
		{	//printf("resched");
			fname = ft_substr(process_file,2,ft_strlen(process_file));
           // temp++;
          // temp = ft_strchr(temp,'>');
          // printf("\nfilename-----%s",fname);
			fd = open(fname, O_APPEND | O_RDWR);
			if(fd ==-1)
			fd = open(fname, O_TRUNC | O_CREAT | O_RDWR, 0000644);
			if(fd == -1)
  			{
    			perror("error2:");
                 g_msv.exit_status=errno;
    			
			}
		}
		else
    {
      fname = ft_substr(process_file,1,ft_strlen(process_file));
		fd = open(fname, O_TRUNC | O_CREAT | O_RDWR, 0000644);
if(fd == -1)
  {
    perror(process_file);
     g_msv.exit_status=errno;
return fd;
				
}
    }
    return(fd);
    }


/*
int check_input1(char **process_file)
{int i;
int fd=-2;
char *fname;
i=0;

    while(process_file[i])
    {
   //   printf("%s----------\n",process_file[i]);
     if(process_file[i][0] == '<')
		{
                fname = ft_substr(process_file[i],1,ft_strlen(process_file[i]));
                fd = ft_atoi(fname);
        }
        else
        {
fd = open(process_file[i],O_RDONLY);
if(fd == -1)
{
   perror(process_file[i]);
     g_msv.exit_status=errno;
  /// clean_exit();
}
        }
i++;
}
//printf("------%d",i);
return fd;
    
}


int check_output(char **process_file)
{int i;
int fd=-2;
//char *temp;
char *fname;

i=0;
    while(process_file[i])
    {
       // temp =ft_strdup(ft_strtrim(process_file[i]," "));
        if(process_file[i][0] == '>')
		{	//printf("resched");
			fname = ft_substr(process_file[i],1,ft_strlen(process_file[i]));
           // temp++;
          // temp = ft_strchr(temp,'>');
          // printf("\nfilename-----%s",fname);
			fd = open(fname, O_APPEND | O_RDWR);
			if(fd ==-1)
			fd = open(fname, O_TRUNC | O_CREAT | O_RDWR, 0000644);
			if(fd == -1)
  			{
    			perror("error2:");
                 g_msv.exit_status=errno;
    			return fd;
			}
		}
		else
		fd = open(process_file[i], O_TRUNC | O_CREAT | O_RDWR, 0000644);
if(fd == -1)
  {
    perror(process_file[i]);
     g_msv.exit_status=errno;
 //  clean_exit();
				
}
i++;
}
return fd;
}*/
