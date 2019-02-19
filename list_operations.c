/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:46:50 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/19 20:01:46 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

t_files_attrib *ft_list_create(char *name, t_files_attrib *next,
							   t_files_attrib *prev)
{
	t_files_attrib *list;

	list = ft_memalloc(sizeof(t_files_attrib));
	list->filename = name ? ft_strdup(name) : 0;
	list->next = next;
	list->previous = prev;
	return (list);
}

void ft_list_sort_all(t_props *props)
{
	t_path *path;

	path = props->path;
	while (path)
	{
		if (props->flag==NO_FLAGS)
			for_each_level_sort(path->attrib, &comparator_lex);
		path = path->next;
	}
}

void for_each_level_sort(t_files_attrib *attrib, t_bool
( *comp)(t_files_attrib *a, t_files_attrib *b))
{
	t_bool is_sorted;

	is_sorted = false;
	while (attrib)
	{
		if(!is_sorted)
		{
			ft_merge_sort(&attrib, comp);
			is_sorted = true;
		}
		if (attrib->leaf)
			for_each_level_sort(attrib->leaf, comp);
		attrib = attrib->next;
	}
}

t_files_attrib *ft_list_push(t_files_attrib *current, t_files_attrib *prev)
{
	current->next = NULL;
	current->previous = prev;
	prev->next = current;
	return (current);
}

t_files_attrib *create_atr(char *name)
{
	t_files_attrib *attrib;

	attrib = ft_memalloc(sizeof(t_files_attrib));
	attrib->leaf = NULL;
	attrib->next = NULL;
	attrib->previous = NULL;
	attrib->filename = NULL;
	if (name)
		attrib->filename = ft_strdup(name);
	return (attrib);
}

void print_all(t_files_attrib *attrib)
{
	while (attrib)
	{
		if (! attrib->leaf)
			ft_putendl(attrib->filename);
		else
		{
			ft_putchar('\n');
			ft_putendl(attrib->filename);
			print_all(attrib->leaf);
		}
		attrib = attrib->next;
	}
}