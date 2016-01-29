/*
** file.c for  in /home/thomas/Documents/epitech/PSU_2015_navy
** 
** Made by Thomas Henon
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Fri Dec 11 10:19:23 2015 Thomas Henon
** Last update Tue Dec 15 15:26:06 2015 Thomas Henon
*/

#include "navy.h"

int	open_file_or_exit(char *navy_positions_file)
{
  int	fd;

  if (-1 == (fd = open(navy_positions_file, O_RDONLY)))
    {
      my_putstr("File doesn't exist !\n");
      exit(1);
    }
  return (fd);
}

struct s_buffers	*file_get_contents(char *navy_positions_file)
{
  int			fd;
  char			*buffer;
  struct s_buffers	*buffers;
  int			readv;

  buffers = 0;
  fd = open_file_or_exit(navy_positions_file);
  my_malloc((void*)&buffer, FILE_LINE_SIZE+1);
  while ((readv = read(fd, buffer, FILE_LINE_SIZE))
	 && readv != 0 && readv != -1)
    {
      append_buffer(&buffers, buffer);
      my_malloc((void*)&buffer, FILE_LINE_SIZE+1);
    }
  if (readv == -1)
    {
      my_putstr("Read error\n");
      close(fd);
      exit(1);
    }
  return (buffers);
}
