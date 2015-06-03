/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 11:33:59 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/03 12:20:00 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/object.h"

static void	gen_buffers(t_object *object)
{
	glGenBuffers(1, &object->vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object->vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, object->obj->vertex.size * sizeof(float) * 3,\
		&object->v_data[0].x, GL_STATIC_DRAW);
	glGenBuffers(1, &object->indices_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object->indices_buffer);
	glBufferData(GL_ARRAY_BUFFER, object->obj->indices.size * sizeof(int), \
		object->i_v_data, GL_STATIC_DRAW);
	glGenBuffers(1, &object->normals_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object->normals_buffer);
	glBufferData(GL_ARRAY_BUFFER, object->obj->vertex.size * sizeof(float) * 3, \
		&object->n_data[0].x, GL_STATIC_DRAW);
}

t_object	*new_object(char const *obj_file)
{
	t_object	*object;

	if ((object = ft_memalloc(sizeof(t_object))) == NULL)
		return (NULL);
	if ((object->obj = load_obj(obj_file)) == NULL)
		return (NULL);
	object->v_data = get_vertex_buffer(object->obj);
	object->i_v_data = get_indices_buffer(object->obj);
	object->n_data = get_normals_buffer(object);
	object->indices_size = object->obj->indices.size;
	object->transform = new_transform();
	gen_buffers(object);
	return (object);
}
