/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:13:44 by anarebelo         #+#    #+#             */
/*   Updated: 2023/02/02 10:24:39 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
