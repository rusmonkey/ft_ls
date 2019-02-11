/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:47:13 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/09 21:44:59 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void find_flag_pattern(char **argv, t_props *props)
{
	if (ft_strchr(*argv, 'R'))
		props->flag |= R_BIG;
	if (ft_strchr(*argv, 'a'))
		props->flag |= A;
	if (ft_strchr(*argv, 'r'))
		props->flag |= R_SMALL;
	if (ft_strchr(*argv, 't'))
		props->flag |= T;
	if (ft_strchr(*argv, 'l'))
		props->flag |= L;
}

t_props *scan_flags_path(char **argv, int argc)
{
	t_props *props;
	t_path *pat;
	t_path *p_handler;
	t_bool is_first_asign;

	p_handler = NULL;
	is_first_asign = true;
	pat = NULL;
	props = malloc(sizeof(props));
	props->flag = NO_FLAGS;
	props->path = NULL;
	if (argc < 2)
		return (props);
	*(argv)++;
	while (*argv)
	{
		if (*argv[0] == '-')
			find_flag_pattern(argv, props);
		else
		{
			pat = ft_path_append(pat, *argv);
			if (is_first_asign)
				p_handler = pat;
			is_first_asign = false;
		}
		*(argv)++;
	}
	props->path = p_handler;
	return (props);
}


t_props *get_t_size_and_flags(int argc, char **argv)
{
	struct winsize w;
	t_props *props;

	props = scan_flags_path(argv, argc);
	props->isterm = (char) (isatty(fileno(stdin)) ? 1 : 0);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	props->win_size = w.ws_row;
	return (props);
}

void get_path_list(t_props *curent)
{
	t_path *current_path;
	t_path *holder;
	t_bool flag;

	flag = !(curent->flag & A);
	if (!curent->path)
		return;
	current_path = curent->path;
	holder = current_path;
	current_path->attrib = get_attr_from_path(current_path->path, flag);
	while ((current_path = current_path->next))
		current_path->attrib = get_attr_from_path(current_path->path, flag);
	curent->path = holder;
}

int main(int argc, char **argv)
{
	t_props *props;
	t_path *pat;


	props = get_t_size_and_flags(argc, argv);
	get_path_list(props);
	pat = props->path;
	while (pat)
	{
		print_path_list(pat);
		pat = pat->next;
	}

	return 0;
}

t_files_attrib *get_attr_from_path(char *path, int need_to_exclude_system)
{
	t_files_attrib *current_files_list;
	t_files_attrib *tmp_pre;
	t_files_attrib *first;
	DIR *dir;
	struct dirent *direntp;

	first = NULL;
	dir = opendir(path);
	if (errno == ENOENT)
	{
		errno = 0;
		return (NULL);
	}
	if ((direntp = readdir(dir)) != NULL)
	{
		current_files_list = ft_list_create(direntp->d_name, NULL, NULL);
		first = current_files_list;
		while (NULL != (direntp = readdir(dir)))
		{
			if ((need_to_exclude_system && direntp->d_name[0] != '.') ||
				!need_to_exclude_system)
			{
				tmp_pre = current_files_list;
				current_files_list = ft_list_create(direntp->d_name, NULL,
													NULL);
				ft_list_push(current_files_list, tmp_pre);
			}
		}
	}
	closedir(dir);
	return (first);
}
