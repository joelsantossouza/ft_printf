#include "../includes/libftprintf.h"
#include <stdio.h>

int	main(void)
{
	ft_printf("return: %d\n", ft_printf("Im %1.20o years old\n", 42));
	printf("return: %d\n", printf("Im %1.20o years old\n", 42));
	return (0);
}
