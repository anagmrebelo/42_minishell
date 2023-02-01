/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:13:44 by anarebelo         #+#    #+#             */
/*   Updated: 2023/02/01 11:53:48 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Prints error of no such file or directory and sets exit code to 127
*/
void	no_file_dir(t_master *master, char *cmd)
{
	print_error("minishell", cmd, "No such file or directory\n");
	clean_free(master, 127);
}

/**
 * Prints error permission denied and sets exit code to 126
*/
void	perm_denied(t_master *master, char *cmd)
{
	print_error("minishell", cmd, "Permission denied\n");
	clean_free(master, 126);
}
