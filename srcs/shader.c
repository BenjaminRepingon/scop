/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 10:55:32 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/05 10:32:20 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/shader.h"

static char		*load_file(const char *file)
{
	int		fd;
	char	*line;
	char	*res;
	char	*tmp;

	res = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	while (get_next_line(fd, &line))
	{
		tmp = ft_strjoin(res, line);
		ft_memdel((void **)&line);
		if (res)
			ft_memdel((void **)&res);
		res = ft_strjoin(tmp, "\n");
		ft_memdel((void **)&tmp);
	}
	if (line)
		ft_memdel((void **)&line);
	return (res);
}

static GLint	compile_shader(const GLchar *shader_code, int type)
{
	GLint		shader_id;
	GLint		result;
	char		shader_error_message[GL_ERROR_BUFFER];

	shader_id = glCreateShader(type);
	result = GL_FALSE;
	glShaderSource(shader_id, 1, &shader_code, NULL);
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderInfoLog(shader_id, GL_ERROR_BUFFER, NULL, shader_error_message);
	if (result == GL_FALSE)
		exit_error(shader_error_message);
	return (shader_id);
}

static GLint	link_program(GLint const vertex_id, GLint const fragment_id)
{
	GLint		program;
	GLint		result;
	char		program_error_message[GL_ERROR_BUFFER];

	program = glCreateProgram();
	result = GL_FALSE;
	glAttachShader(program, vertex_id);
	glAttachShader(program, fragment_id);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramInfoLog(program, GL_ERROR_BUFFER, NULL, program_error_message);
	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);
	if (result == GL_FALSE)
		exit_error(program_error_message);
	return (program);
}

GLint			load_shaders(const char *vertex_path, const char *fragment_path)
{
	GLint		vertex_shader_id;
	GLint		fragement_shader_id;
	char		*file_content;

	if ((file_content = load_file(vertex_path)) == NULL)
		return (-1);
	vertex_shader_id = compile_shader(file_content, GL_VERTEX_SHADER);
	ft_memdel((void **)&file_content);
	if ((file_content = load_file(fragment_path)) == NULL)
		return (-1);
	fragement_shader_id = compile_shader(file_content, GL_FRAGMENT_SHADER);
	ft_memdel((void **)&file_content);
	return (link_program(vertex_shader_id, fragement_shader_id));
}
