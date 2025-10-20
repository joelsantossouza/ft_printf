/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:07:10 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/20 22:44:46 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	int_config(va_list args, t_spec *spec)
{
	const char	zero_pad = (spec->flags & F_ZERO) && !(spec->flags & F_MINUS);
	int			len;

	len = convert_int(args, spec->length, &spec->str);
	if (*spec->str == '-')
	{
		len--;
		spec->str++;
		ft_strlcpy(spec->prefix, "-", sizeof(spec->prefix));
	}
	else if (spec->flags & F_PLUS)
		ft_strlcpy(spec->prefix, "+", sizeof(spec->prefix));
	else if (spec->flags & F_SPACE)
		ft_strlcpy(spec->prefix, " ", sizeof(spec->prefix));
	spec->pad = ' ';
	if ((spec->flags & PRECISION) && !spec->precision && *spec->str == '0')
		return (0);
	if (zero_pad || (spec->flags & PRECISION))
		spec->pad = '0';
	return (len);
}

int	uint_config(va_list args, t_spec *spec, const char *prefix,
		const char *base)
{
	const char	zero_pad = (spec->flags & F_ZERO) && !(spec->flags & F_MINUS);
	int			len;

	len = convert_uint(args, spec->length, base, &spec->str);
	if ((spec->flags & F_HASH) && *spec->str != '0')
		ft_strlcpy(spec->prefix, prefix, sizeof(spec->prefix));
	spec->pad = ' ';
	if ((spec->flags & PRECISION) && !spec->precision && *spec->str == '0')
		return (0);
	if (zero_pad || (spec->flags & PRECISION))
		spec->pad = '0';
	return (len);
}

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

int	chr_config(va_list args, t_spec *spec)
{
	static char	chr[2];

	spec->pad = ' ';
	*chr = va_arg(args, int);
	spec->str = chr;
	return (1);
}

int	ptr_config(va_list args, t_spec *spec)
{
	const char	zero_pad = (spec->flags & F_ZERO) && !(spec->flags & F_MINUS);

	spec->pad = ' ';
	spec->str = va_arg(args, void *);
	if (!spec->str)
	{
		spec->precision = 0;
		spec->str = "(nil)";
		return (5);
	}
	ft_strlcpy(spec->prefix, "0x", sizeof(spec->prefix));
	if (zero_pad || (spec->flags & PRECISION))
		spec->pad = '0';
	return (ft_static_ultoa_base((size_t) spec->str, &spec->str, LHEX));
}
