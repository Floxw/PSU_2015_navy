/*
** signal.c for  in /home/thomas/Documents/epitech/PSU_2015_navy
** 
** Made by Thomas Henon
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Fri Dec 11 10:26:57 2015 Thomas Henon
** Last update Sun Dec 20 11:17:10 2015 Thomas Henon
*/

#include "navy.h"

void	send_signal(int sig)
{
  if (-1 == kill(GAME.enemy_pid, sig))
    {
      my_putstr("Failed to send signal\n");
      exit(1);
    }
  usleep(8000);
}
void			recv_packet(int signo, siginfo_t *sinfo, void *context)
{
  static char		no_sig = 1;
  static unsigned char	packet_type = 0;
  static unsigned char	packet_datas = 0;
  char			bit;

  GAME.enemy_pid = (int)sinfo->si_pid;
  bit = (SIGUSR1 == signo) ? 1 : 0;
  if (no_sig <= 8)
    packet_type ^= (-bit ^ packet_type) & (1 << (no_sig-1));
  else
    packet_datas ^= (-bit ^ packet_datas) & (1 << (no_sig-1-8));
  if (no_sig == 16)
    {
      usleep(2000);
      on_packet(packet_type, packet_datas);
      no_sig = 1;
    }
  else
    no_sig++;
}

void			handle_signal(int sig)
{
  struct sigaction	act;

  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = recv_packet;
  if (-1 == sigaction(sig, &act, NULL))
    {
      my_putstr("Failed to handle signal\n");
      exit(1);
    }
}

void    send_packet(unsigned char packet_type, unsigned char packet_datas)
{
  int	i;
  char	bit;

  usleep(2000);
  i = 0;
  while (i < 8)
    {
      bit = (packet_type >> i) & 1;
      if (bit)
	send_signal(SIGUSR1);
      else
	send_signal(SIGUSR2);
      i++;
    }
  i = 0;
  while (i < 8)
    {
      bit = (packet_datas >> i) & 1;
      if (bit)
	send_signal(SIGUSR1);
      else
	send_signal(SIGUSR2);
      i++;
    }
}
