/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:31:12 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/20 23:00:59 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include "../libs/libft/libft.h"
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
	"No Existing Format",
	"Format %",
	"Format \'c\'",
	"Format \'s\'",
	"Format \'d\' and \'i\'",
	"Format \'u\', \'x\', \'X\', \'o\'",
	"Format \'p\'",
};

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

static int	ft_putspec_fd(t_spec spec, int len, int fd)
{
	const int	prec_pad_len = ft_max(0, spec.precision - len);
	const int	maxlen = ft_strlen(spec.prefix) + len + prec_pad_len;
	char		width_pad;
	int			nbytes;

	nbytes = 0;
	width_pad = spec.pad;
	if (spec.flags & PRECISION)
		width_pad = ' ';
	if (width_pad != ' ')
		add_bytes(ft_putstr_fd(spec.prefix, fd), &nbytes);
	if (!(spec.flags & F_MINUS))
		add_bytes(padding(width_pad, spec.width - maxlen, fd), &nbytes);
	if (width_pad == ' ')
		add_bytes(ft_putstr_fd(spec.prefix, fd), &nbytes);
	if (spec.flags & PRECISION)
		add_bytes(padding(spec.pad, prec_pad_len, fd), &nbytes);
	add_bytes(write(fd, spec.str, len), &nbytes);
	if (spec.flags & F_MINUS)
		add_bytes(padding(width_pad, spec.width - maxlen, fd), &nbytes);
	return (nbytes);
}

int	ft_vfprintf(int fd, const char *format, va_list args) 
{
	t_spec		spec;
	int			nbytes;
	int			len;

	nbytes = 0;
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
			len = parse_spec(format, args, &spec, &format);
			add_bytes(ft_putspec_fd(spec, len, fd), &nbytes);
		}
	}
	return (nbytes);
}

#define BUF_SIZE 4026
int	filecmp(FILE *file, int fd2)
{
	char	buf1[BUF_SIZE];
	char	buf2[BUF_SIZE];
	ssize_t	bytes1;
	ssize_t	bytes2;

	rewind(file);
	lseek(fd2, 0, SEEK_SET);
	while (1)
	{
		bytes1 = read(fileno(file), buf1, BUF_SIZE);
		bytes2 = read(fd2, buf2, BUF_SIZE);
		if (bytes1 <= 0 || bytes2 <= 0 || ft_strncmp(buf1, buf2, ft_max(bytes1, bytes2)))
			break ;
	}
	rewind(file);
	lseek(fd2, 0, SEEK_SET);
	return (ft_strncmp(buf1, buf2, ft_max(bytes1, bytes2)));
}

void	putfile(int fd)
{
	lseek(fd, 0, SEEK_SET);
	char	buf[BUF_SIZE];
	ssize_t	bytes;

	printf("|");
	while ((bytes = read(fd, buf, BUF_SIZE)) > 0)
		printf("%.*s", (int) bytes, buf);
	printf("|");
	printf("\n");
	lseek(fd, 0, SEEK_SET);
}

void	test(char *str, ...)
{
	va_list	args1;
	va_list	args2;
	int		fd;
	FILE	*file;
	char	template[] = "/home/joel/coding/exercises/printf/temp/.tests/XXXXXX";
	char	*color;
	int		expected;
	int		output;

	fd = mkstemp(template);
	if (fd < 0)
		return ;
	file = tmpfile();
	if (!file)
	{
		unlink(template);
		return ;
	}
	va_start(args1, str);
	va_copy(args2, args1);

	expected = vfprintf(file, str, args1);
	output = ft_vfprintf(fd, str, args2);
	
	color = expected == output && !filecmp(file, fd) ? GREEN : RED;
	printf("%s", color);
	printf("Input:   \t%s\n", str);
	printf("Expected:\t(%d) ", expected); putfile(fileno(file));
	printf("Output:  \t(%d) ", output); putfile(fd);
	printf("%s", RESET);

	printf("\n----------\n");
	ATF_CHECK(expected == output && !filecmp(file, fd));
	va_end(args1);
	va_end(args2);
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

// TEST 01 --> NO FORMAT STRINGS
ATF_TC(test01);
ATF_TC_HEAD(test01, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing ft_printf");
}
ATF_TC_BODY(test01, tc)
{
	printf("\n<test01> %s\n", tests_titles[1]);
	test("This is a test");
	test("This is a test", "Another test");
	test("1234567890", 234);
	test("12345678902fj92jfq9jf9jf", 242);
	test("\123\223\222\111\222\244\012", 239424980);
	test("");
	test("-1", 0);
}

// TEST 02 --> NO EXISTING FORMAT
ATF_TC(test02);
ATF_TC_HEAD(test02, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing ft_printf");
}
ATF_TC_BODY(test02, tc)
{
	printf("\n<test02> %s\n", tests_titles[2]);
	test("hello %t", 209847209487);
	test("%q");
	test("%q%q%q%q%q%q%|%^");
	test("%!!!!!!!!!", "", '4');
	test("     % ");
	test("%");
}

// TEST 03 --> FORMAT %
ATF_TC(test03);
ATF_TC_HEAD(test03, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing ft_printf");
}
ATF_TC_BODY(test03, tc)
{
	printf("\n<test03> %s\n", tests_titles[3]);
	test("%%", "joel");
	test("%%42", "joel");
	test("%%422o%%fj%%o2jfo2fj2jfo", "joe%%l");
	test("%%d%%", "24");
	test("%%i", 42);
	test("%%s");
	test("s%%");
	test("2%%%%");
}

// TEST 04 --> FORMAT c
ATF_TC(test04);
ATF_TC_HEAD(test04, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing ft_printf");
}
ATF_TC_BODY(test04, tc)
{
	printf("\n<test04> %s\n", tests_titles[4]);
	test("%c", 0);
	test("%c%c", 0, 0);
	test("%c%%%c", -1, 0);
	test("%c", 'a');
	test("%c%c", 24, 99);
	test("%c%%%c", 100, -129);
	test("%c", 999);
	test("%c%c", -2498, -2999);
	test("%c%%%c", -1090, 99129);
	test("%c%c%c%c%c%ccoejfoejfo%ccc%c", '1', '2', '3', '4', '5', '6', '7', '8');
	test("cc%cc", -2147483648);
	test("%10c", 0);
	test("%100c", 0);
	test("%0c", 0);
	test("%-0c", 0);
	test("%0-c", 0);
	test("%0-.c", 0);
	test("%0-1.1c", 0);
	test("%0-1.01c", 0);
	test("%10c", 65);
	test("%100c", 65);
	test("%1-23c", 65);
	test("%0c", 65);
	test("%-0c", 65);
	test("%0-c", 65);
	test("%0-.c", 65);
	test("%0-1.1c", 65);
	test("%0-1.01c", 65);
	test("%0-1.-01c", 65);
	test("%0-1.-010c", 65);
	test("%010.-010c", 65);
	test("%10.-0100c", 65);
	test("%10.10c", 65);
	test("%-10.10c", 65);
	test("%-9.10c", 65);
	test("%-8.10c", 65);
	test("%-8.6c", 65);
	test("%8.6c", 65);
	test("%2.6c", 65);
	test("%2.8c", 65);
	test("%2c", 65);
	test("%002c", 65);
	test("%01002c", 65);
	test("%#01002c", 65);
	test("%-01002c", 65);
}

// TEST 05 --> FORMAT s
ATF_TC(test05);
ATF_TC_HEAD(test05, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing ft_printf");
}
ATF_TC_BODY(test05, tc)
{
	printf("\n<test05> %s\n", tests_titles[5]);
	test("%s", "joel");
	test("%s", 0);
	test("%s", "");
	test("%10s", "12345");
	test("%10.0s", "12345");
	test("%10.10s", "\12\342\234\21");
	test("%0.100s", "\12\342\234\21");
	test("%0.5s", "\12\342\234\21");
	test("%#0.5s", "\12\342\234\21");
	test("%-0.5s", "\12\342\234\21");
	test("%-.5s", "\12\342\234\21");
	test("%-10.5s", "\12\342\234\21");
	test("%-------10.1s", "");
	test("%#s", 0);
	test("%-10s", 0);
	test("%-s", 0);
	test("%-100s", 0);
	test("%-1s", 0);
	test("%31s", 0);
	test("%1s", 0);
	test("%#.s", 0);
	test("%-.10s", 0);
	test("%-.s", 0);
	test("%-.100s", 0);
	test("%-.1s", 0);
	test("%.31s", 0);
	test("%.1s", 0);
	test("%+10.100s", "029f029ufh29ufh2-9fh2-");
	test("%+-100.8s", "029f029ufh29ufh2-9fh2-");
	test("%+-100.*s", 9, "029f029ufh29ufh2-9fh2-");
	test("%+-100.*s", 0, "029f029ufh29ufh2-9fh2-");
}

// TEST 06 --> FORMAT d and i
ATF_TC(test06);
ATF_TC_HEAD(test06, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing ft_printf");
}
ATF_TC_BODY(test06, tc)
{
	printf("\n<test06> %s\n", tests_titles[6]);
	test("%d", 0);
	test("%d", 214);
	test("%d", 2243);
	test("%d", 002243);
	test("%d", -2147483648);
	test("%d", 2147483648);
	test("%d", 2147483647);
	test("%+0d", 0);
	test("%+d", 0);
	test("%+ 10d", 214);
	test("%+ d", 214);
	test("%+++++ 22d", 2243);
	test("%#---- +d", 002243);
	test("%#d", -2147483648);
	test("%.10d", 2147483648);
	test("%10.10d", 2147483647);
	test("%-10.10d", 10);
	test("%20.10d", 10);
	test("%20.0d", 10);
	test("%-0.0d", 10);
	test("%0.0d", 0);
	test("%-10.0d", 0);
	test("%hhd", 2242987429);
	test("%hhd", -2242987429);
	test("%-100hhd", -2242987429);
	test("%100hhd", -2242987429);
	test("%10.10hhd", 2242987429);
	test("%#+10.10hhd", 2242987429);
	test("%+10.10hhd", 2242987429);
	test("% +10.10hhd", 2242987429);
	test("% +10.0hhd", 2242987429);
	test("% +10.0hhd", 0);
	test("% +10.0hd", 999999999999999999);
	test("% +10.0hd", -999999999999999999);
	test("% #++10.0hd", -999999999999999999);
	test("% #++0.100hd", -999999999999999999);
	test("% #++0.100hd", 1234);
	test("% #++0.100hd", -1234);
	test("%+lld", -1234);
	test("%+lld", -1023954029817508998);
	test("%+lld", 10239540298175089988LU);
	test("%+100lld", 1023954029817508998);
	test("%+23.12lld", 1023954029817508998);
	test("%# +23.12lld", 1023954029817508998);
	test("% + 23.12lld", 1023954029817508998);
	test("%hd", 2242987429);
	test("%hd", -2242987429);
	test("%-100hd", -2242987429);
	test("%100hd", -2242987429);
	test("%10.10hd", 2242987429);
	test("%#+10.10hd", 2242987429);
	test("%+10.10hd", 2242987429);
	test("% +10.10hd", 2242987429);
	test("% +10.0hd", 2242987429);
	test("% +10.0hd", 0);
	test("% +10.0ld", 999999999999999999);
	test("% +10.0ld", -999999999999999999);
	test("% #++10.0ld", -999999999999999999);
	test("% #++0.100ld", -999999999999999999);
	test("% #++0.100ld", 1234);
	test("% #++0.100ld", -1234);
	test("%+ld", -1234);
	test("%+ld", -1023954029817508998);
	test("%+ld", 10239540298175089988LU);
	test("%+100ld", 1023954029817508998);
	test("   ---%+23.12lld---", 1023954029817508998);
	test("%# +23.12ld", 1023954029817508998);
	test("%+23.12ld", 1023954029817508998);
	test("%23.12d", 1023954029817508998);
	test("%23.12hd", 1023954029817508998);
	test("%23.12hhdfwjf9wjf9wjf9wjf9wjf", 1023954029817508998);
	test("%23.12hd", 1023954029817508998);
	test("%23.12hd, %d, %d, %d", 1023954029817508998, 1, 1, 2, 3);
}

// TEST 07 --> FORMAT u, x, X, o
ATF_TC(test07);
ATF_TC_HEAD(test07, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing ft_printf");
}
ATF_TC_BODY(test07, tc)
{
	printf("\n<test07> %s\n", tests_titles[7]);
	test("%u", -1);
	test("%u", -2);
	test("%u", 4294967295);
	test("%u", 4294967296);
	test("%u", 4294967296224);
	test("% +u", 4294967296224);
	test("% #+u", 4294967296224);
	test("% # +u", 4294967296224);
	test("% -# +u", 4294967296224);
	test("%--u", 4294967296224);
	test("%--uwo", -1);
	test("%--uyo", -1);
	test("%--uuo", -1);
	test("%  --uuo", -1);
	test("%  - -uuo", -1);
	test("%%%  - -uuo", -1);
	test("%%%  - -luuo", -1);
	test("% luuo", -1);
	test("% lluuo", -1);
	test("% huuo", -1);
	test("%+hhuuo", -1);
	test("%+hhu", -1);
	test("%hhu", -1);
	test("%hhu, %u%hd", -1, -24, 243);
	test("%10hhu, %u%hd", -1, -24, 243);
	test("%010hhu, %u%hd", -1, -24, 243);
	test("%#010hhu, %u%hd", -1, -24, 243);
	test("%#-010hhu, %u%hd", -1, -24, 243);
	test("%#-010hhu, %u%hd", -1, -24, 243);
	test("%#-0100hhu, %u%hd", -1, -24, 243);
	test("%#-0100.hhu, %u%hd", 0, 0, 243);
	test("%#-0100.0hhu, %u%hd", 0, 0, 243);
	test("%#-0100.10hhu, %u%hd", 0, 0, 243);
	test("%#0.10hhu, %u%hd", 0, 0, 243);
	test("%#0.100hhu, %u%hd", 0, 0, 243);
	test("%#0.100lu, %u%hd", 0, 0, 243);
	test("%#0.100llu, %u%hd", 0, 0, 243);
	test("%#0.100llu, %u%hd", -1, 0, 243);
	test("%#10.100llu, %u%hd", -1, 0, 243);
	test("%#-10.100llu, %u%hd", -1, 0, 243);
	test("%-10.1llu, %u%hd", -1, 0, 243);
	test("%----10.1llu, %u%hd", -1, 0, 243);
	test("%----10.10llu, %u%hd", -1, 0, 243);
	test("%----10.10hhu, %u%hd", -1, 0, 243);
	test("%+ -#-#0.10hhu, %u%hd", -1, 0, 243);
	test("% -#-#100.10hhu, %u%hd", -1, 0, 243);
	test("%100.10hhu, %u%hd", -1, 0, 243);

	test("%x", -1);
	test("%x", -2);
	test("%x", 4294967295);
	test("%x", 4294967296);
	test("%x", 4294967296224);
	test("% +x", 4294967296224);
	test("% #+x", 4294967296224);
	test("% # +x", 4294967296224);
	test("% -# +x", 4294967296224);
	test("%--x", 4294967296224);
	test("%--xwo", -1);
	test("%--xyo", -1);
	test("%--xuo", -1);
	test("%  --xuo", -1);
	test("%  - -xuo", -1);
	test("%%%  - -xuo", -1);
	test("%%%  - -lxuo", -1);
	test("% lxuo", -1);
	test("% llxuo", -1);
	test("% hxuo", -1);
	test("%+hhxuo", -1);
	test("%+hhx", -1);
	test("%hhx", -1);
	test("%hhx, %u%hd", -1, -24, 243);
	test("%10hhx, %u%hd", -1, -24, 243);
	test("%010hhx, %u%hd", -1, -24, 243);
	test("%#010hhx, %u%hd", -1, -24, 243);
	test("%#-010hhx, %u%hd", -1, -24, 243);
	test("%#-010hhx, %u%hd", -1, -24, 243);
	test("%#-0100hhx, %u%hd", -1, -24, 243);
	test("%#-0100.hhx, %u%hd", 0, 0, 243);
	test("%#-0100.0hhx, %u%hd", 0, 0, 243);
	test("%#-0100.10hhx, %u%hd", 0, 0, 243);
	test("%#0.10hhx, %u%hd", 0, 0, 243);
	test("%#0.100hhx, %u%hd", 0, 0, 243);
	test("%#0.100lx, %u%hd", 0, 0, 243);
	test("%#0.100llx, %u%hd", 0, 0, 243);
	test("%#0.100llx, %u%hd", -1, 0, 243);
	test("%#10.100llx, %u%hd", -1, 0, 243);
	test("%#-10.100llx, %u%hd", -1, 0, 243);
	test("%-10.1llx, %u%hd", -1, 0, 243);
	test("%----10.1llx, %u%hd", -1, 0, 243);
	test("%----10.10llx, %u%hd", -1, 0, 243);
	test("%----10.10hhx, %u%hd", -1, 0, 243);
	test("%+ -#-#0.10hhx, %x%hx", -1, 0, 243);
	test("% -#-#100.10hhx, %x%hd", -1, 0, 243);
	test("%100.10hhx, %x%hx", -1, 0, 243);

	test("%X", -1);
	test("%X", -2);
	test("%X", 4294967295);
	test("%X", 4294967296);
	test("%X", 4294967296224);
	test("% +X", 4294967296224);
	test("% #+X", 4294967296224);
	test("% # +X", 4294967296224);
	test("% -# +X", 4294967296224);
	test("%--X", 4294967296224);
	test("%--Xwo", -1);
	test("%--Xyo", -1);
	test("%--Xuo", -1);
	test("%  --Xuo", -1);
	test("%  - -Xuo", -1);
	test("%%%  - -Xuo", -1);
	test("%%%  - -lXuo", -1);
	test("% lXuo", -1);
	test("% llXuo", -1);
	test("% hXuo", -1);
	test("%+hhXuo", -1);
	test("%+hhX", -1);
	test("%hhX", -1);
	test("%hhX, %u%hd", -1, -24, 243);
	test("%10hhX, %u%hd", -1, -24, 243);
	test("%010hhX, %u%hd", -1, -24, 243);
	test("%#010hhX, %u%hd", -1, -24, 243);
	test("%#-010hhX, %u%hd", -1, -24, 243);
	test("%#-010hhX, %u%hd", -1, -24, 243);
	test("%#-0100hhX, %u%hd", -1, -24, 243);
	test("%#-0100.hhX, %u%hd", 0, 0, 243);
	test("%#-0100.0hhX, %u%hd", 0, 0, 243);
	test("%#-0100.10hhX, %u%hd", 0, 0, 243);
	test("%#0.10hhX, %u%hd", 0, 0, 243);
	test("%#0.100hhX, %u%hd", 0, 0, 243);
	test("%#0.100lX, %u%hd", 0, 0, 243);
	test("%#0.100llX, %u%hd", 0, 0, 243);
	test("%#0.100llX, %u%hd", -1, 0, 243);
	test("%#10.100llX, %X%hd", -1, 0, 243);
	test("%#-10.100llX, %x%hd", -1, 0, 243);
	test("%-10.1llX, %u%hd", -1, 0, 243);
	test("%----10.1llX, %u%hd", -1, 0, 243);
	test("%----10.10llX, %u%hd", -1, 0, 243);
	test("%----10.10hhX, %X%hd", -1, 0, 243);
	test("%+ -#-#0.10hhX, %x%hx", -1, 0, 243);
	test("% -#-#100.10hhX, %x%hd", -1, 0, 243);
	test("%100.10hhX, %X%hx", -1, 0, 243);

	test("%o", -1);
	test("%o", -2);
	test("%o", 4294967295);
	test("%o", 4294967296);
	test("%o", 4294967296224);
	test("% +o", 4294967296224);
	test("% #+o", 4294967296224);
	test("% # +o", 4294967296224);
	test("% -# +o", 4294967296224);
	test("%--o", 4294967296224);
	test("%--owo", -1);
	test("%--oyo", -1);
	test("%--ouo", -1);
	test("%  --ouo", -1);
	test("%  - -ouo", -1);
	test("%%%  - -ouo", -1);
	test("%%%  - -louo", -1);
	test("% louo", -1);
	test("% llouo", -1);
	test("% houo", -1);
	test("%+hhouo", -1);
	test("%+hho", -1);
	test("%hho", -1);
	test("%hho, %u%hd", -1, -24, 243);
	test("%10hho, %u%hd", -1, -24, 243);
	test("%010hho, %u%hd", -1, -24, 243);
	test("%#010hho, %u%hd", -1, -24, 243);
	test("%#-010hho, %u%hd", -1, -24, 243);
	test("%#-010hho, %u%hd", -1, -24, 243);
	test("%#-0100hho, %u%hd", -1, -24, 243);
	test("%#-0100.hho, %u%hd", 0, 0, 243);
	test("%#-0100.0hho, %u%hd", 0, 0, 243);
	test("%#-0100.10hho, %u%hd", 0, 0, 243);
	test("%#0.10hho, %u%hd", 0, 0, 243);
	test("%#0.100hho, %u%hd", 0, 0, 243);
	test("%#0.100lo, %u%hd", 0, 0, 243);
	test("%#0.100llo, %u%hd", 0, 0, 243);
	test("%#0.100llo, %u%hd", -1, 0, 243);
	test("%#10.100llo, %X%hd", -1, 0, 243);
	test("%#-10.100llo, %x%hd", -1, 0, 243);
	test("%-10.1llo, %u%hd", -1, 0, 243);
	test("%----10.1llo, %o%hd", -1, 0, 243);
	test("%----10.10llo, %u%ho", -1, 0, 243);
	test("%----10.10hho, %X%ho", -1, 0, 243);
	test("%+ -#-#0.10hho, %o%hx", -1, 0, 243);
	test("% -#-#100.10hho, %x%hd", -1, 0, 243);
	test("%100.10hho, %X%ho", -1, 0, 243);
}

// TEST 08 --> FORMAT 'p'
ATF_TC(test08);
ATF_TC_HEAD(test08, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing ft_printf");
}
ATF_TC_BODY(test08, tc)
{
	int	var;

	printf("\n<test08> %s\n", tests_titles[8]);
	test("%p", 0);
	test("%10p", 0);
	test("%10.10p", 0);
	test("%-10.10p", 0);
	test("%#-10.10p", 0);
	test("%#-10.100p", 0);
	test("%-10.100p", 0);
	test("%10.100p", 0);
	test("%0.100p", 0);
	test("%#10p", 0);
	test("%-10p", 0);
	test("%010p", 0);
	test("%050p", 0);
	test("%050.0p", 0);
	test("%#050.1p", 0);
	test("%#050.20p", 0);
	test("%#050.25p", 0);
	test("%#0150.25p", 0);
	test("%#00.p", 0);
	test("%0.p", 0);
	test("%.p", 0);
	test("%--.p", 0);
	test("%-100.p", 0);
	test("%-100.240p", 0);
	test("%-00.40p", 0);
	test("%-50.20p", 0);
	test("%#-50p", 0);

	test("%p", &var);
	test("%10p", &var);
	test("%10.10p", &var);
	test("%-10.10p", &var);
	test("%#-10.10p", &var);
	test("%#-10.100p", &var);
	test("%-10.100p", &var);
	test("%10.100p", &var);
	test("%0.100p", &var);
	test("%#10p", &var);
	test("%-10p", &var);
	test("%010p", &var);
	test("%050p", &var);
	test("%050.0p", &var);
	test("%#050.1p", &var);
	test("%#050.20p", &var);
	test("%#050.25p", &var);
	test("%#0150.25p", &var);
	test("%#00.p", &var);
	test("%0.p", &var);
	test("%.p", &var);
	test("%--.p", &var);
	test("%-100.p", &var);
	test("%-100.240p", &var);
	test("%-00.40p", &var);
	test("%-50.20p", &var);
	test("%#-50p", &var);
	test("%*p", 30, &var);
}

// TEST PROGRAM
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);
	ATF_TP_ADD_TC(tp, test01);
	ATF_TP_ADD_TC(tp, test02);
	ATF_TP_ADD_TC(tp, test03);
	ATF_TP_ADD_TC(tp, test04);
	ATF_TP_ADD_TC(tp, test05);
	ATF_TP_ADD_TC(tp, test06);
	ATF_TP_ADD_TC(tp, test07);
	ATF_TP_ADD_TC(tp, test08);

	return (atf_no_error());
}
