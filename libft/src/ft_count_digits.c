/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:37:18 by jaslim            #+#    #+#             */
/*   Updated: 2024/05/01 17:42:13 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_digits(long long n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%d\n", ft_count_digits(9223372036854775807));
// }
