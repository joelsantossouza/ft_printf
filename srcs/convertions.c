/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:29:04 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/17 14:15:58 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

int	convert_int(va_list args, const char *length, char **s)
{
	if (!ft_strcmp(length, "hh"))
		return (ft_static_ltoa_base((char) va_arg(args, int), s, DEC));
	else if (!ft_strcmp(length, "ll"))
		return (ft_static_ltoa_base(va_arg(args, long long), s, DEC));
	else if (*length == 'h')
		return (ft_static_ltoa_base((short) va_arg(args, int), s, DEC));
	else if (*length == 'l')
		return (ft_static_ltoa_base(va_arg(args, long), s, DEC));
	return (ft_static_ltoa_base(va_arg(args, int), s, DEC));
}

int	convert_uint(va_list args, const char *length, const char *base, char **s)
{
	//FIND TYPEDEFS TO UNSIGNEDS
	if (!ft_strcmp(length, "hh"))
		return (ft_static_ultoa_base((unsigned char) va_arg(args, int), s, base));
	else if (!ft_strcmp(length, "ll"))
		return (ft_static_ultoa_base(va_arg(args, unsigned long long), s, base));
	else if (*length == 'h')
		return (ft_static_ultoa_base((unsigned short) va_arg(args, int), s, base));
	else if (*length == 'l')
		return (ft_static_ultoa_base(va_arg(args, unsigned long), s, base));
	return (ft_static_ultoa_base(va_arg(args, unsigned int), s, base));
}
