/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 13:52:24 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/01 15:38:23 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/obj_loader.h"

t_obj	*load_obj(const char *file)
{
	t_obj	*obj;
	int		fd;
	char	*line;
	char	**tmp;
	int		*indices;

	if ((obj = ft_memalloc(sizeof(t_obj))) == NULL)
		return (NULL);
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		exit_error("Can't fint .obj");
		return (NULL);
	}
	while (get_next_line(fd, &line) != 0)
	{
		tmp = ft_strsplit(line, ' ');
		if (ft_tabsize((void **)tmp) < 2)
			continue ;
		if (tmp[0][0] == 'v')
			add_elem(&obj->vertex, new_vector3f(ft_atof(tmp[1]), ft_atof(tmp[2]), ft_atof(tmp[3])));
		else if (tmp[0][0] == 'f')
		{
			indices = ft_memalloc(sizeof(int) * 3);
			indices[0] = ft_atoi(tmp[1]) - 1;
			add_elem(&obj->indices, &indices[0]);
			indices[1] = ft_atoi(tmp[2]) - 1;
			add_elem(&obj->indices, &indices[1]);
			indices[2] = ft_atoi(tmp[3]) - 1;
			add_elem(&obj->indices, &indices[2]);
		}
		ft_freetab((void **)tmp);
		ft_memdel((void **)&line);
	}
	return (obj);
}

static void		gen_normals(t_obj *obj)
{
	int		i;
	int		i0;
	int		i1;
	int		i2;
	VEC3	*v;
	VEC3	*v1;
	VEC3	*v2;
	t_elem	*elem;

	i = 0;
	while (i < obj->vertex.size)
	{
		add_elem(&obj->normals, new_vector3f(0, 0, 0));
		i++;
	}
	i = 0;
	elem = obj->indices.first;
	while (i < obj->indices.size)
	{
		i0 = *(int *)elem->data;
		elem = elem->next;
		i1 = *(int *)elem->data;
		elem = elem->next;
		i2 = *(int *)elem->data;
		elem = elem->next;

		v = (VEC3 *)get_elem(&obj->vertex, i1)->data;
		v = new_vector3f(v->x, v->y, v->z);
		v1 = sub3v(v, (VEC3 *)get_elem(&obj->vertex, i0)->data);
		v = (VEC3 *)get_elem(&obj->vertex, i2)->data;
		v = new_vector3f(v->x, v->y, v->z);
		v2 = sub3v(v, (VEC3 *)get_elem(&obj->vertex, i0)->data);

		v1 = normalized3(cross3(v1, v2));
		add3v((VEC3 *)get_elem(&obj->normals, i0)->data, v1);
		add3v((VEC3 *)get_elem(&obj->normals, i1)->data, v1);
		add3v((VEC3 *)get_elem(&obj->normals, i2)->data, v1);
		ft_memdel((void **)&v1);
		ft_memdel((void **)&v2);
		i += 3;
	}
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

float	*get_vertex_buffer(t_obj *obj)
{
	t_elem	*elem;
	int		i;
	float	*buffer;
	VEC3	*vec;

	if ((buffer = ft_memalloc(sizeof(float) * 3 * obj->vertex.size)) == NULL)
		return (NULL);
	elem = obj->vertex.first;
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

int		*get_indices_buffer(t_obj *obj)
{
	t_elem	*elem;
	int		i;
	int		*buffer;

	if ((buffer = ft_memalloc(sizeof(float) * 3 * obj->indices.size)) == NULL)
		return (NULL);
	elem = obj->indices.first;
	i = 0;
	while (elem)
	{
		buffer[i++] = *((int *)elem->data);
		elem = elem->next;
	}
	return (buffer);
}
