/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:28:17 by acharik           #+#    #+#             */
/*   Updated: 2024/03/07 01:35:44 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list*/;

char				*ft_substr(char const *s, unsigned int start, size_t len);

t_list				*ft_lstnew(void *content, int *lst_size);
char				*get_next_line(int fd);
int					read_file(int fd, char **buffer);
char				*copy_linked_list(t_list *lst, int lst_size);
int					helper_function(char **buffer, int i);
int					line_search(char **buffer, t_list **node,
						t_list **first_node, int *list_size);
char				*process_buffer(t_list **first_node, char **buffer,
						t_list **node, int fd);
void				ft_lstclear(t_list **lst, void (*del)(void *));

#endif
