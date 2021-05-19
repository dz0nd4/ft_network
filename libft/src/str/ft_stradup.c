/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_stradup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/11 14:25:36 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:16 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char		**ft_stradup(char **array)
{
	char	**stra;
	int		i;

	stra = NULL;
	i = -1;
	if (array)
	{
		if (!(stra = (char **)malloc(sizeof(char *) * ft_stralen(array))))
			return (NULL);
		while (array[++i])
			stra[i] = ft_strdup(array[i]);
		stra[i] = NULL;
	}
	return (stra);
}
