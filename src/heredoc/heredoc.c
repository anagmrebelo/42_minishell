#include "../../include/minishell.h"

int    handle_heredoc(char *limit)
{
   int     fd;
   char    *line;

   fd = open(".hdoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
   line = readline("> ");
   while (ft_strcmp(line, limit) != 0)
   {
       ft_putendl_fd(line, fd);
       line = readline("> ");
   }
   close(fd);
   return (0);
}