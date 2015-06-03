/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 13:52:24 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/03 14:38:23 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/object.h"

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

static int	add_v_f(t_obj *obj, char **tmp)
{
	int		res;

	res = 1;
	if (ft_strlen(tmp[0]) == 1 && tmp[0][0] == 'v')
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
	else if (ft_strlen(tmp[0]) > 1 && tmp[0][0] == 'v' && tmp[0][1] == 'n')
		add_elem(&obj->normals, new_vector3f(ft_atof(tmp[1]), ft_atof(tmp[2]), \
			ft_atof(tmp[3])));
	else
		res = 0;
	return (res);
}

t_obj		*load_obj(const char *file)
{
	t_obj	*obj;
	int		fd;
	char	*line;
	char	**tmp;
	char	*mtllib;

	mtllib = NULL;
	if ((obj = ft_memalloc(sizeof(t_obj))) == NULL)
		return (NULL);
	obj->normals.size = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		exit_error("Can't find .obj");
		return (NULL);
	}
	while (get_next_line(fd, &line) != 0)
	{
		tmp = ft_strsplit(line, ' ');
		if (ft_tabsize((void **)tmp) < 2)
			continue ;
		if (!add_v_f(obj, tmp) && ft_strcmp(tmp[0], "mtllib") == 0)
			mtllib = ft_strdup(line + 7);
		ft_freetab((void **)tmp);
		ft_memdel((void **)&line);
	}
	if (mtllib)
		load_material_lib(obj, mtllib, file);
	return (obj);
}

VEC3		*get_vertex_buffer(t_obj *obj)
{
	t_elem	*elem;
	int		i;
	VEC3	*buffer;

	if ((buffer = ft_memalloc(sizeof(VEC3) * obj->vertex.size)) == NULL)
		return (NULL);
	elem = obj->vertex.first;
	i = 0;
	while (elem)
	{
		buffer[i++] = *(VEC3 *)elem->data;
		elem = elem->next;
	}
	return (buffer);
}

GLuint		*get_indices_buffer(t_obj *obj)
{
	t_elem	*elem;
	int		i;
	GLuint	*buffer;

	if ((buffer = ft_memalloc(sizeof(GLuint) * obj->indices.size)) == NULL)
		return (NULL);
	elem = obj->indices.first;
	i = 0;
	while (elem)
	{
		buffer[i++] = *((GLuint *)elem->data);
		elem = elem->next;
	}
	return (buffer);
}
