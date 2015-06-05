/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 20:18:45 by zion              #+#    #+#             */
/*   Updated: 2015/06/05 10:09:00 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <libft.h>
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

# define BMP_HEADER 54

enum				e_uniform
{
	MODEL,
	VIEW,
	PROJECTION,
	NUM_LIGHTS,
	EYE_POS,
	SIZE
};

typedef struct		s_texture
{
	unsigned char	header[BMP_HEADER];
	size_t			data_pos;
	size_t			width;
	size_t			height;
	size_t			size;
	unsigned char	*data;
}					t_texture;

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
	GLuint			location_ka;
	GLuint			location_kd;
	GLuint			location_ks;
	GLuint			location_d;
	GLuint			location_ns;
	GLuint			location_illum;
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

typedef struct		s_material
{
	char			*newmtl;
	VEC3			ka;
	VEC3			kd;
	VEC3			ks;
	float			d;
	float			ns;
	int				illum;
}					t_material;

typedef struct		s_object
{
	GLuint			vertex_buffer;
	GLuint			indices_buffer;
	GLuint			normals_buffer;
	VEC3			*v_data;
	GLuint			*i_v_data;
	VEC3			*n_data;
	t_list			vertex;
	t_list			indices;
	t_list			normals;
	int				indices_size;
	t_material		*material;
	char			*usemtl;
}					t_object;

typedef struct		s_obj
{
	TRAN			*transform;
	t_list			materials;
	t_list			objects;
}					t_obj;

t_obj				*load_obj(const char *file);
VEC3				*get_vertex_buffer(t_object *obj);
GLuint				*get_indices_buffer(t_object *obj);
VEC3				*get_normals_buffer(t_object *object);
void				gen_buffers(t_object *object);

t_object			*new_object();

void				load_material_lib(t_obj *obj, char *file, char *obj_file);

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
