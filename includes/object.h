/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 11:34:19 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/02 16:37:50 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include <libft.h>
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include "shader.h"
# include "obj_loader.h"

typedef struct		s_object
{
	t_obj			*obj;
	TRAN			*transform;
	GLuint			vertex_buffer;
	GLuint			indices_buffer;
	GLuint			normals_buffer;
	int				indices_size;
}					t_object;

t_object			*new_object(char const *obj_file);

#endif
