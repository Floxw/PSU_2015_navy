/*
** packets.c for  in /home/thomas/Documents/epitech/PSU_2015_navy
** 
** Made by Thomas Henon
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Thu Dec 17 15:33:24 2015 Thomas Henon
** Last update Sun Dec 20 11:23:30 2015 Thomas Henon
*/

#include "navy.h"

void	on_attack_hit(int pos, char from_packet)
{
  int	x;
  int	y;

  y = pos / 8;
  x = pos % 8;
  if (from_packet)
    GAME.discovered_navy_positions[y][x] = 'x';
  my_putstr("\nresult: ");
  my_putchar('A' + x);
  my_putchar('1' + y);
  my_putstr(":hit\n\n");
}

void	on_attack_miss(int pos, char from_packet)
{
  int	x;
  int	y;

  y = pos / 8;
  x = pos % 8;
  if (from_packet)
    GAME.discovered_navy_positions[y][x] = 'o';
  my_putstr("\nresult: ");
  my_putchar('A' + x);
  my_putchar('1' + y);
  my_putstr(":missed\n\n");
}

void	on_client_hello(int packet_datas)
{
  GAME.game_started = 1;
  send_packet(S_HELLO, 0);
  my_putstr("enemy connected\n\n");
  player_turn();
}

void	on_win(int packet_datas)
{
  display_maps();
  my_putstr("I won\n");
  exit(0);
}

void	on_attack(int pos)
{
  int	x;
  int	y;

  y = pos / 8;
  x = pos % 8;
  if (GAME.navy_positions[y][x] >= '1' && GAME.navy_positions[y][x] <= '8')
    {
      GAME.navy_positions[y][x] = 'x';
      on_attack_hit(pos, 0);
      send_packet(CS_ATTACK_HIT, pos);
    }
  else
    {
      if (GAME.navy_positions[y][x] != 'x')
	GAME.navy_positions[y][x] = 'o';
      on_attack_miss(pos, 0);
      send_packet(CS_ATTACK_MISS, pos);
    }
  test_win();
  player_turn();
}
