/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 11:34:19 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/03 15:03:40 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include <libft.h>
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include "shader.h"

typedef struct		s_material
{
	char			*newmtl;
	VEC3			ka;
	VEC3			kd;
	VEC3			ks;
	float			d;
	float			ns;
	int				illum;
}					t_material;

typedef struct		s_obj
{
	t_list			vertex;
	t_list			indices;
	t_list			normals;
	t_list			materials;
}					t_obj;

typedef struct		s_object
{
	t_obj			*obj;
	TRAN			*transform;
	GLuint			vertex_buffer;
	GLuint			indices_buffer;
	GLuint			normals_buffer;
	VEC3			*v_data;
	GLuint			*i_v_data;
	VEC3			*n_data;
	int				indices_size;
}					t_object;

t_obj				*load_obj(const char *file);
VEC3				*get_vertex_buffer(t_obj *obj);
GLuint				*get_indices_buffer(t_obj *obj);
VEC3				*get_normals_buffer(t_object *object);

t_object			*new_object(char const *obj_file);

void				load_material_lib(t_obj *obj, char *file, char *obj_file);

#endif
