/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:29:12 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/15 12:13:27 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
