/*
** ls_util.c for  in /home/thomas/Documents/LS
** 
** Made by Thomas Henon
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat Nov 28 16:28:40 2015 Thomas Henon
** Last update Thu Dec 17 15:45:50 2015 Thomas Henon
*/

#include "navy.h"

void	my_putstr_error(char *str)
{
  write(2, str, my_strlen(str));
}

void	my_malloc(void **ptr, int size)
{
  if (!(*ptr = malloc(size)))
    {
      my_putstr_error("Malloc error\n");
      exit(1);
    }
}

void	parsing_error(char *buffer)
{
  my_putstr("Parsing error\nLine: ");
  my_putstr(buffer);
  my_putchar('\n');
  my_put_nbr(my_strlen(buffer));
  my_putchar('\n');
  exit(1);
}
