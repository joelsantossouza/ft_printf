#include "../includes/libftprintf.h"
#include <stdio.h>

int	main(void)
{
	ft_printf("(myown)    %%Hello, %20.10d\n", 42);
	printf(   "(original) %%Hello, %20.10d\n", 42);
	return (0);
}
