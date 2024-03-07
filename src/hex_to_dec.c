/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:51:16 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/07 23:14:23 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

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

long	convert_to_decimal(char *str)
{
	int  len = ft_strlen(str) - 1;
	long decimal = 0;
	char *hex_digits_up = "0123456789ABCDEF";
	char *hex_digits_min = "0123456789abcdef";

	int i = 0;
	while (len > 1)
	{
		int j = 0;
		while (hex_digits_up[j] != '\0')
		{
			if (hex_digits_up[j] == str[len] || hex_digits_min[j] == str[len])
			{
				decimal += j * ft_power(16, i);
				break;
			}
			j++;
		}
		i++;
		len--;
	}
	return (decimal);
}