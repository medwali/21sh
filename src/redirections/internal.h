/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 18:52:14 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/05 19:36:28 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include "twenty_one.h"

# define UMASK 0644

void	remove_redirections_tokens(t_vector *tokens);
int		redirect_output(char *filename, int io_number, t_bool append);
int		redirect_input(char *filename, int io_number);
int		fd_aggregation(int old_fd, int new_fd);
int		here_document(int fd, char *delimeter, t_bool remove_tabs);
void	close_output(int io_number);

#endif
