/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 11:33:59 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/02 16:20:32 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/object.h"

static void	gen_buffers(t_object *object, GLfloat *v, GLint *i, GLfloat *n)
{
	glGenBuffers(1, &object->vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object->vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, object->obj->vertex.size * sizeof(float) * 3,\
		v, GL_STATIC_DRAW);
	glGenBuffers(1, &object->indices_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object->indices_buffer);
	glBufferData(GL_ARRAY_BUFFER, object->obj->indices.size * sizeof(int), \
		i, GL_STATIC_DRAW);
	glGenBuffers(1, &object->normals_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object->normals_buffer);
	glBufferData(GL_ARRAY_BUFFER, object->obj->vertex.size * sizeof(int) * 3, \
		n, GL_STATIC_DRAW);
}

t_object	*new_object(char const *obj_file)
{
	t_object	*object;
	GLfloat		*v_buffer_data;
	GLint		*i_buffer_data;
	GLfloat		*n_buffer_data;

	if ((object = ft_memalloc(sizeof(t_object))) == NULL)
		return (NULL);
	if ((object->obj = load_obj(obj_file)) == NULL)
		return (NULL);
	v_buffer_data = get_vertex_buffer(object->obj);
	i_buffer_data = get_indices_buffer(object->obj);
	n_buffer_data = clac_normals(object->obj);
	object->indices_size = object->obj->indices.size;
	object->transform = new_transform();
	gen_buffers(object, v_buffer_data, i_buffer_data, n_buffer_data);
	return (object);
}
