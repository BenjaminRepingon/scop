/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 15:03:11 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/02 16:05:26 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

t_light		*new_light(GLint program, const char *name)
{
	t_light	*light;
	char	*tmp;

	if ((light = (t_light *)ft_memalloc(sizeof(t_light))) == NULL)
		return (NULL);
	tmp = ft_strjoin((char *)name, ".ambient");
	light->location_ambient = glGetUniformLocation(program, tmp);
	ft_memdel((void **)&tmp);
	tmp = ft_strjoin((char *)name, ".diffuse");
	light->location_diffuse = glGetUniformLocation(program, tmp);
	ft_memdel((void **)&tmp);
	tmp = ft_strjoin((char *)name, ".specular");
	light->location_specular = glGetUniformLocation(program, tmp);
	ft_memdel((void **)&tmp);
	tmp = ft_strjoin((char *)name, ".position");
	light->location_position = glGetUniformLocation(program, tmp);
	ft_memdel((void **)&tmp);
	return (light);
}

void		update_light(t_light *light)
{
	glUniform3f(light->location_ambient, light->ambient.x, \
		light->ambient.y, light->ambient.z);
	glUniform3f(light->location_diffuse, light->diffuse.x, \
		light->diffuse.y, light->diffuse.z);
	glUniform3f(light->location_specular, light->specular.x, \
		light->specular.y, light->specular.z);
	glUniform3f(light->location_position, light->position.x, \
		light->position.y, light->position.z);
}

void		update_lights(t_scop *scop)
{
	t_elem	*tmp;

	tmp = scop->light_list.first;
	while (tmp)
	{
		update_light((t_light *)tmp->data);
		tmp = tmp->next;
	}
	glUniform1i(scop->uniforms[NUM_LIGHTS], scop->light_list.size);
}
