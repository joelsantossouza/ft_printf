/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:29:04 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/15 16:29:01 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

static ssize_t	temp_max(ssize_t n1, ssize_t n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

const char	*convert_int(va_list args, t_spec *spec)
{
	char	*str;
	int		len;

	if (spec->flags & FORCE_SIGN)
		ft_strlcpy(spec->prefix, "+", sizeof(spec->prefix));
	else if (spec->flags & BLANK_SPACE)
		ft_strlcpy(spec->prefix, " ", sizeof(spec->prefix));
	spec->pad = ' ';
	if (spec->flags & ZEROES_PAD && !(spec->flags & LEFT_JUSTIFY))
		spec->pad = '0';
	if (!ft_strcmp(spec->length, "hh"))
		len = ft_static_ltoa_base((char) va_arg(args, int), &str, "0123456789");
	else if (!ft_strcmp(spec->length, "ll"))
		len = ft_static_ltoa_base(va_arg(args, long long), &str, "0123456789");
	else if (*spec->length == 'h')
		len = ft_static_ltoa_base((short) va_arg(args, int), &str, "0123456789");
	else if (*spec->length == 'l')
		len = ft_static_ltoa_base(va_arg(args, long), &str, "0123456789");
	else
		len = ft_static_ltoa_base(va_arg(args, int), &str, "0123456789");
	spec->precision = temp_max(len, spec->precision);
	return ((const char *) str);
}

const char	*convert_uint(va_list args, t_spec *spec, const char *prefix, const char *base)
{
	char	*str;
	int		len;

	if (spec->flags & ALTERN_FORM)
		ft_strlcpy(spec->prefix, prefix, sizeof(spec->prefix));
	spec->pad = ' ';
	if (spec->flags & ZEROES_PAD && !(spec->flags & LEFT_JUSTIFY))
		spec->pad = '0';
	if (!ft_strcmp(spec->length, "hh"))
		len = ft_static_ltoa_base((unsigned char) va_arg(args, int), &str, base);
	else if (!ft_strcmp(spec->length, "ll"))
		len = ft_static_ltoa_base(va_arg(args, unsigned long long), &str, base);
	else if (*spec->length == 'h')
		len = ft_static_ltoa_base((unsigned short) va_arg(args, int), &str, base);
	else if (*spec->length == 'l')
		len = ft_static_ltoa_base(va_arg(args, unsigned long), &str, base);
	else
		len = ft_static_ltoa_base(va_arg(args, unsigned int), &str, base);
	spec->precision = temp_max(len, spec->precision);
	return ((const char *) str);
}
