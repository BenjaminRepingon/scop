/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 13:47:22 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/05 12:24:34 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/scop.h"

t_material	*new_material(char *name)
{
	t_material	*material;

	if ((material = (t_material *)ft_memalloc(sizeof(t_material))) == NULL)
		return (NULL);
	material->newmtl = ft_strdup(name);
	return (material);
}

void	update_material_uniform(t_scop *scop, t_material *mat)
{
	if (mat)
	{
		glUniform3f(scop->location_ka, mat->ka.x, mat->ka.y, mat->ka.z);
		glUniform3f(scop->location_kd, mat->kd.x, mat->kd.y, mat->kd.z);
		glUniform3f(scop->location_ks, mat->ks.x, mat->ks.y, mat->ks.z);
		glUniform1f(scop->location_d, mat->d);
		glUniform1f(scop->location_ns, mat->ns);
		glUniform1i(scop->location_illum, mat->illum);
	}
	else
	{
		glUniform3f(scop->location_ka, 1.0f, 1.0f, 1.0f);
		glUniform3f(scop->location_kd, 1.0f, 1.0f, 1.0f);
		glUniform3f(scop->location_ks, 1.0f, 1.0f, 1.0f);
		glUniform1f(scop->location_d, 1);
		glUniform1f(scop->location_ns, 1);
		glUniform1i(scop->location_illum, 1);
	}
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

static t_material	*find_material(t_obj *obj, char *name)
{
	t_elem		*elem;
	t_material	*mat;

	elem = obj->materials.first;
	while (elem)
	{
		mat = (t_material *)elem->data;
		if (ft_strcmp(mat->newmtl, name) == 0)
			return (mat);
		elem = elem->next;
	}
	return (NULL);
}

static void		assign_material(t_obj *obj)
{
	t_elem		*elem;
	t_object	*object;

	elem = obj->objects.first;
	while (elem)
	{
		object = (t_object *)elem->data;
		if (object->usemtl)
			object->material = find_material(obj, object->usemtl);
		elem = elem->next;
	}
}

void		load_material_lib(t_obj *obj, char *file, char *obj_file)
{
	int			fd;
	char		*line;
	char		**tmp;
	t_material	*material;

	material = NULL;
	file = file_path(file, obj_file);
	ft_putendl(file);
	if ((fd = open(file, O_RDONLY)) == -1)
		exit_error("Can't find .mtl");
	ft_memdel((void **)&file);
	while (get_next_line(fd, &line) != 0)
	{
		tmp = ft_strsplit(line, ' ');
		if (ft_strlen(line) <= 1)
		{
			ft_freetab((void **)tmp);
			ft_memdel((void **)&line);
			continue ;
		}
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
	if (line)
		ft_memdel((void **)&line);
	if (material)
		add_elem(&obj->materials, material);
	assign_material(obj);
}
