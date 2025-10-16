/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:29:04 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/16 14:07:12 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

const char	*convert_int(va_list args, t_spec *spec)
{
	char	*str;
	int		len;

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
	if (spec->flags & FORCE_SIGN)
		ft_strlcpy(spec->prefix, "+", sizeof(spec->prefix));
	else if (spec->flags & BLANK_SPACE)
		ft_strlcpy(spec->prefix, " ", sizeof(spec->prefix));
	spec->pad = ' ';
	if (((spec->flags & ZEROES_PAD) && (spec->flags & RIGHT_JUSTIFY)) || (spec->flags & PRECISION))
		spec->pad = '0';
	spec->precision = ft_max(len, spec->precision);
	return ((const char *) str);
}

const char	*convert_uint(va_list args, t_spec *spec, const char *prefix, const char *base)
{
	char	*str;
	int		len;

	if (!ft_strcmp(spec->length, "hh"))
		len = ft_static_ultoa_base((unsigned char) va_arg(args, int), &str, base);
	else if (!ft_strcmp(spec->length, "ll"))
		len = ft_static_ultoa_base(va_arg(args, unsigned long long), &str, base);
	else if (*spec->length == 'h')
		len = ft_static_ultoa_base((unsigned short) va_arg(args, int), &str, base);
	else if (*spec->length == 'l')
		len = ft_static_ultoa_base(va_arg(args, unsigned long), &str, base);
	else
		len = ft_static_ultoa_base(va_arg(args, unsigned int), &str, base);
	if (spec->flags & ALTERN_FORM)
		ft_strlcpy(spec->prefix, prefix, sizeof(spec->prefix));
	spec->pad = ' ';
	if (((spec->flags & ZEROES_PAD) && (spec->flags & RIGHT_JUSTIFY)) || (spec->flags & PRECISION))
		spec->pad = '0';
	spec->precision = ft_max(len, spec->precision);
	return ((const char *) str);
}

const char	*convert_str(va_list args, t_spec *spec)
{
	const char	*str = va_arg(args, char *);
	const int	len = ft_strlen(str);

	spec->pad = ' ';
	if (!(spec->flags & PRECISION) || spec->precision > len)
		spec->precision = len;
	return (str);
}

const char	*convert_chr(va_list args, t_spec *spec)
{
	const char	*str = va_arg(args, char *);

	spec->pad = ' ';
	spec->precision = 1;
	return (str);
}

const char	*convert_ptr(va_list args, t_spec *spec)
{
	char	*str;

	spec->pad = ' ';
	spec->precision = ft_static_ultoa_base(va_arg(args, size_t), &str, "0123456789abcdef");
	ft_strlcpy(spec->prefix, "0x", sizeof(spec->prefix));
	return (str);
}
