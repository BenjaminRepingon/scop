/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 15:03:26 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/01 15:34:07 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include <libft.h>
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

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

t_light		*new_light(GLint program, const char *name);
void		update_light(t_light *light);

#endif
