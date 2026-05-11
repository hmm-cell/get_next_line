#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h" // Certifica-te que o nome do teu .h está correto

int	main(void)
{
	int		fd;
	char	*line;
	int		count;

	count = 1;
	// Abre um ficheiro chamado "test.txt" (cria este ficheiro antes de correr!)
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
		free(line); // MUITO IMPORTANTE: libertar a memória de cada linha
	}
	printf("\n--- Fim do Teste ---\n");

	close(fd);
	return (0);
}
