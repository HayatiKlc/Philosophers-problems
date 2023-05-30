/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkilic <hkilic@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:57:26 by hkilic            #+#    #+#             */
/*   Updated: 2022/12/30 18:21:44 by hkilic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc == 6 || argc == 5)
	{
		if (init_all(&sim, argv) == 1 || init_all(&sim, argv) == 2)
		{
			return (0);
		}
		if (sim_start(&sim) == 1)
			return (0);
	}
	else
		if (print_error("WRONG ARGUMENT !") == 1)
			return (0);
}
