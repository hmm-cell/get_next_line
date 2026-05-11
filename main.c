#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;
	int		count;

	count = 1;
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Erro ao abrir o ficheiro\n");
		return (1);
	}

	printf("--- Início do Teste ---\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Linha [%d]: %s", count++, line);
		free(line);
	}
	printf("\n--- Fim do Teste ---\n");

	close(fd);
	return (0);
}
