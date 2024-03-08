/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:51:16 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/08 06:56:00 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	ft_power(int base, int exponent)
{
	int	result;

	result = 1;
	while (exponent > 0)
	{
		result *= base;
		exponent--;
	}
	return (result);
}

void	initialise_data(char **hex_digits, int *i, int *j)
{
	*i = 0;
	*j = 0;
	hex_digits[0] = "0123456789ABCDEF";
	hex_digits[1] = "0123456789abcdef";
}

long	convert_to_decimal(char *str)
{
	int		len;
	long	decimal;
	char	*hex_digits[2];
	int		i;
	int		j;

	initialise_data(hex_digits, &i, &j);
	len = ft_strlen(str) - 1;
	decimal = 0;
	while (len >= 0)
	{
		while (hex_digits[0][j] != '\0')
		{
			if (hex_digits[0][j] == str[len] || hex_digits[1][j] == str[len])
			{
				decimal += j * ft_power(16, i);
				break ;
			}
			j++;
		}
		j = 0;
		i++;
		len--;
	}
	return (decimal);
}
