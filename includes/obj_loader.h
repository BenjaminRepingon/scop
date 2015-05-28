/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 13:52:35 by rbenjami          #+#    #+#             */
/*   Updated: 2015/05/28 14:46:12 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_LOADER_H
# define OBJ_LOADER_H

# include <libft.h>

typedef struct		s_obj
{
	t_list			vertex;
	t_list			indices;
}					t_obj;

t_obj	*load_obj(const char *file);
float	*get_vertex_buffer(t_obj *obj);
int		*get_indices_buffer(t_obj *obj);
float	*clac_normals(t_obj *obj);

#endif
