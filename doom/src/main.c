/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:29:09 by clala             #+#    #+#             */
/*   Updated: 2020/12/09 21:20:02 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_point			dot(int x, int y)
{
	t_point	new;

	new.x = x;
	new.y = y;
	return (new);
}

int				max(int a, int b)
{
	return (a > b ? a : b);
}

static t_wolf	*t_wolf_new(void)
{
	t_wolf		*new;

	!(new = (t_wolf *)malloc(sizeof(t_wolf))) ? error(new, ERR_MALLOC) : 0;
	!(new->map = (t_map *)malloc(sizeof(t_map))) ? error(new, ERR_MALLOC) : 0;
	if (!(new->player = (t_player *)malloc(sizeof(t_player))))
		error(new, ERR_MALLOC);
	if (!(new->sdl = (t_sdl *)malloc(sizeof(t_sdl))))
		error(new, ERR_MALLOC);
	if (!(new->bon = (t_bonus *)malloc(sizeof(t_bonus))))
		error(new, ERR_MALLOC);
	if (!(new->monster = (t_monster *)malloc(sizeof(t_monster))))
		error(new, ERR_MALLOC);
	new->walls[0].x1=7*CUBE;
	new->walls[0].y1=3*CUBE;
	new->walls[0].x2=14*CUBE;
	new->walls[0].y2=2*CUBE;

	new->walls[1].x1=14*CUBE;
	new->walls[1].y1=2*CUBE;
	new->walls[1].x2=17*CUBE;
	new->walls[1].y2=5*CUBE;

	new->walls[2].x1=17*CUBE;
	new->walls[2].y1=5*CUBE;
	new->walls[2].x2=8*CUBE;
	new->walls[2].y2=6*CUBE;

	new->walls[3].x1=8*CUBE;
	new->walls[3].y1=6*CUBE;
	new->walls[3].x2=7*CUBE;
	new->walls[3].y2=3*CUBE;

	return (new);
}

static void		validate_const(t_wolf *wolf)
{
	H > W ? error(wolf, ERR_INV_H) : 0;
	H < 300 || W < 384 ? error(wolf, ERR_INV_RES) : 0;
	H > H_MAX ? error_inv_n(wolf, ERR_H_MAX, H_MAX) : 0;
	W > W_MAX ? error_inv_n(wolf, ERR_W_MAX, W_MAX) : 0;
}

int				main(int a, char **b)
{
	t_wolf		*wolf;

	wolf = NULL;
	validate_const(wolf);
	a != 2 ? error(wolf, ERR_USAGE) : 0;
	SDL_Init(SDL_INIT_EVERYTHING) != 0 ? error(wolf, SDL_GetError()) : 0;
	TTF_Init() != 0 ? error(wolf, SDL_GetError()) : 0;
	wolf = t_wolf_new();
	init_map(wolf, b[1]);
	init_player(wolf, wolf->player, wolf->map);
	init_bonus(wolf);
	init_monster(wolf);
	music(wolf->bon);
	init_tex_arr(wolf);
	wolf_loop(wolf);
	return (0);
}
