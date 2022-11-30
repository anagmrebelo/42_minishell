#include "../../include/minishell.h"

void    handle_heredoc(t_token *token, char *limit)
{
   int      fd;
   char     *line;

   fd = open(".hdoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
   line = readline("> ");
   while (ft_strcmp(line, limit) != 0)
   {
        ft_putendl_fd(line, fd);
        free (line);
        line = readline("> ");
   }
   free (line);
   close(fd);
   free(token->str);
   token->str = ft_strdup(".hdoc");
}