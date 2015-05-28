/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 20:18:35 by zion              #+#    #+#             */
/*   Updated: 2015/05/28 14:57:22 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include "../includes/scop.h"

int		key_pressed[GLFW_KEY_LAST];
int		button_pressed[GLFW_MOUSE_BUTTON_LAST];

t_scop	*get_scop()
{
	static t_scop	scop;

	return (&scop);
}

static void error_callback(int error, const char* description)
{
	(void)error;
	ft_putendl_fd((char *)description, 2);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	t_scop	*scop;
	(void)scancode;
	(void)mods;

	scop = get_scop();
	if (action == GLFW_PRESS)
		key_pressed[key] = GL_TRUE;
	else if (action == GLFW_RELEASE)
		key_pressed[key] = GL_FALSE;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		if (scop->have_focus)
			scop->have_focus = 0;
		else
			glfwSetWindowShouldClose(window, GL_TRUE);
		glfwSetInputMode(scop->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	(void)window;
	(void)button;
	(void)action;
	(void)mods;

	if (action == GLFW_PRESS)
		button_pressed[button] = GL_TRUE;
	else if (action == GLFW_RELEASE)
		button_pressed[button] = GL_FALSE;
	// printf("%lf - %lf\n", x, y);
}

void	update_main_view(t_scop *scop)
{
	double	cursor_x;
	double	cursor_y;
	// MAT4	*tmp1;
	// MAT4	*tmp2;
	QUAT	*quat;

	scop->motion.x *= 0.8;
	scop->motion.y *= 0.8;
	if (scop->motion.x < 1 && scop->motion.x > -1)
		scop->motion.x = 0;
	if (scop->motion.y < 1 && scop->motion.y > -1)
		scop->motion.y = 0;
	if (button_pressed[GLFW_MOUSE_BUTTON_LEFT])
	{
		glfwGetCursorPos(scop->window, &cursor_x, &cursor_y);
		scop->motion.x += scop->width / 2.0 - cursor_x;
		scop->motion.y += scop->height / 2.0 - cursor_y;
	}
	if (scop->motion.x || scop->motion.y)
	{
		if (scop->motion.x)
		{
			VEC3	top;
			top.x = 0;
			top.y = 1;
			top.z = 0;
			quat = new_quaternion4vf(&top, scop->motion.x * 0.002);
			quat = normalized4(mul4q(quat, &scop->view->rot));
			scop->view->rot = *quat;
			ft_memdel((void **)&quat);
		}
		if (scop->motion.y)
		{
			VEC3	*right = rotate3q(new_vector3f(1, 0, 0), &scop->view->rot);
			quat = new_quaternion4vf(right, scop->motion.y * 0.002);
			quat = normalized4(mul4q(quat, &scop->view->rot));
			scop->view->rot = *quat;
			ft_memdel((void **)&quat);
		}
	}
	VEC3	*forward = rotate3q(new_vector3f(0, 0, 1), &scop->view->rot);
	if (key_pressed[GLFW_KEY_W])
		add3v(&scop->view->pos, mul3f(forward, 0.5f));
	if (key_pressed[GLFW_KEY_S])
		add3v(&scop->view->pos, mul3f(forward, -0.5f));
	ft_memdel((void **)&forward);

	VEC3	*right = rotate3q(new_vector3f(1, 0, 0), &scop->view->rot);
	if (key_pressed[GLFW_KEY_D])
		add3v(&scop->view->pos, mul3f(right, -0.5f));
	if (key_pressed[GLFW_KEY_A])
		add3v(&scop->view->pos, mul3f(right, 0.5f));
	ft_memdel((void **)&forward);

	VEC3	*top = rotate3q(new_vector3f(0, 1, 0), &scop->view->rot);
	if (key_pressed[GLFW_KEY_LEFT_SHIFT])
		add3v(&scop->view->pos, mul3f(top, 0.5f));
	if (key_pressed[GLFW_KEY_SPACE])
		add3v(&scop->view->pos, mul3f(top, -0.5f));
	ft_memdel((void **)&forward);
}

void	init_scene(t_scop *scop, const char **argv)
{
	t_object	*plan;
	t_object	*teapot;

	plan = new_object("plan.obj");
	plan->transform->scale.x = 10;
	plan->transform->scale.y = 10;
	plan->transform->scale.z = 10;
	teapot = new_object(argv[1]);
	add_elem(&scop->object_list, teapot);
	add_elem(&scop->object_list, plan);
}

int main(int argc, const char *argv[])
{
	t_scop	*scop;
	if (argc < 2)
		return (-1);

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

	scop->window = glfwCreateWindow(850, 550, "Simple example", NULL, NULL);
	if (!scop->window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(scop->window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(scop->window, key_callback);
	glfwSetMouseButtonCallback(scop->window, mouse_button_callback);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	// t_obj	*obj = load_obj(argv[1]);

	// GLfloat	*vertex_buffer_data = get_vertex_buffer(obj);
	// GLint	*indices_buffer_data = get_indices_buffer(obj);

	GLint	shaderProgram = load_shaders("./vertex.glsl", "./fragment.glsl");

	GLint	model_matrix_id = glGetUniformLocation(shaderProgram, "model");
	GLint	view_matrix_id = glGetUniformLocation(shaderProgram, "view");
	GLint	projection_matrix_id = glGetUniformLocation(shaderProgram, "projection");


	// MAT4	*model = init_scale(1, 1, 1);

	VEC3	pos;
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	scop->view = new_transform();
			// QUAT	*quat;
			// quat = new_quaternion4vf(new_vector3f(0, 1, 0), -90.0f);
			// scop->view->rot = *normalized4(mul4q(&scop->view->rot, quat));
	MAT4	*projection = init_perspective(to_radians(70.0f), 850.0f / 550.0f, 0.01f, 1000.0f);

	if (shaderProgram == -1)
		exit_error("Unable to load shaders");

	init_scene(scop, argv);
	// GLuint vertex_buffer;// This will identify our vertex buffer
	// glGenBuffers(1, &vertex_buffer);// Generate 1 buffer, put the resulting identifier in vertex_buffer
	// glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);// The following commands will talk about our 'vertex_buffer' buffer
	// glBufferData(GL_ARRAY_BUFFER, obj->vertex.size * sizeof(float) * 3, vertex_buffer_data, GL_STATIC_DRAW);// Give our vertices to OpenGL.

	// GLuint indices_buffer;// This will identify our indices buffer
	// glGenBuffers(1, &indices_buffer);// Generate 1 buffer, put the resulting identifier in indices_buffer
	// glBindBuffer(GL_ARRAY_BUFFER, indices_buffer);// The following commands will talk about our 'indices_buffer' buffer
	// glBufferData(GL_ARRAY_BUFFER, obj->indices.size * sizeof(int), indices_buffer_data, GL_STATIC_DRAW);// Give our vertices to OpenGL.
//-----
	t_elem		*tmp;
	t_object	*object;
	MAT4		*transformed_view;
	MAT4		*transformed_model;
	// glfwSetCursorPos(scop->window, scop->width / 2, scop->height / 2);
	while (!glfwWindowShouldClose(scop->window))
	{
		glfwGetFramebufferSize(scop->window, &scop->width, &scop->height);
		glViewport(0, 0, scop->width, scop->height);
		// update_fov_aspect(projection, to_radians(70.0f), width / height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram);
//-----

		update_main_view(scop);
		transformed_view = get_transforms(scop->view);

		tmp = scop->object_list.first;
		glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, &transformed_view->m[0][0]);
		glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE, &projection->m[0][0]);
		while (tmp)
		{
			object = (t_object *)tmp->data;
			transformed_model = get_transforms(object->transform);
			glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, &transformed_model->m[0][0]);
			ft_memdel((void **)&transformed_model);

	//-----
			// 1rst attribute buffer : vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, object->vertex_buffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, object->normals_buffer);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->indices_buffer);

			// Draw the triangles !
			glDrawElements(GL_TRIANGLES, object->indices_size, GL_UNSIGNED_INT, (void*)0);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			tmp = tmp->next;
		}
		ft_memdel((void **)&transformed_view);
//-----

		glfwSwapBuffers(scop->window);
		glfwPollEvents();
	}
	glfwDestroyWindow(scop->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
