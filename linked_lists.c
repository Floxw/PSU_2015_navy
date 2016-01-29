/*
** linked_lists.c for  in /home/thomas/Documents/epitech/PSU_2015_navy
** 
** Made by Thomas Henon
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Thu Dec 10 15:29:55 2015 Thomas Henon
** Last update Thu Dec 17 15:41:03 2015 Thomas Henon
*/

#include "navy.h"

struct s_buffers	*new_elem(char *buffer)
{
  struct s_buffers	*elem;

  my_malloc((void*)&elem, sizeof(struct s_buffers));
  elem->buffer = buffer;
  elem->next = 0;
  elem->nbr_elems = 1;
  return (elem);
}

char			append_buffer(struct s_buffers **head, char *buffer)
{
  struct s_buffers	*tmp;

  if (*head == 0)
    {
      *head = new_elem(buffer);
      return (1);
    }
  tmp = *head;
  while (tmp->next != 0)
    tmp = tmp->next;
  tmp->next = new_elem(buffer);
  (*head)->nbr_elems++;
  return (1);
}

void			free_buffers(struct s_buffers *head)
{
  struct s_buffers	*tmp;

  while (head != 0)
    {
      tmp = head;
      head = head->next;
      free(tmp);
    }
}
