/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 10:54:12 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/19 08:14:55 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

void	ft_putnbr(int nb);
void	ft_putchar(char c);
char	ft_isprint(char c);
void	ft_puthex(size_t nb);
char 	*ft_strdup(char *src);
char 	**ft_split(char *src);
size_t	ft_arglen(char **arg);
double	ft_sqrt(double number);
void	ft_putstr(const char *s);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	ft_puthexbyte(unsigned char c);
void	ft_putbits(unsigned char byte);
char 	*ft_strjoin(char *s1, char *s2);
char	*ft_strcpy(char *dst, char *src);
void	ft_putbytes(void *bytes, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	ft_puthex_bytes(void *bytes, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
