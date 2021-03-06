/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 01:31:28 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/09 01:35:11 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_STRUCTURES_H
# define FT_LS_STRUCTURES_H

# include <zconf.h>
# include "ft_ls.h"

typedef struct				s_files_attrib
{
	char					*error_message;
	char					*full_path;
	char					*filename;
	struct s_files_attrib	*next;
	struct s_files_attrib	*previous;
	time_t					time;
	char					*timestamp;
	char					*st_mode_to_char;
	char					*owner_name;
	char					*group_name;
	size_t					file_size;
	int						link_count;
	blkcnt_t				block_size;
	char					*link_pointer;
	int						major;
	int						minor;
}							t_files_attrib;
typedef struct				s_path
{
	struct s_path			*next;
	char					*path;
	t_files_attrib			*attrib;
}							t_path;
typedef struct				s_props
{
	int						win_size;
	char					isterm;
	unsigned short int		flag;
	t_path					*path;
}							t_props;
typedef struct				s_print
{
	unsigned short int		links_max;
	unsigned int			owner_len_max;
	unsigned int			group_name_max;
	unsigned long int		tmp;
	unsigned int			nodes_count;
	unsigned int			filename_max;
	unsigned int			file_size_max;
	unsigned int			pointers_len;
	unsigned int			major_size;
	char					has_major;
	char					*ptr;
	int						count;
}							t_print;
typedef struct				s_column
{
	t_files_attrib			**attr_half;
	unsigned short			vh;
	unsigned short			width;
	unsigned short			cn;
}							t_column;
#endif
