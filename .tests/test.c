#include "../includes/libftprintf.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	ft_printf("(myown)    %%Hello, %20.10d %-10.10s %-10.p\n", 42, (char*)0, (void*)0);
	printf(   "(original) %%Hello, %20.10d %-10.10s %-10.p\n", 42, (char*)0, (void*)0);
	return (0);
}
