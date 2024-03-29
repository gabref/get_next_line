#include "get_next_line.h"
// #include "leak_detector_c.h"
#include <stdio.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	// atexit(report_mem_leak);
	fd = 0;
	i = 0;
	do
	{
		line = get_next_line(fd);
		printf("Line %d\t%s\n", i++, line);
		free(line);
	} while (line != NULL);
	return (0);
}
