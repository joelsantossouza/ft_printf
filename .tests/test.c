#include "../includes/libftprintf.h"
#include <stdio.h>

int	main(void)
{
	ft_printf("(myown)    %%Hello, %.100s\n", "joel");
	printf(   "(original) %%Hello, %.100s\n", "joel");
	return (0);
}
