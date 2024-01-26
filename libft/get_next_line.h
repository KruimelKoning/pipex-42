/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 15:54:12 by lbartels      #+#    #+#                 */
/*   Updated: 2023/12/14 15:45:19 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*set_buffer(int fd, char *str);
int		check_new_line(char *str);
char	*gnl_strjoin(char *str, char const *buffer);
char	*set_next_line(char *str);
char	*new_str(char *str);
size_t	gnl_strlen(const char *s);

#endif