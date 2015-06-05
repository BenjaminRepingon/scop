/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 15:12:52 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/05 10:42:29 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

static void	cam_update(t_scop *scop)
{
	QUAT	*quat;
	VEC3	*v;
	VEC3	v2;

	if (scop->motion.x || scop->motion.y)
	{
		if (scop->motion.x)
		{
			v2.x = 0;
			v2.y = 1;
			v2.z = 0;
			quat = new_quaternion4vf(&v2, scop->motion.x * -0.002);
			quat = normalized4(mul4q(quat, &scop->view->rot));
			scop->view->rot = *quat;
			ft_memdel((void **)&quat);
		}
		if (scop->motion.y)
		{
			v = new_vector3f(1, 0, 0);
			v = rotate3q(v, &scop->view->rot);
			quat = new_quaternion4vf(v, scop->motion.y * -0.002);
			ft_memdel((void **)&v);
			quat = normalized4(mul4q(quat, &scop->view->rot));
			scop->view->rot = *quat;
			ft_memdel((void **)&quat);
		}
	}
}

static void	motion_update(t_scop *scop)
{
	VEC3	*v;

	v = rotate3q(new_vector3f(0, 0, 1), &scop->view->rot);
	if (scop->key_pressed[GLFW_KEY_W])
		add3v(&scop->view->pos, mul3f(v, -0.2f));
	if (scop->key_pressed[GLFW_KEY_S])
		add3v(&scop->view->pos, mul3f(v, 0.2f));
	ft_memdel((void **)&v);
	v = rotate3q(new_vector3f(1, 0, 0), &scop->view->rot);
	if (scop->key_pressed[GLFW_KEY_D])
		add3v(&scop->view->pos, mul3f(v, -0.2f));
	if (scop->key_pressed[GLFW_KEY_A])
		add3v(&scop->view->pos, mul3f(v, 0.2f));
	ft_memdel((void **)&v);
	v = rotate3q(new_vector3f(0, 1, 0), &scop->view->rot);
	if (scop->key_pressed[GLFW_KEY_LEFT_SHIFT])
		add3v(&scop->view->pos, mul3f(v, 0.2f));
	if (scop->key_pressed[GLFW_KEY_SPACE])
		add3v(&scop->view->pos, mul3f(v, -0.2f));
	ft_memdel((void **)&v);
}

void		update_main_view(t_scop *scop)
{
	double	cursor_x;
	double	cursor_y;

	scop->motion.x *= 0.8;
	scop->motion.y *= 0.8;
	if (scop->motion.x < 1 && scop->motion.x > -1)
		scop->motion.x = 0;
	if (scop->motion.y < 1 && scop->motion.y > -1)
		scop->motion.y = 0;
	if (scop->button_pressed[GLFW_MOUSE_BUTTON_LEFT])
	{
		glfwGetCursorPos(scop->window, &cursor_x, &cursor_y);
		scop->motion.x += scop->width / 2.0 - cursor_x;
		scop->motion.y += scop->height / 2.0 - cursor_y;
	}
	cam_update(scop);
	motion_update(scop);
}
