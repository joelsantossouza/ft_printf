/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:30:01 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/18 12:20:02 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>

# define RIGHT_JUSTIFY	1
# define LEFT_JUSTIFY	2
# define FORCE_SIGN		4
# define BLANK_SPACE	8
# define ALTERN_FORM	16
# define ZERO_PAD		32
# define PRECISION		64

# define STDOUT			1

# define OCT			"01234567"
# define DEC			"0123456789"
# define LHEX			"0123456789abcdef"
# define UHEX			"0123456789ABCDEF"

typedef struct s_spec
{
	char	flags;
	char	pad;
	char	prefix[3];
	char	length[3];
	int		width;
	int		precision;
	char	*str;
}	t_spec;

int		convert_int(va_list args, const char *length, char **s);
int		convert_uint(va_list args, const char *length, const char *base, char **s);

int		int_config(va_list args, t_spec *spec);
int		uint_config(va_list args, t_spec *spec, const char *prefix, const char *base);
int		str_config(va_list args, t_spec *spec);
int		chr_config(va_list args, t_spec *spec);
int		ptr_config(va_list args, t_spec *spec);

void	parse_flags(const char *str, t_spec *spec, const char **endptr);
void	parse_width(const char *str, va_list args, t_spec *spec,
			const char **endptr);
void	parse_precision(const char *str, va_list args, t_spec *spec,
				const char **endptr);
void	parse_length(const char *str, t_spec *spec, const char **endptr);
int		parse_spec(const char *str, va_list args, t_spec *spec, const char **endptr);

int		ft_printf(const char *format, ...);

#endif
