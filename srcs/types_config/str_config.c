/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:07:10 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/21 10:17:30 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	str_config(va_list args, t_spec *spec)
{
	const int	precision = spec->precision;

	spec->pad = ' ';
	spec->precision = 0;
	spec->str = va_arg(args, char *);
	if (!spec->str)
	{
		if ((spec->flags & PRECISION) && precision < 6)
			return (0);
		spec->str = "(null)";
		return (6);
	}
	if (spec->flags & PRECISION)
		return (ft_strnlen(spec->str, precision));
	return (ft_strlen(spec->str));
}
