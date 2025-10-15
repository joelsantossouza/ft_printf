/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:28:51 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/15 13:14:23 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"
#include <unistd.h>

static void	add_bytes(ssize_t add, int *store)
{
	if (*store == -1)
		return ;
	if (add >= 0)
		*store += add;
	else
		*store = -1;
}

int	ft_printf(const char *format, ...)
{
	t_spec		spec;
	va_list		args;
	int			nbytes;
	const char	*spec_str;

	nbytes = 0;
	va_start(args, format);
	while (*format && nbytes >= 0)
	{
		if (*format != '%' || *++format == '%')
			add_bytes(ft_putchar_fd(*format, STDOUT), &nbytes);
		else
		{
			ft_memset(&spec, 0, sizeof(t_spec));
			parse_flags(format, &spec, &format);
			parse_width(format, args, &spec, &format);
			parse_precision(format, args, &spec, &format);
			parse_length(format, &spec, &format);
			spec_str = get_spec_str(format, &spec, &format);
			add_bytes(print_spec(spec_str, spec, STDOUT), &nbytes);
		}
	}
	va_end(args);
	return (nbytes);
}
