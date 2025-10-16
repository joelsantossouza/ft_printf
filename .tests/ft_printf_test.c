/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:31:12 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/16 20:06:49 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../includes/libft.h"
#include <atf-c.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"

const char	*tests_titles[] = {
	"Empty Strings",
	"No Format Strings",
	"Format %",
	"Format \'c\'",
	"Format \'s\'",
	"Format \'d\' and \'i\'",
	"Format \'u\'",
	"Format \'x\'",
	"Format \'X\'",
	"Format \'o\'",
	"Format \'p\'",
};

#define BUF_SIZE 4026
int	filecmp(int fd1, int fd2)
{
	char	buf1[BUF_SIZE];
	char	buf2[BUF_SIZE];

	while (read(fd1, buf1, BUF_SIZE) > 0 && read(fd2, buf2, BUF_SIZE) > 0)
		if (ft_strncmp(buf1, buf2, BUF_SIZE))
			break ;
	return (ft_strncmp(buf1, buf2, BUF_SIZE));
}

void	putfile(int fd)
{
	char	buf[BUF_SIZE];
	ssize_t	bytes;

	while ((bytes = read(fd, buf, BUF_SIZE)) > 0)
		printf("%.*s", (int) bytes, buf);
	printf("\n");
}

void	test(char *str, ...)
{
	va_list	args;
	int		fd;
	FILE	*file;
	char	template[] = "/home/joel/coding/exercises/printf/final/.tests/XXXXXX";
	char	*color;

	fd = mkstemp(template);
	if (fd < 0)
		return ;
	file = tmpfile();
	if (!file)
	{
		unlink(template);
		return ;
	}
	va_start(args, str);

	fprintf(file, str, args);
	ft_fprintf(fd, str, args);
	
	fseek(file, 0, SEEK_SET);
	lseek(fd, 0, SEEK_SET);
	color = !filecmp(fileno(file), fd) ? GREEN : RED;
	printf("%s", color);
	printf("Input:   \t%s\n", str);
	printf("Expected:\t"); putfile(fileno(file));
	printf("Output:  \t"); putfile(fd);
	printf("%s", RESET);

	printf("\n----------\n");
	ATF_CHECK(!filecmp(fileno(file), fd));
	va_end(args);
	unlink(template);
}

// TEST 00 --> EMPTY STRINGS
ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing ft_printf");
}
ATF_TC_BODY(test00, tc)
{
	printf("\n<test00> %s\n", tests_titles[0]);
	test("");
	test("", "42");
	test("", 42);
	test("", (void*) 0);
}

// TEST PROGRAM
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);

	return (atf_no_error());
}
