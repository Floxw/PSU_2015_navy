/*
** game.c for  in /home/thomas/Documents/epitech/PSU_2015_navy
** 
** Made by Thomas Henon
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat Dec 12 16:36:42 2015 Thomas Henon
** Last update Sun Dec 20 11:22:35 2015 Thomas Henon
*/

#include "navy.h"

void	player_turn()
{
  int	attack_pos;

  send_packet(CS_YOUR_TURN, 0);
  attack_pos = -1;
  display_maps();
  while (attack_pos == -1)
    {
      my_putstr("attack : ");
      if (-1 == (attack_pos = read_position()))
	my_putstr("\nwrong position\n\n");
    }
  send_packet(CS_ATTACK, attack_pos);
}

char	test_win()
{
  int	x;
  int	y;

  y = 0;
  while (y < 8)
    {
      x = 0;
      while (x < 8)
	{
	  if (GAME.navy_positions[y][x] >= '1' &&
	      GAME.navy_positions[y][x] <= '8')
	    return (0);
	  x++;
	}
      y++;
    }
  display_maps();
  my_putstr("Enemy won\n");
  send_packet(CS_WIN, 0);
  exit(1);
}

void	on_packet(int packet_type, int packet_datas)
{
  if (packet_type == C_HELLO)
    on_client_hello(packet_datas);
  if (packet_type == S_HELLO)
    GAME.game_started = 1;
  if (packet_type == CS_ATTACK)
    on_attack(packet_datas);
  if (packet_type == CS_ATTACK_HIT)
    on_attack_hit(packet_datas, 1);
  if (packet_type == CS_ATTACK_MISS)
    on_attack_miss(packet_datas, 1);
  if (packet_type == CS_WIN)
    on_win(packet_datas);
  if (packet_type == CS_YOUR_TURN)
    my_putstr("waiting for enemy's attack...\n\n");
}

int		read_position()
{
  char		buff[3];

  read(0, &buff, 3);
  if (!(buff[0] >= 'A' && buff[0] <= 'H') ||
      !(buff[1] >= '0' && buff[1] <= '8'))
    return (-1);
  else
    return (((buff[1]-1-'0')*8)+(buff[0]-'A'));
}

void	game(int enemy_pid, char **navy_positions,
	     char **discovered_navy_positions)
{
  GAME.game_started = 0;
  GAME.navy_positions = navy_positions;
  GAME.discovered_navy_positions = discovered_navy_positions;
  GAME.enemy_pid = enemy_pid;
  my_putstr("my_pid: ");
  my_put_nbr((int)getpid());
  my_putstr("\n\n");
  if (enemy_pid)
    send_packet(C_HELLO, 0);
  else
    my_putstr("waiting for enemy...\n\n");
  while (1)
    pause();
}
