/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:35:37 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/07 16:35:39 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void			path_print(const t_path *current_path)
{
	write(1, "\n", 1);
	ft_putstr(current_path->path);
	ft_putendl(":");
}

int				ft_love_norme(t_files_attrib **at)
{
	*at = 0;
	errno = 0;
	return (1);
}

void			get_path_list(t_props *current)
{
	t_path		*current_path;
	int			assigment;

	assigment = -1;
	g_flag = current->flag;
	if (!current->path)
		return ;
	current_path = current->path;
	while ((current_path))
	{
		errno = 0;
		if (++assigment)
			path_print(current_path);
		if (-1 == access(current_path->path, F_OK))
		{
			print_error(current_path->path, errno, NULL);
			current_path = current_path->next;
			continue;
		}
		ft_open_folder(current_path->path, 0, current);
		current_path = current_path->next;
	}
}
