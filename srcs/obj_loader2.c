/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 16:06:19 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/05 10:08:14 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

static void	gen_normals_loop(t_object *object, VEC3 *buffer)
{
	int		i;
	int		i_012[3];
	VEC3	v_012[3];
	VEC3	v1;
	VEC3	v2;

	i = 0;
	while (i < object->indices.size)
	{
		i_012[0] = object->i_v_data[i + 0];
		i_012[1] = object->i_v_data[i + 1];
		i_012[2] = object->i_v_data[i + 2];
		v_012[0] = object->v_data[i_012[0]];
		v_012[1] = object->v_data[i_012[1]];
		v_012[2] = object->v_data[i_012[2]];
		v1 = *sub3v(&v_012[0], &v_012[1]);
		v_012[0] = object->v_data[i_012[0]];
		v2 = *sub3v(&v_012[0], &v_012[2]);
		v1 = *normalized3(cross3(&v1, &v2));
		add3v(&buffer[i_012[0]], &v1);
		add3v(&buffer[i_012[1]], &v1);
		add3v(&buffer[i_012[2]], &v1);
		i += 3;
	}
}

static void	gen_normals(t_object *object, VEC3 *buffer)
{
	int		i;

	i = 0;
	while (i < object->vertex.size)
		buffer[i++] = vector3f(0, 0, 0);
	gen_normals_loop(object, buffer);
	i = 0;
	while (i < object->vertex.size)
		normalized3(&buffer[i++]);
}

VEC3		*get_normals_buffer(t_object *object)
{
	t_elem	*elem;
	int		i;
	VEC3	*buffer;

	// if (object->obj->normals.size > 0)
	// {
	// 	if ((buffer = ft_memalloc(sizeof(VEC3) * object->obj->normals.size)) == NULL)
	// 		return (NULL);
	// 	elem = object->obj->normals.first;
	// 	i = 0;
	// 	while (elem)
	// 	{
	// 		buffer[i++] = *(VEC3 *)elem->data;
	// 		elem = elem->next;
	// 	}
	// 	return (buffer);
	// }
	// else
	// {
		if ((buffer = ft_memalloc(sizeof(VEC3) * object->vertex.size)) == NULL)
			return (NULL);
		gen_normals(object, buffer);
	// }
	return (buffer);
}
