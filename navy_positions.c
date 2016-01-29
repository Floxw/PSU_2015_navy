/*
** navy_positions.c for  in /home/thomas/Documents/epitech/PSU_2015_navy
** 
** Made by Thomas Henon
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Fri Dec 11 10:23:48 2015 Thomas Henon
** Last update Sun Dec 20 22:02:55 2015 Thomas Henon
*/

#include "navy.h"

void	malloc_navy_positions(char **navy_positions)
{
  int	i;
  int	i2;

  i = 0;
  while (i < 8)
    {
      my_malloc((void*)&navy_positions[i], sizeof(char) * 8);
      i2 = 0;
      while (i2 < 8)
	navy_positions[i][i2++] = '.';
      i++;
    }
}

void		swap_navy_pos(struct s_pos **pos1, struct s_pos **pos2)
{
  struct s_pos	*tmp;

  tmp = *pos1;
  if ((*pos1)->x > (*pos2)->x)
    {
      *pos1 = *pos2;
      *pos2 = tmp;
    }
  else if ((*pos1)->x == (*pos2)->x &&
	   (*pos1)->y > (*pos2)->y)
    {
      *pos1 = *pos2;
      *pos2 = tmp;
    }
}

void		set_navy_positions(struct s_buffers *buffers,
				   char **navy_positions)
{
  struct s_pos	*tmp;

  my_malloc((void*)&tmp, sizeof(struct s_pos));
  while (buffers != 0)
    {
      swap_navy_pos(&(buffers->pos_start), &(buffers->pos_end));
      tmp->x = buffers->pos_start->x;
      tmp->y = buffers->pos_start->y;
      while ((tmp->x <= buffers->pos_end->x))
	navy_positions[tmp->y][tmp->x++] = buffers->boat_length + '0';
      while (tmp->y <= buffers->pos_end->y)
	navy_positions[tmp->y++][tmp->x-1] = buffers->boat_length + '0';
      buffers = buffers->next;
    }
}

void	cross_navy_positions(char **navy_positions)
{
  int	i;
  int	i2;

  i = 0;
  my_putstr(" |A B C D E F G H\n");
  my_putstr("-+---------------\n");
  while (i < 8)
    {
      i2 = 0;
      my_put_nbr(i + 1);
      my_putchar('|');
      while (i2 < 8)
	{
	  my_putchar(navy_positions[i][i2]);
	  my_putchar(' ');
	  i2++;
	}
      my_putchar('\n');
      i++;
    }
}

void	display_maps()
{
  my_putstr("my navy:\n");
  cross_navy_positions(GAME.navy_positions);
  my_putstr("\nenemy navy: \n");
  cross_navy_positions(GAME.discovered_navy_positions);
  my_putstr("\n");
}
