/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:28:51 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/16 22:45:31 by joesanto         ###   ########.fr       */
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

static ssize_t	padding(const char pad, int times, int fd)
{
	size_t	nbytes;
	ssize_t	ret;

	nbytes = 0;
	while (times-- > 0)
	{
		ret = ft_putchar_fd(pad, fd);
		if (ret < 0)
			return (-1);
		nbytes += ret;
	}
	return (nbytes);
}

static int	print_spec(const char *str, t_spec spec, int fd)
{
	const int	len = ft_strnlen(str, spec.precision) + (spec.flags & IS_CHAR);
	const int	prec_size = ft_max(0, spec.precision - len);
	const int	maxlen = ft_strlen(spec.prefix) + len + prec_size;
	char		width_pad;
	int			nbytes;

	nbytes = 0;
	width_pad = spec.pad;
	if (spec.flags & PRECISION)
		width_pad = ' ';
	if (width_pad != ' ')
		add_bytes(ft_putstr_fd(spec.prefix, fd), &nbytes);
	if (spec.flags & RIGHT_JUSTIFY && nbytes >= 0)
		add_bytes(padding(width_pad, spec.width - maxlen, fd), &nbytes);
	if (width_pad == ' ' && nbytes >= 0)
		add_bytes(ft_putstr_fd(spec.prefix, fd), &nbytes);
	if (spec.flags & PRECISION && nbytes >= 0)
		add_bytes(padding(spec.pad, prec_size, fd), &nbytes);
	if (nbytes >= 0)
		add_bytes(write(fd, str, len), &nbytes);
	if (spec.flags & LEFT_JUSTIFY && nbytes >= 0)
		add_bytes(padding(width_pad, spec.width - maxlen, fd), &nbytes);
	return (nbytes);
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
			add_bytes(ft_putchar_fd(*format++, STDOUT), &nbytes);
		else
		{
			ft_memset(&spec, 0, sizeof(t_spec));
			parse_flags(format, &spec, &format);
			parse_width(format, args, &spec, &format);
			parse_precision(format, args, &spec, &format);
			parse_length(format, &spec, &format);
			spec_str = get_spec_str(format, args, &spec, &format);
			add_bytes(print_spec(spec_str, spec, STDOUT), &nbytes);
		}
	}
	va_end(args);
	return (nbytes);
}

int	ft_fprintf(int fd, const char *format, ...)
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
			add_bytes(ft_putchar_fd(*format++, fd), &nbytes);
		else
		{
			ft_memset(&spec, 0, sizeof(t_spec));
			parse_flags(format, &spec, &format);
			parse_width(format, args, &spec, &format);
			parse_precision(format, args, &spec, &format);
			parse_length(format, &spec, &format);
			spec_str = get_spec_str(format, args, &spec, &format);
			add_bytes(print_spec(spec_str, spec, fd), &nbytes);
		}
	}
	va_end(args);
	return (nbytes);
}
