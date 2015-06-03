/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 20:18:45 by zion              #+#    #+#             */
/*   Updated: 2015/06/03 11:30:16 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <libft.h>
# include "object.h"
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

enum				e_uniform
{
	MODEL,
	VIEW,
	PROJECTION,
	NUM_LIGHTS,
	EYE_POS,
	SIZE
};

typedef struct		s_scop
{
	GLFWwindow		*window;
	int				width;
	int				height;
	TRAN			*view;
	VEC2			motion;
	uint8_t			have_focus;
	t_list			object_list;
	t_list			light_list;
	GLint			prog;
	int				key_pressed[GLFW_KEY_LAST];
	int				button_pressed[GLFW_MOUSE_BUTTON_LAST];
	MAT4			*projection;
	GLint			uniforms[SIZE];
	int				frame;
}					t_scop;

typedef struct		s_light
{
	VEC3			ambient;
	VEC3			diffuse;
	VEC3			specular;
	VEC3			position;
	GLint			location_ambient;
	GLint			location_diffuse;
	GLint			location_specular;
	GLint			location_position;
}					t_light;

t_light				*new_light(GLint program, const char *name);
void				update_light(t_light *light);
void				update_lights(t_scop *scop);
t_scop				*get_scop(void);
void				pre_win_init(void);
void				win_init(const char *name, int width, int height);
void				update_main_view(t_scop *scop);
void				update_scene(t_scop *scop);
void				init_scene(t_scop *scop, const char **argv);

#endif
