/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:07:10 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/21 10:01:11 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

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
