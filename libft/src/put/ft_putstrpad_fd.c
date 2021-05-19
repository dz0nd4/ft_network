#include "ft_put.h"

void	ft_putstrpad_fd(const char *s, size_t len, int fd)
{
	while (s && *s)
	{
		ft_putchar_fd(*s, fd);
		s++;
		len = (len == 0) ? 0 : len - 1;
	}
	while (len--)
		ft_putchar_fd('0', fd);
}