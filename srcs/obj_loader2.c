/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 16:06:19 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/02 16:15:43 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/obj_loader.h"

static void	add_and_del(t_obj *obj, VEC3 *v1, VEC3 *v2, int i_012[3])
{
	add3v((VEC3 *)get_elem(&obj->normals, i_012[0])->data, v1);
	add3v((VEC3 *)get_elem(&obj->normals, i_012[1])->data, v1);
	add3v((VEC3 *)get_elem(&obj->normals, i_012[2])->data, v1);
	ft_memdel((void **)&v1);
	ft_memdel((void **)&v2);
}

static void	gen_normals_loop(t_obj *obj, VEC3 *v, VEC3 *v1, VEC3 *v2)
{
	int		i;
	int		i_012[3];
	t_elem	*elem;

	i = 0;
	elem = obj->indices.first;
	while (i < obj->indices.size)
	{
		i_012[0] = *(int *)elem->data;
		elem = elem->next;
		i_012[1] = *(int *)elem->data;
		elem = elem->next;
		i_012[2] = *(int *)elem->data;
		elem = elem->next;
		v = (VEC3 *)get_elem(&obj->vertex, i_012[0])->data;
		v = new_vector3f(v->x, v->y, v->z);
		v1 = sub3v(v, (VEC3 *)get_elem(&obj->vertex, i_012[1])->data);
		v = (VEC3 *)get_elem(&obj->vertex, i_012[0])->data;
		v = new_vector3f(v->x, v->y, v->z);
		v2 = sub3v(v, (VEC3 *)get_elem(&obj->vertex, i_012[2])->data);
		v1 = normalized3(cross3(v1, v2));
		add_and_del(obj, v1, v2, i_012);
		i += 3;
	}
}

static void	gen_normals(t_obj *obj)
{
	int		i;
	t_elem	*elem;

	i = 0;
	while (i < obj->vertex.size)
	{
		add_elem(&obj->normals, new_vector3f(0, 0, 0));
		i++;
	}
	i = 0;
	gen_normals_loop(obj, NULL, NULL, NULL);
	elem = obj->normals.first;
	while (elem)
	{
		normalized3((VEC3 *)elem->data);
		elem = elem->next;
	}
}

float		*clac_normals(t_obj *obj)
{
	t_elem	*elem;
	int		i;
	float	*buffer;
	VEC3	*vec;

	gen_normals(obj);
	if ((buffer = ft_memalloc(sizeof(float) * 3 * obj->normals.size)) == NULL)
		return (NULL);
	elem = obj->normals.first;
	i = 0;
	while (elem)
	{
		vec = (VEC3 *)elem->data;
		buffer[i++] = vec->x;
		buffer[i++] = vec->y;
		buffer[i++] = vec->z;
		elem = elem->next;
	}
	return (buffer);
}
