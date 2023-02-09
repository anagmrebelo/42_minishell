/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:13:44 by anarebelo         #+#    #+#             */
/*   Updated: 2023/02/09 23:08:28 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "free.h"

/**
 * Prints error of no such file or directory and sets exit code to 127
*/
void	no_file_dir(t_master *master, char *cmd, int exit_code)
{
	print_error("minishell", cmd, "No such file or directory\n");
	clean_free(master, exit_code);
}

/**
 * Prints error permission denied and sets exit cod
*/
void	perm_denied(t_master *master, char *cmd, int exit_code)
{
	print_error("minishell", cmd, "Permission denied\n");
	clean_free(master, exit_code);
}

/**
 * Prints not a directory error (e.g. src/ana.txt/a) and sets exit code
*/
void	not_dir(t_master *master, char *cmd, int exit_code)
{
	print_error("minishell", cmd, "Not a directory\n");
	clean_free(master, exit_code);
}
