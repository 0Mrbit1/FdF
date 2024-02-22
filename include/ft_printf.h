/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 05:25:39 by acharik           #+#    #+#             */
/*   Updated: 2023/12/13 22:07:21 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

void	ft_putnbr(int number, int *bytes_written);
void	ft_putstr(char *str, int *bytes_written);
void	check_format(const char *str, int i, va_list args, int *bytes_written);
void	ft_putchar(char c, int *bytes_written);
int		ft_printf(const char *str, ...);
void	ft_putnbr_unsigned(unsigned int number, int *bytes_written);
void	convert_to_hex_pointer(unsigned long quotient, int write_0x,
			int *bytes_written, int recursion);
void	convert_to_hex(unsigned int quotient, int flag, int *bytes_written,
			int recursion);

#endif