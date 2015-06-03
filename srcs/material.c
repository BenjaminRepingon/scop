/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 13:47:22 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/03 15:04:01 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/object.h"

t_material	*new_material(char *name)
{
	t_material	*material;

	if ((material = (t_material *)ft_memalloc(sizeof(t_material))) == NULL)
		return (NULL);
	material->newmtl = ft_strdup(name);
	return (material);
}

static void	load_colors(t_material *material, char **colors, char type)
{
	if (type == 'a')
		material->ka = vector3f(ft_atof(colors[0]), ft_atof(colors[1]), ft_atof(colors[2]));
	if (type == 'd')
		material->kd = vector3f(ft_atof(colors[0]), ft_atof(colors[1]), ft_atof(colors[2]));
	if (type == 's')
		material->ks = vector3f(ft_atof(colors[0]), ft_atof(colors[1]), ft_atof(colors[2]));
}

static char	*file_path(char *file, char *obj_file)
{
	int		i;
	char	*res;

	i = ft_strrchr(obj_file, '/') - obj_file;
	res = ft_strnew(i + ft_strlen(file) + 1);
	ft_strncpy(res, obj_file, i + 1);
	ft_strncpy(res + i + 1, file, ft_strlen(file));
	return (res);
}

void		load_material_lib(t_obj *obj, char *file, char *obj_file)
{
	int			fd;
	char		*line;
	char		**tmp;
	t_material	*material;

	material = NULL;
	if ((fd = open(file_path(file, obj_file), O_RDONLY)) == -1)
		exit_error("Can't find .mtl");
	while (get_next_line(fd, &line) != 0)
	{
		tmp = ft_strsplit(line, ' ');
		if (ft_strcmp(tmp[0], "newmtl") == 0)
		{
			if (material)
				add_elem(&obj->materials, material);
			material = new_material(tmp[1]);
		}
		else if (material && tmp[0][0] == 'K')
			load_colors(material, &tmp[1], tmp[0][1]);
		else if (material && tmp[0][0] == 'd')
			material->d = ft_atof(tmp[1]);
		else if (material && tmp[0][0] == 'N')
			material->ns = ft_atof(tmp[1]);
		else if (material && tmp[0][0] == 'i')
			material->illum = ft_atoi(tmp[1]);
		ft_freetab((void **)tmp);
		ft_memdel((void **)&line);
	}
	if (material)
		add_elem(&obj->materials, material);
}
