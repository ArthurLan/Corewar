/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:02:15 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/04 14:20:55 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	*ft_ustrsub(unsigned char *s, unsigned int start, size_t len)
{
	unsigned char	*str;
	size_t			i;

	if (!(str = (unsigned char*)malloc(sizeof(unsigned char) * (len + 1))))
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

t_env			*init_env(void)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (0);
	env->nb_champs = 0;
	env->head_champs = NULL;
	env->arena = NULL;
	env->opt.is_dump_set = 0;
	env->opt.show_lives = 0;
	env->opt.visu = 0;
	return (env);
}

void			store_option(t_env *env, int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-v"))
			env->opt.visu = 1;
		if (ft_strequ(argv[i], "-l"))
			env->opt.show_lives = 1;
		else if (ft_strequ(argv[i], "-dump"))
		{
			if (i + 1 < argc)
			{
				env->opt.is_dump_set = 1;
				env->opt.dump_value = ft_atoi(argv[i + 1]);
			}
		}
		i++;
	}
	return ;
}

void			free_all(t_env *env)
{
	t_list		*current_champ;
	t_list		*tmp;
	t_champ		*champ;

	if (env->arena)
	{
		free(env->arena->cell);
		free(env->arena);
	}
	current_champ = env->head_champs;
	while (current_champ)
	{
		tmp = current_champ->next;
		champ = (t_champ*)current_champ->content;
		free(champ->header);
		free(champ->content);
		free(current_champ->content);
		free(current_champ);
		current_champ = tmp;
	}
	free(env);
}

int				main(int argc, char **argv)
{
	t_env		*env;

	if (argc == 1)
	{
		ft_putstr_fd("Usage: ./corewar [-dump nbr_cycles] [-l] [-v] ", 2);
		ft_putendl_fd("[[-n number] champion1.cor] ...", 2);
		return (0);
	}
	env = init_env();
	store_option(env, argc, argv);
	if (get_champions(env, argc, argv) == 0)
	{
		if (env->nb_champs == 0)
			ft_putendl_fd("Invalid champion(s), exiting.", 2);
		free_all(env);
		return (0);
	}
	init_arena(env);
	run_cycle(env);
	free_all(env);
	return (0);
}
