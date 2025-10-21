/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:07:10 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/21 09:58:25 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

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
