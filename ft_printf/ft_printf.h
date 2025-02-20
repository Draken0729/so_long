/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:57:13 by qbaret            #+#    #+#             */
/*   Updated: 2025/02/20 18:08:53 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int				ft_putstr(char *s);
int				ft_putnbr(int n);
int				ft_putchar(char c);
unsigned int	ft_printhex_min(unsigned int nombre);
unsigned int	ft_printhex_maj(unsigned int nombre);
int				ft_print_pointer(void *ptr);
int				ft_putunbr(unsigned int n);
int				ft_printf( char *format, ...);

#endif