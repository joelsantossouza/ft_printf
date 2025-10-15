/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:29:04 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/15 15:38:36 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

const char	*convert_int(va_list args, t_spec *spec)
{
	char	*str;

	if (!ft_strcmp(spec->length, "hh"))
		ft_static_ltoa_base((char) va_arg(args, int), &str, "0123456789");
	else if (!ft_strcmp(spec->length, "ll"))
		ft_static_ltoa_base(va_arg(args, long long), &str, "0123456789");
	else if (*spec->length == 'h')
		ft_static_ltoa_base((short) va_arg(args, int), &str, "0123456789");
	else if (*spec->length == 'l')
		ft_static_ltoa_base(va_arg(args, long), &str, "0123456789");
	else
		ft_static_ltoa_base(va_arg(args, int), &str, "0123456789");
	return ((const char *) str);
}

const char	*convert_uint(va_list args, t_spec *spec, const char *prefix, const char *base)
{
	char	*str;

	(void)prefix;
	if (!ft_strcmp(spec->length, "hh"))
		ft_static_ltoa_base((unsigned char) va_arg(args, int), &str, base);
	else if (!ft_strcmp(spec->length, "ll"))
		ft_static_ltoa_base(va_arg(args, unsigned long long), &str, base);
	else if (*spec->length == 'h')
		ft_static_ltoa_base((unsigned short) va_arg(args, int), &str, base);
	else if (*spec->length == 'l')
		ft_static_ltoa_base(va_arg(args, unsigned long), &str, base);
	else
		ft_static_ltoa_base(va_arg(args, unsigned int), &str, base);
	return ((const char *) str);
}
