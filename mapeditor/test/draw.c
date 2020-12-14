#include "map.h"

void draw_gr(t_map *mp, int x, int y, unsigned char c)
{
	int pixel;

	if (x < WIDTH && y < HEIGHT)
	{
		pixel = (x * mp->pixb) + (y * mp->strb);
		mp->s[pixel] = 0;
		mp->s[++pixel] = c;
		mp->s[++pixel] = 0;
	}
}

void draw_pr(t_map *mp, int x, int y, unsigned char c)
{
	int pixel;

	if (x < WIDTH && y < HEIGHT)
	{
		pixel = (x * mp->pixb) + (y * mp->strb);
		mp->s[pixel] = c;
		mp->s[++pixel] = 0;
		mp->s[++pixel] = c;
	}
}

void draw_node(t_map *mp, t_nod *n)
{
	int x1 = n->x1 + mp->z_x;
	int x2 = n->x2 + mp->z_x;
	if (x1 < 0 && x2 < 0)
		return;
	int y1 = n->y1 + mp->z_y;
	int y2 = n->y2 + mp->z_y;
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	int er = 0;
	int de = dy + 1;
	int j = y1;
	int diry;
	int i = x1;
	int di = 0;
	if (dx > dy)
	{
		i = x1;
		j = y1;
		di = (x2 - x1) / dx;
		diry = y2 - y1;
		de = dy + 1;
		if (diry > 0)
			diry = 1;
		if (diry < 0)
			diry = -1;
		
		while (i != x2)
		{
			draw_gr(mp, i, j, 80);
			er += de;
			if (er >= dx + 1)
			{
				j += diry;
				er = er - (dx + 1);
			}
			i += di;
		}
	}
	else if (dy != 0)
	{
		i = y1;
		j = x1;
		di = (y2 - y1) / dy;
		diry = x2 - x1;
		de = dx + 1;
		if (diry > 0)
			diry = 1;
		if (diry < 0)
			diry = -1;
		
		while (i != y2)
		{
			draw_gr(mp, j, i, 80);
			er += de;
			if (er >= dy + 1)
			{
				j += diry;
				er = er - (dy + 1);
			}
			i += di;
		}
	}
	draw_pixel(mp, x1, y1, 250);
	draw_pixel(mp, x2, y2, 250);
}

void draw_nodes(t_map *mp)
{
	t_nod *n;

	n = mp->nod;
	if (n == NULL)
		return;
	while (n)
	{
		draw_node(mp, n);
		n = n->nxt;
	}
}