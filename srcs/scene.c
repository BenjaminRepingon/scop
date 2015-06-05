/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 15:57:19 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/05 12:26:06 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

static void	init_light2(t_scop *scop)
{
	t_light	*light;

	light = new_light(scop->prog, "lights[2]");
	// light->ambient = vector3f(0.1f, 0.1f, 0.1f);
	// light->diffuse = vector3f(0.5f, 0.5f, 0.5f);
	// light->specular = vector3f(0.4f, 0.4f, 0.4f);
	light->ambient = vector3f(0.0f, 0.0f, 0.5f);
	light->diffuse = vector3f(0.0f, 0.0f, 0.5f);
	light->specular = vector3f(0.0f, 0.0f, 0.2f);
	light->position = vector3f(17.0f, 10.0f, -17.0f);
	add_elem(&scop->light_list, light);
	light = new_light(scop->prog, "lights[3]");
	// light->ambient = vector3f(0.1f, 0.1f, 0.1f);
	// light->diffuse = vector3f(0.5f, 0.5f, 0.5f);
	// light->specular = vector3f(0.4f, 0.4f, 0.4f);
	light->ambient = vector3f(0.1f, 0.5f, 0.0f);
	light->diffuse = vector3f(0.1f, 0.5f, 0.0f);
	light->specular = vector3f(0.05f, 0.2f, 0.0f);
	light->position = vector3f(-17.0f, 10.0f, 17.0f);
	add_elem(&scop->light_list, light);
	light = new_light(scop->prog, "lights[4]");
	light->ambient = vector3f(0.2f, 0.2f, 0.2f);
	light->diffuse = vector3f(0.6f, 0.6f, 0.6f);
	light->specular = vector3f(0.5f, 0.5f, 0.5f);
	light->position = vector3f(-0.0f, 20.0f, 0.0f);
	add_elem(&scop->light_list, light);
}

static void	init_light(t_scop *scop)
{
	t_light	*light;

	light = new_light(scop->prog, "lights[0]");
	// light->ambient = vector3f(0.1f, 0.1f, 0.1f);
	// light->diffuse = vector3f(0.5f, 0.5f, 0.5f);
	// light->specular = vector3f(0.4f, 0.4f, 0.4f);
	light->ambient = vector3f(0.3f, 0.0f, 0.0f);
	light->diffuse = vector3f(0.8f, 0.0f, 0.0f);
	light->specular = vector3f(0.4f, 0.0f, 0.0f);
	light->position = vector3f(17.0f, 10.0f, 17.0f);
	add_elem(&scop->light_list, light);
	light = new_light(scop->prog, "lights[1]");
	// light->ambient = vector3f(0.1f, 0.1f, 0.1f);
	// light->diffuse = vector3f(0.5f, 0.5f, 0.5f);
	// light->specular = vector3f(0.4f, 0.4f, 0.4f);
	light->ambient = vector3f(0.5f, 0.5f, 0.0f);
	light->diffuse = vector3f(0.5f, 0.5f, 0.0f);
	light->specular = vector3f(0.2f, 0.2f, 0.0f);
	light->position = vector3f(-17.0f, 10.0f, -17.0f);
	add_elem(&scop->light_list, light);
	init_light2(scop);
}

void		init_scene(t_scop *scop, const char **argv)
{
	t_obj		*cube;
	t_obj		*object;

	scop->view = new_transform();
	scop->view->pos.x = 0;
	scop->view->pos.y = -3;
	scop->view->pos.z = 8;
	scop->projection = init_perspective(to_radians(70.0f), 850.0f / 550.0f, -0.1f, 1000.0f);
	cube = load_obj("inv_cube.obj");
	cube->transform->scale.x = 30;
	cube->transform->scale.y = 30;
	cube->transform->scale.z = 30;
	cube->transform->pos.y = 1;
	object = load_obj(argv[1]);
	object->transform->scale.x = 0.01;
	object->transform->scale.y = 0.01;
	object->transform->scale.z = 0.01;

	add_elem(&scop->object_list, object);
	add_elem(&scop->object_list, cube);
	init_light(scop);
}

void		update_scene(t_scop *scop)
{
	VEC3		*v;
	QUAT		*quat;
	t_obj		*object;
	t_elem		*elem;
	int			i;

	i = 0;
	elem = scop->object_list.first;
	while (elem)
	{
		object = (t_obj *)elem->data;
		if (i == 0)
		{
			v = new_vector3f(0, 1, 0);
			v = rotate3q(v, &object->transform->rot);
			quat = new_quaternion4vf(v, to_radians(20));
			ft_memdel((void **)&v);
			quat = normalized4(mul4q(quat, &object->transform->rot));
			object->transform->rot = *quat;
			ft_memdel((void **)&quat);
		}
		elem = elem->next;
		i++;
	}
}
