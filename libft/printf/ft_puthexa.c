/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:45:58 by gemartel          #+#    #+#             */
/*   Updated: 2023/12/04 14:38:32 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_puthexa_upper(unsigned int nbr, size_t *count_char)
{
	if (nbr > 15)
		ft_puthexa_upper(nbr / 16, count_char);
	ft_putchar_pf("0123456789ABCDEF"[nbr % 16], count_char);
}

void	ft_puthexa_lower(unsigned int nbr, size_t *count_char)
{
	if (nbr > 15)
		ft_puthexa_lower(nbr / 16, count_char);
	ft_putchar_pf("0123456789abcdef"[nbr % 16], count_char);
}
