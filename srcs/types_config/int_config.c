/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:07:10 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/21 10:00:41 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

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
