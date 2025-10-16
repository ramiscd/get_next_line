/* Add the main project logic. */

/* 
Valor de retorno:
	Linha lida: comportamento correto
	NULL: não há mais nada para ler ou ocorreu um erro

Funções externas autorizadas -> read, malloc, free

Descrição
	Escreva uma função que retorna uma linha lida de um file descriptor

• Chamadas repetidas (por exemplo, usando um loop) para sua função get_next_line()
devem permitir que você leia o arquivo de texto apontado pelo file descriptor, uma
linha por vez.

• Sua função deve retornar a linha que foi lida.
Se não houver mais nada para ler ou se ocorrer um erro, ela deve retornar NULL.

• Certifique-se de que sua função funcione como esperado tanto ao ler um arquivo
quanto ao ler da entrada padrão.

• Observe que a linha retornada deve incluir o caractere de terminação \n, exceto
quando o final do arquivo é alcançado e o arquivo não termina com um caractere
\n.

• Seu header file get_next_line.h deve conter pelo menos o protótipo da função
get_next_line().

• Adicione todas as funções auxiliares necessárias no arquivo get_next_line_utils.c. 
*/

/* char *get_next_line(int fd)
{
	return (fd);
} */	

	
	
	
	// Create a new file or open it
	// if it exists (write-only access)
	// File permissions: rw-r--r--s
	/* 
	int fd = creat("novo_arquivo.txt", 0644);
	printf("%i", fd);
	close(fd);
	 */
	/* ------------------------------------- */

	// If file does not have in directory
	// then file foo.txt is created.
	/* 	
	int fd2 = open("foo.txt", O_RDONLY | O_CREAT);
	printf("fd2 = %d", fd2);
	*/
	/* ------------------------------------- */

	/* 	
	int fd, sz;
	char* c = (char*)calloc(100, sizeof(char));
	fd = open("foo.txt", O_RDONLY);
	if (fd < 0) {
		perror("r1");
		exit(1);
	}
	sz = read(fd, c, 150);
	printf("called read(% d, c, 10). returned that"
			" %d bytes were read.\n",
			fd, sz);
	// c[sz] = '\0';
	printf("Those bytes are as follows: %s\n", c);
	return 0;
	*/