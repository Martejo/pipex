/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:45:48 by gemartel          #+#    #+#             */
/*   Updated: 2023/12/04 14:42:33 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

void	ft_putstr_pf(char *s, size_t *count_char);
void	ft_putchar_pf(char c, size_t *count_char);
void	ft_putnbr_pf(int nbr, size_t *count_char);
void	print_ptr_addr(void *ptr, size_t *count_char);
void	ft_puthexa_upper(unsigned int nbr, size_t *count_char);
void	ft_puthexa_lower(unsigned int nbr, size_t *count_char);
void	ft_putnbr_unsigned(unsigned int nbr, size_t *count_char);
int		ft_printf(const char *str, ...);

#endif
