/*
** parsing.c for  in /home/thomas/Documents/epitech/PSU_2015_navy
** 
** Made by Thomas Henon
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Fri Dec 11 10:20:46 2015 Thomas Henon
** Last update Thu Dec 17 15:45:53 2015 Thomas Henon
*/

#include "navy.h"

struct s_pos		*get_index_position(char *buffer, int *index)
{
  struct s_pos		*pos;

  my_malloc((void*)&pos, sizeof(struct s_pos));
  pos->x = (buffer[*index] - 'A');
  pos->y = (buffer[*index + 1] - '0') - 1;
  return (pos);
}

int		parse_positions(struct s_buffers *buffers, int *index)
{
  char		*buffer;

  buffer = buffers->buffer;
  if (!(buffer[*index] >= 'A' && buffer[*index] <= 'H') ||
      !(buffer[*index + 1] >= '1' && buffer[*index + 1] <= '8'))
    parsing_error(buffer);
  buffers->pos_start = get_index_position(buffer, index);
  (*index)+= 2;
  if (buffer[*index] != ':')
    parsing_error(buffer);
  (*index)+= 1;
  if (!(buffer[*index] >= 'A' && buffer[*index] <= 'H') ||
      !(buffer[*index + 1] >= '1' && buffer[*index + 1] <= '8'))
    parsing_error(buffer);
  buffers->pos_end = get_index_position(buffer, index);
  (*index)+= 2;
}

void		parse_boat_length(struct s_buffers *buffers, int *index)
{
  char		*buffer;

  buffer = buffers->buffer;
  if (!(buffer[*index] >= '0' && buffer[*index] <= '9'))
    parsing_error(buffer);
  buffers->boat_length = my_getnbr(&buffer[*index]);
  while ((buffer[*index] >= '0' && buffer[*index] <= '9'))
    (*index)++;
  if (buffer[*index] != ':')
    parsing_error(buffer);
  (*index)++;
}

void		parse_buffers(struct s_buffers *buffers, char **navy_positions)
{
  int		index;

  while (buffers != 0)
    {
      index = 0;
      if (my_strlen(buffers->buffer) != FILE_LINE_SIZE)
	parsing_error(buffers->buffer);
      parse_boat_length(buffers, &index);
      parse_positions(buffers, &index);
      if (buffers->buffer[index] != '\n')
	parsing_error(buffers->buffer);
      buffers = buffers->next;
    }
}

void			parse_navy_positions(char *navy_positions_file,
					     char ***navy_positions)
{
  struct s_buffers	*buffers;

  buffers = file_get_contents(navy_positions_file);
  my_malloc((void*)*navy_positions, buffers->nbr_elems);
  malloc_navy_positions(*navy_positions);
  parse_buffers(buffers, *navy_positions);
  set_navy_positions(buffers, *navy_positions);
}
