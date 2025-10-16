/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 22:38:31 by rdamasce          #+#    #+#             */
/*   Updated: 2025/10/15 23:16:21 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Add the prototyoes

#define BUFFER_SIZE=8; // Quantos blocos vão ser lidos de cada vez.

char *get_next_line(int fd);