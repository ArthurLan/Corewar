/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:10:48 by clecalie          #+#    #+#             */
/*   Updated: 2018/11/19 09:34:07 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <wchar.h>
# include <stdint.h>
# include "libft.h"

int			ft_printf(const char *format, ...);
size_t		arg_len(char *str);
char		*get_length_flag(char *flag);
char		*handle_flags(char *length_flag, char *flag, va_list *args);
char		*handle_other_flags(char *flag, va_list *args);
char		*handle_conversion(char *flag, char *ret);
char		*replacestr(char *dest, char *find, char *content);
char		*add_begin(char *str, char *add);
char		*add_end(char *str, char *add);
char		*get_flag(char *str);
char		*handle_sharp(char *flag, char *ret);
char		*handle_neg(char *flag, char *ret);
char		*handle_zero(char *flag, char *ret);
char		*handle_digit(char *flag, char *ret);
char		*handle_plus(char *flag, char *ret);
char		*handle_space(char *flag, char *ret);
char		*handle_precision(char *flag, char *ret);
char		*get_0_param(char *str);
long long	ft_atol(const char *str);
char		*ft_uintmaxtoa(uintmax_t n);
char		*ft_intmaxtoa(intmax_t n);
char		*ft_uintmaxtoa_base(uintmax_t n, int base);
char		*ft_intmaxtoa_base(intmax_t n, int base);
char		*ft_ulltoa(unsigned long long n);
char		*ft_ulltoa_base(unsigned long long n, int base);
char		*wchartoasc(wchar_t *str);
char		*handle_di(char flag_letter, char *ret,
		char *length_flag, va_list *args);
char		*handle_x(char flag_letter, char *ret,
		char *length_flag, va_list *args);
char		*handle_o(char flag_letter, char *ret,
		char *length_flag, va_list *args);
char		*handle_u(char flag_letter, char *ret,
		char *length_flag, va_list *args);
char		*handle_s(char *flag, char *ret, char *length_flag, va_list *args);
char		*handle_c(char *flag, char *ret, char *length_flag, va_list *args);
char		*ft_update(char **old, char *new);
char		*replace_chars(char *dest, char *find, char *content);
char		*apply_flag(char *flag, char *str, int *i, va_list *args);
char		*ft_strndup_static(char *str, size_t n);

#endif
