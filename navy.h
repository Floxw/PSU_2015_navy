/*
** navy.h for  in /home/thomas/Documents/epitech/PSU_2015_navy
** 
** Made by Thomas Henon
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Thu Dec 10 15:13:06 2015 Thomas Henon
** Last update Sun Dec 20 11:30:11 2015 Thomas Henon
*/

#ifndef __NAVY_H__
# define __NAVY_H__

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "my.h"

# define FILE_LINE_SIZE 8
# define DEBUG 0

struct			s_pos
{
  char			x;
  char			y;
};

struct			s_buffers
{
  int			nbr_elems;
  char			*buffer;
  char			boat_length;
  struct s_pos		*pos_start;
  struct s_pos		*pos_end;
  struct s_buffers	*next;
};

struct		s_game
{
  unsigned int	enemy_pid;
  char		game_started;
  char		**navy_positions;
  char		**discovered_navy_positions;
} GAME;

# define C_HELLO		0x00
# define S_HELLO		0x01
# define CS_ATTACK		0x02
# define CS_ATTACK_MISS		0x03
# define CS_ATTACK_HIT		0x04
# define CS_WIN			0x05
# define CS_YOUR_TURN		0x06

/*
** main.c
*/
char	usage(int argc, char **argv);
int	main(int argc, char **argv);

/*
** linked_lists.c
*/
struct s_buffers	*new_elem(char *buffer);
char			append_buffer(struct s_buffers **head, char *buffer);
void			free_buffers(struct s_buffers *head);
char			cross_list(struct s_buffers *head);

/*
** game.c
*/
void	on_packet(int packet_type, int packet_datas);
int	read_position();
void	game_loop(int pid, char **navy_positions, char **discovered_navy_positions);
void	game(int enemy_pid, char **navy_positions, char **discovered_navy_positions);

/*
** file.c
*/

int			open_file_or_exit(char *navy_positions_file);
struct s_buffers	*file_get_contents(char *navy_positions_file);

/*
** navy_positions.c
*/
void		malloc_navy_positions(char **navy_positions);
void		swap_navy_pos(struct s_pos **pos1, struct s_pos **pos2);
void		set_navy_positions(struct s_buffers *buffers, char **navy_positions);
void		cross_navy_positions(char **navy_positions);

/*
** parsing.c
*/
void		parsing_error(char *buffer);
struct s_pos	*get_index_position(char *buffer, int *index);
int		parse_positions(struct s_buffers *buffers, int *index);
void		parse_boat_length(struct s_buffers *buffers, int *index);
void		parse_buffers(struct s_buffers *buffers, char **navy_positions);
void		parse_navy_positions(char *navy_positions_file, char ***navy_positions);

/*
** signal.c
*/
void	send_signal(int sig);
void	send_packet(unsigned char packet_type, unsigned char packet_datas);
void	handle_signal(int sig);
void	recv_packet(int signo, siginfo_t *sinfo, void *context);

/*
** util.c
*/
void	my_putstr_error(char *str);
void	my_malloc(void **ptr, int size);

#endif
