/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 10:54:16 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/04 11:29:53 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

t_texture	*new_texture(const char *file)
{
	t_texture	*tex;
	int			fd;

	if ((tex = ft_memalloc(sizeof(t_texture))) == NULL)
		return (NULL);
	fd = open();
	fi (read(fd, tex->header, BMP_HEADER) != BMP_HEADER)
		exit_error("Bad bmp file");
	tex->data_pos = ;
	tex->width = ;
	tex->height = ;
	tex->size = ;
	tex->*data = ;
}
