/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:28:51 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/15 09:23:08 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"
#include <stdarg.h>
#include <unistd.h>

int	ft_printf(const char *format, ...)
{
	t_spec		spec;
	va_list		args;
	int			nbytes;

	nbytes = 0;
	va_start(args, format);
	while (*format && nbytes >= 0)
	{
		if (*format != '%' || *++format == '%')

	}
	va_end(args);
	return (nbytes);
}
