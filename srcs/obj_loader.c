/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 13:52:24 by rbenjami          #+#    #+#             */
/*   Updated: 2015/05/28 14:59:23 by rbenjami         ###   ########.fr       */
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

float		*clac_normals(t_obj *obj)
{
	float	*normals_buffer;
	int		i;

	if ((normals_buffer = ft_memalloc(sizeof(float) * obj->vertex.size * 3)) == NULL)
		return (NULL);

	i = 0;
	while (i < obj->vertex.size * 3)
	{
		normals_buffer[i++] = 1;
		normals_buffer[i++] = 1;
		normals_buffer[i++] = 1;
	}
	return (normals_buffer);
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
