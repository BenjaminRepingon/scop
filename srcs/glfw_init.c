/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 14:53:51 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/02 15:12:25 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

static void	error_callback(int error, const char *description)
{
	(void)error;
	ft_putendl_fd((char *)description, 2);
}

static void	key_callback(GLFWwindow *w, int key, int sc, int action, int mods)
{
	t_scop	*scop;

	(void)sc;
	(void)mods;
	scop = get_scop();
	if (action == GLFW_PRESS)
		scop->key_pressed[key] = GL_TRUE;
	else if (action == GLFW_RELEASE)
		scop->key_pressed[key] = GL_FALSE;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		if (scop->have_focus)
			scop->have_focus = 0;
		else
			glfwSetWindowShouldClose(w, GL_TRUE);
		glfwSetInputMode(scop->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

static void	mouse_button_callback(GLFWwindow *w, int b, int action, int mods)
{
	t_scop	*scop;

	(void)w;
	(void)action;
	(void)mods;
	scop = get_scop();
	if (action == GLFW_PRESS)
		scop->button_pressed[b] = GL_TRUE;
	else if (action == GLFW_RELEASE)
		scop->button_pressed[b] = GL_FALSE;
}

void		pre_win_init(void)
{
	t_scop	*scop;

	scop = get_scop();
	scop->motion.x = 0;
	scop->motion.y = 0;
	scop->have_focus = 0;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
}

void		win_init(const char *name, int width, int height)
{
	t_scop	*scop;
	GLuint	vertex_array_id;

	scop = get_scop();
	scop->window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (!scop->window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(scop->window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(scop->window, key_callback);
	glfwSetMouseButtonCallback(scop->window, mouse_button_callback);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);
}
