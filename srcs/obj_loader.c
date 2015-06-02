/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 13:52:24 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/02 16:15:21 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/obj_loader.h"

static void	put_indices(t_list *indices_list, int a, int b, int c)
{
	int		*indices;

	indices = ft_memalloc(sizeof(int) * 3);
	indices[0] = a;
	add_elem(indices_list, &indices[0]);
	indices[1] = b;
	add_elem(indices_list, &indices[1]);
	indices[2] = c;
	add_elem(indices_list, &indices[2]);
}

static void	add_v_f(t_obj *obj, char **tmp)
{
	if (tmp[0][0] == 'v')
		add_elem(&obj->vertex, new_vector3f(ft_atof(tmp[1]), ft_atof(tmp[2]), \
			ft_atof(tmp[3])));
	else if (tmp[0][0] == 'f')
	{
		put_indices(&obj->indices, ft_atoi(tmp[1]) - 1, ft_atoi(tmp[2]) - 1, \
			ft_atoi(tmp[3]) - 1);
		if (ft_tabsize((void **)tmp) == 5)
			put_indices(&obj->indices, ft_atoi(tmp[3]) - 1, \
				ft_atoi(tmp[4]) - 1, ft_atoi(tmp[1]) - 1);
	}
}

t_obj		*load_obj(const char *file)
{
	t_obj	*obj;
	int		fd;
	char	*line;
	char	**tmp;

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
		add_v_f(obj, tmp);
		ft_freetab((void **)tmp);
		ft_memdel((void **)&line);
	}
	return (obj);
}

float		*get_vertex_buffer(t_obj *obj)
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

int			*get_indices_buffer(t_obj *obj)
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
