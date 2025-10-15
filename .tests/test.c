while (*format)
{
	ptr = format;
	format = ft_strchrnul(format, '%');
	if (*format && *(format + 1) == '%')
		format++;
	write(1, ptr, format - ptr);
	if (!*format)
		break ;
}
