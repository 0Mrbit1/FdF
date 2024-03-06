/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:51:16 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/06 02:51:16 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_power(int number, int power)
{
	int	result;

	result = 1;
	while (power--)
		result = result * number;
	return (result);
}

long	convert_to_decimal(char *str)
{
	char *hex_digits_up;
	int i;
	int j;
	int len;
	long decimal;
	char *hex_digits_min;

	len = ft_strlen(str) - 1;
	i = 0;
	j = 0;
	decimal = 0;
	hex_digits_up = "0123456789ABCDEF";
	hex_digits_min = "0123456789abcdef";

	while (len > 1)
	{
		while (hex_digits_up[j])
		{
			if (hex_digits_up[j] == str[len])
			{
				decimal += j * ft_power(16, i);
				i++;
				break ;
			}
			else if (hex_digits_min[j] == str[len])
			{
				decimal += j * ft_power(16, i);
				i++;
				break ;
			}
			j++;
		}
		j = 0;
		len--;
	}
	return (decimal);
}