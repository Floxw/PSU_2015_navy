/*
** main.c for  in /home/thomas/Documents/epitech/PSU_2015_navy
** 
** Made by Thomas Henon
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Thu Dec 10 14:57:13 2015 Thomas Henon
** Last update Sun Dec 20 00:15:07 2015 Thomas Henon
*/

#include "navy.h"

char	usage(int argc, char **argv)
{
  if (argc < 2 || argc > 3)
    {
      my_putstr("Usage: ./navy [enemy_pid] navy_positions.txt\n");
      return (0);
    }
  return (1);
}

int	main(int argc, char **argv)
{
  int	enemy_pid;
  char	*navy_positions_file;
  char	**discovered_navy_positions;
  char	**navy_positions;

  if (!usage(argc, argv))
    return (1);
  enemy_pid = (argc == 3) ? my_getnbr(argv[1]) : 0;
  navy_positions_file = (argc == 3) ? argv[2] : argv[1];
  parse_navy_positions(navy_positions_file, &navy_positions);
  my_malloc((void*)&discovered_navy_positions,
	    sizeof(*discovered_navy_positions)*8);
  malloc_navy_positions(discovered_navy_positions);
  handle_signal(SIGUSR1);
  handle_signal(SIGUSR2);
  game(enemy_pid, navy_positions, discovered_navy_positions);
  return (0);
}
