/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:11:06 by lde-cast          #+#    #+#             */
/*   Updated: 2024/01/11 15:19:04 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_status	t_status;
typedef struct s_timer	t_timer;
typedef enum e_hand		t_hand;
typedef struct s_philo	t_philo;
typedef struct s_action	t_action;
typedef struct s_life	t_life;

extern unsigned long	pl_atoul_base(char *str, unsigned char base);
extern int				index_get(int n, int max);

enum e_status
{
	Off,
	On
};

struct s_timer
{
	_Atomic long		begin;
	_Atomic long		interval;
};

extern long				time_now(void);
extern void				timer_start(t_timer *set, unsigned long interval);
extern void				timer_set(t_timer *set);
extern t_status			timer_get(t_timer *set);

enum e_hand
{
	LEFT_HAND,
	RIGHT_HAND
};

struct s_philo
{
	pthread_t		core;
	int				id;
	int				has_eaten;
	t_timer			wait[3];
	t_timer			die[1];
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
};

extern t_status			philo_fork_take(t_philo *set);
extern void				philo_fork_release(t_philo *set);
extern t_status			philo_eat(t_philo *set);
extern void				philo_set(t_philo *set, int id, t_action *action);
extern void				philo_sleep(t_philo *man);
extern void				philo_think(t_philo *man);
extern void				philo_message(t_philo *set, char *msg);
extern void				philo_die(t_philo *set, char *msg);
extern t_status			philo_satiated(t_philo *set);

struct s_action
{
	long	die;
	long	eat;
	long	sleep;
	int		eat_max;
};

struct s_life
{
	t_philo				*philo;
	_Atomic int			philo_max;
	t_action			action[1];
	_Atomic t_status	alive;
	pthread_t			leader;
	pthread_mutex_t		time_to_die;
	pthread_mutex_t		message;
	pthread_mutex_t		satiated;
	pthread_mutex_t		full;
	pthread_mutex_t		*fork;
	_Atomic long		begin;
	_Atomic int			max;
};

extern t_life			*life_get(void);
extern void				life_set(t_life *set);
extern void				life_is_going(t_life *set, char **argv);
extern void				*life_action(void *data);
extern void				*main_loop(void *data);
extern long				life_time(void);
extern t_status			life_is_over(void);
extern void				life_pop(t_life *set);

#endif