/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 11:33:59 by rbenjami          #+#    #+#             */
/*   Updated: 2015/05/28 14:45:55 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/object.h"

t_object	*new_object(char const *obj_file)
{
	t_object	*object;
	t_obj		*obj;
	GLfloat		*vertex_buffer_data;
	GLint		*indices_buffer_data;
	GLfloat		*normals_buffer_data;

	if ((object = ft_memalloc(sizeof(t_object))) == NULL)
		return (NULL);
	if ((obj = load_obj(obj_file)) == NULL)
		return (NULL);
	vertex_buffer_data = get_vertex_buffer(obj);
	indices_buffer_data = get_indices_buffer(obj);
	normals_buffer_data = clac_normals(obj);
	object->indices_size = obj->indices.size;
	object->transform = new_transform();
	glGenBuffers(1, &object->vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object->vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, obj->vertex.size * sizeof(float) * 3, vertex_buffer_data, GL_STATIC_DRAW);
	glGenBuffers(1, &object->indices_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object->indices_buffer);
	glBufferData(GL_ARRAY_BUFFER, obj->indices.size * sizeof(int), indices_buffer_data, GL_STATIC_DRAW);
	glGenBuffers(1, &object->normals_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object->normals_buffer);
	glBufferData(GL_ARRAY_BUFFER, obj->vertex.size * sizeof(int), normals_buffer_data, GL_STATIC_DRAW);
	return (object);
}
