/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:28:51 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/15 15:51:03 by joesanto         ###   ########.fr       */
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

static ssize_t	repeat_chr(const char chr, int times, int fd)
{
	size_t	nbytes;
	ssize_t	ret;

	nbytes = 0;
	while (times-- > 0)
	{
		ret = ft_putchar_fd(chr, fd);
		if (ret < 0)
			return (-1);
		nbytes += ret;
	}
	return (nbytes);
}

static void	print_spec(const char *str, t_spec spec, int *nbytes, int fd)
{
	const int	len = ft_strlen(str);

	if (spec.flags & LEFT_JUSTIFY)
	{
		add_bytes(ft_putstr_fd(spec.prefix, fd), nbytes);
		add_bytes(write(fd, str, len), nbytes);
		add_bytes(repeat_chr(spec.pad, spec.width - len, fd), nbytes);
	}
	else
	{
		if (spec.pad == '0')
		{
			add_bytes(ft_putstr_fd(spec.prefix, fd), nbytes);
			add_bytes(repeat_chr(spec.pad, spec.width - len, fd), nbytes);
			add_bytes(write(fd, str, len), nbytes);
		}
		else
		{
			add_bytes(repeat_chr(spec.pad, spec.width - len, fd), nbytes);
			add_bytes(ft_putstr_fd(spec.prefix, fd), nbytes);
			add_bytes(write(fd, str, len), nbytes);
		}
	}
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
			print_spec(spec_str, spec, &nbytes, STDOUT);
		}
	}
	va_end(args);
	return (nbytes);
}
