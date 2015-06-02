/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 20:18:35 by zion              #+#    #+#             */
/*   Updated: 2015/06/02 16:28:27 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

t_scop		*get_scop(void)
{
	static t_scop	scop;

	return (&scop);
}

static void	shader_and_uniforms(t_scop *scop)
{
	scop->prog = load_shaders("./vertex.glsl", "./fragment.glsl");
	if (scop->prog == -1)
		exit_error("Unable to load shaders");
	scop->uniforms[MODEL] = glGetUniformLocation(scop->prog, "model");
	scop->uniforms[VIEW] = glGetUniformLocation(scop->prog, "view");
	scop->uniforms[PROJECTION] = glGetUniformLocation(scop->prog, "projection");
	scop->uniforms[NUM_LIGHTS] = glGetUniformLocation(scop->prog, "numLights");
	scop->uniforms[EYE_POS] = glGetUniformLocation(scop->prog, "eyePos");
}

static void	update_objects(t_scop *scop)
{
	t_elem		*tmp;
	t_object	*object;
	MAT4		*transformed_model;

	tmp = scop->object_list.first;
	while (tmp)
	{
		object = (t_object *)tmp->data;
		transformed_model = get_transforms(object->transform);
		glUniformMatrix4fv(scop->uniforms[MODEL], 1, GL_FALSE,\
			&transformed_model->m[0][0]);
		ft_memdel((void **)&transformed_model);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, object->vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, object->normals_buffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->indices_buffer);
		glDrawElements(GL_TRIANGLES, object->indices_size, GL_UNSIGNED_INT, \
			(void*)0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		tmp = tmp->next;
	}
}

static void	main_loop(t_scop *scop)
{
	MAT4		*transformed_view;

	while (!glfwWindowShouldClose(scop->window))
	{
		scop->frame = (scop->frame == 60) ? 0 : scop->frame;
		glfwGetFramebufferSize(scop->window, &scop->width, &scop->height);
		glViewport(0, 0, scop->width, scop->height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(scop->prog);
		update_main_view(scop);
		update_scene(scop);
		transformed_view = get_transforms(scop->view);
		glUniformMatrix4fv(scop->uniforms[PROJECTION], 1, GL_FALSE, \
			&scop->projection->m[0][0]);
		glUniformMatrix4fv(scop->uniforms[VIEW], 1, GL_FALSE, \
			&transformed_view->m[0][0]);
		glUniform3f(scop->uniforms[EYE_POS], scop->view->pos.x, \
			scop->view->pos.y, scop->view->pos.z);
		update_lights(scop);
		update_objects(scop);
		ft_memdel((void **)&transformed_view);
		glfwSwapBuffers(scop->window);
		glfwPollEvents();
		scop->frame++;
	}
}

int			main(int argc, const char *argv[])
{
	t_scop	*scop;

	if (argc < 2)
		return (-1);
	scop = get_scop();
	scop->frame = 0;
	pre_win_init();
	win_init("Scop", 850, 550);
	shader_and_uniforms(scop);
	init_scene(scop, argv);
	main_loop(scop);
	glfwDestroyWindow(scop->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
