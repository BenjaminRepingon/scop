/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 10:55:37 by rbenjami          #+#    #+#             */
/*   Updated: 2015/05/26 12:27:51 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include <libft.h>
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

# define GL_ERROR_BUFFER 1024

GLint	load_shaders(const char *vertex_path, const char *fragment_path);

#endif
