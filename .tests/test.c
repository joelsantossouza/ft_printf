#include "../includes/libftprintf.h"
#include <stdio.h>

int	main(void)
{
	ft_printf("Im %10.20x years old\n", 42);
	printf("Im %10.20x years old\n", 42); 
	return (0);
}
