/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 20:18:45 by zion              #+#    #+#             */
/*   Updated: 2015/06/01 15:43:05 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <libft.h>
# include "object.h"
# include "light.h"

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
	GLint			shaderProgram;
}					t_scop;

#endif
