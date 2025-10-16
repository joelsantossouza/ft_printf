/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:29:12 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/16 10:57:25 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"
#include <stdarg.h>

void	parse_flags(const char *str, t_spec *spec, const char **endptr)
{
	*endptr = str;
	while (1)
	{
		if (**endptr == '-')
			spec->flags |= LEFT_JUSTIFY;
		else if (**endptr == '+')
			spec->flags |= FORCE_SIGN;
		else if (**endptr == ' ')
			spec->flags |= BLANK_SPACE;
		else if (**endptr == '#')
			spec->flags |= ALTERN_FORM;
		else if (**endptr == '0')
			spec->flags |= ZEROES_PAD;
		else
			break ;
		(*endptr)++;
	}
	if (!(spec->flags & LEFT_JUSTIFY))
		spec->flags |= RIGHT_JUSTIFY;
}

void	parse_width(const char *str, va_list args, t_spec *spec, const char **endptr)
{
	*endptr = str;
	if (**endptr == '*')
	{
		spec->width = va_arg(args, int);
		(*endptr)++;
	}
	else
		spec->width = ft_atol_base(*endptr, (char **) endptr, "0123456789");
}

void	parse_precision(const char *str, va_list args, t_spec *spec, const char **endptr)
{
	*endptr = str;
	if (**endptr == '.')
	{
		spec->flags |= PRECISION;
		if (*++(*endptr) == '*')
		{
			spec->precision = va_arg(args, int);
			(*endptr)++;
		}
		else
			spec->precision = ft_atol_base(*endptr, (char **) endptr, "0123456789");
	}
}

void	parse_length(const char *str, t_spec *spec, const char **endptr)
{
	*endptr = str;
	if (!ft_strncmp(*endptr, "hh", 2) || !ft_strncmp(*endptr, "ll", 2))
		*endptr += ft_strlcpy(spec->length, *endptr, sizeof(spec->length));
	else if (ft_strchr("hl", **endptr))
		*endptr += ft_strlcpy(spec->length, *endptr, 2);
}

const char	*get_spec_str(const char *str, va_list args, t_spec *spec, const char **endptr)
{
	*endptr = str + 1;
	if (*str == 'd' || *str == 'i')
		return (convert_int(args, spec));
	else if (*str == 'u')
		return (convert_uint(args, spec, "", "0123456789"));
	else if (*str == 'o')
		return (convert_uint(args, spec, "0", "01234567"));
	else if (*str == 'x')
		return (convert_uint(args, spec, "0x", "0123456789abcdef"));
	else if (*str == 'X')
		return (convert_uint(args, spec, "0X", "0123456789ABCDEF"));
	return (0);
}
