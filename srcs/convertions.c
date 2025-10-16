/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:29:04 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/16 15:47:35 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

const char	*convert_int(va_list args, t_spec *spec)
{
	char	*s;
	int		len;

	if (!ft_strcmp(spec->length, "hh"))
		len = ft_static_ltoa_base((char) va_arg(args, int), &s, "0123456789");
	else if (!ft_strcmp(spec->length, "ll"))
		len = ft_static_ltoa_base(va_arg(args, long long), &s, "0123456789");
	else if (*spec->length == 'h')
		len = ft_static_ltoa_base((short) va_arg(args, int), &s, "0123456789");
	else if (*spec->length == 'l')
		len = ft_static_ltoa_base(va_arg(args, long), &s, "0123456789");
	else
		len = ft_static_ltoa_base(va_arg(args, int), &s, "0123456789");
	if (spec->flags & FORCE_SIGN)
		ft_strlcpy(spec->prefix, "+", sizeof(spec->prefix));
	else if (spec->flags & BLANK_SPACE)
		ft_strlcpy(spec->prefix, " ", sizeof(spec->prefix));
	spec->pad = ' ';
	if (((spec->flags & ZEROES_PAD) && (spec->flags & RIGHT_JUSTIFY)) || (spec->flags & PRECISION))
		spec->pad = '0';
	spec->precision = ft_max(len, spec->precision);
	return ((const char *) s);
}

const char	*convert_uint(va_list args, t_spec *spec, const char *prefix, const char *base)
{
	char	*s;
	int		len;

	if (!ft_strcmp(spec->length, "hh"))
		len = ft_static_ultoa_base((unsigned char) va_arg(args, int), &s, base);
	else if (!ft_strcmp(spec->length, "ll"))
		len = ft_static_ultoa_base(va_arg(args, unsigned long long), &s, base);
	else if (*spec->length == 'h')
		len = ft_static_ultoa_base((unsigned short) va_arg(args, int), &s, base);
	else if (*spec->length == 'l')
		len = ft_static_ultoa_base(va_arg(args, unsigned long), &s, base);
	else
		len = ft_static_ultoa_base(va_arg(args, unsigned int), &s, base);
	if (spec->flags & ALTERN_FORM)
		ft_strlcpy(spec->prefix, prefix, sizeof(spec->prefix));
	spec->pad = ' ';
	if (((spec->flags & ZEROES_PAD) && (spec->flags & RIGHT_JUSTIFY)) || (spec->flags & PRECISION))
		spec->pad = '0';
	spec->precision = ft_max(len, spec->precision);
	return ((const char *) s);
}

const char	*convert_str(va_list args, t_spec *spec)
{
	const char	*s = va_arg(args, char *);
	const int	len = ft_strlen(s);

	spec->pad = ' ';
	if (!(spec->flags & PRECISION) || spec->precision > len)
		spec->precision = len;
	return (s);
}

const char	*convert_chr(va_list args, t_spec *spec)
{
	const char	*s = va_arg(args, char *);

	spec->pad = ' ';
	spec->precision = 1;
	return (s);
}

const char	*convert_ptr(va_list args, t_spec *spec)
{
	char	*s;

	spec->pad = ' ';
	spec->precision = ft_static_ultoa_base(va_arg(args, size_t), &s, "0123456789abcdef");
	ft_strlcpy(spec->prefix, "0x", sizeof(spec->prefix));
	return (s);
}
