/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 22:38:26 by rdamasce          #+#    #+#             */
/*   Updated: 2025/10/15 23:29:26 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 

int main()
{
	int fd; // Aonde será armazenado o numero do file descriptor.

	fd = open("test.txt", O_RDONLY);
	
	if (fd < 0) {
		perror("erro ao abrir arquivo");
		printf("erro em abrir arquivo");
		exit(1);
	}
	printf("arquivo aberto com sucesso, fd=%i \n", fd);
}