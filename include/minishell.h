/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:50:53 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/15 14:20:31 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <../libft/libft.h>

/*
typedef struct s_list
{
    char    *title;
    char    *value;
    char    *content;
    struct s_list   *next;
}   t_list;
*/

typedef struct  s_token
{
    char            *str;
    int             type;
    struct s_token  *next;
    struct s_token  *prev;
} t_token;

typedef struct s_master
{
    t_list *env;
    t_token *token_list;
}   t_master;


//Environment
int		init_env(t_master *master, char **enviroment);
char    *get_title(char *str);
char    *get_value(char *str);
void	print_env(t_list *env);


//Parsing
void	parsing(char * line, t_master *master);
int     tokenize(char *line, t_master *master);
t_token *new_token(char *line, int size, t_master *master);

void	env_update(t_token *new, t_master *master);
char	*find_var(char * str, t_master *master);

char	*quotes_clean(t_token *new);
void	quotes_update(t_token *new);

void    add_list(t_master *list, t_token *item);
t_token *last_token(t_token *token);
t_token *first_token(t_token *token);
void    free_token(t_token *item);
void    free_list(t_token *list);

//Aux
void    print_list_tokens(t_token *list);
size_t	ft_strlcat1(char *dst, const char *src, size_t dstsize);

#endif
