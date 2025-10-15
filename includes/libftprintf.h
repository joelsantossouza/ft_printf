/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:30:01 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/15 12:11:42 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

#define LEFT_JUSTIFY	(1 << 0)
#define FORCE_SIGN		(1 << 1)
#define BLANK_SPACE		(1 << 2)
#define ALTERN_FORM		(1 << 3)
#define ZEROES_PAD		(1 << 4)

typedef struct s_spec
{
	char	flags;
	char	pad;
	char	prefix[3];
	char	length[3];
	int		width;
	int		precision;
}	t_spec;

void	parse_flags(const char *str, t_spec *spec, const char **endptr);
void	parse_width(const char *str, va_list args, t_spec *spec, const char **endptr);

#endif
