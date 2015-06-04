/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 11:33:59 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/04 15:49:43 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void		gen_buffers(t_object *object)
{
	object->v_data = get_vertex_buffer(object);
	object->i_v_data = get_indices_buffer(object);
	object->n_data = get_normals_buffer(object);
	object->indices_size = object->indices.size;
	glGenBuffers(1, &object->vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object->vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, object->vertex.size * sizeof(float) * 3,\
		&object->v_data[0].x, GL_STATIC_DRAW);
	glGenBuffers(1, &object->indices_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->indices_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, object->indices.size * sizeof(int), \
		object->i_v_data, GL_STATIC_DRAW);
	glGenBuffers(1, &object->normals_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object->normals_buffer);
	glBufferData(GL_ARRAY_BUFFER, object->vertex.size * sizeof(float) * 3, \
		&object->n_data[0].x, GL_STATIC_DRAW);
}

t_object	*new_object()
{
	t_object	*object;

	if ((object = ft_memalloc(sizeof(t_object))) == NULL)
		return (NULL);
	// if ((object->obj = load_obj(obj_file)) == NULL)
	// 	return (NULL);
	// gen_buffers(object);material
	object->material = NULL;
	return (object);
}
