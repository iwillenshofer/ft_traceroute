/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 10:54:12 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/09 00:16:54 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <limits.h>

# define TRUE 1
# define FALSE 0

int		ft_ishex(int c);
void	ft_putnbr(int nb);
void	ft_putchar(char c);
char	ft_isprint(char c);
int		ft_isdigit(int c);
char	*ft_nothex(char *s);
void	ft_puthex(size_t nb);
char	*ft_strdup(char *src);
char	**ft_split(char *src);
size_t	ft_arglen(char **arg);
double	ft_sqrt(double number);
char	*ft_notnumeric(char *s);
int		ft_atoi(const char *str);
void	ft_putstr(const char *s);
size_t	ft_strlen(const char *s);
size_t	ft_atoul(const char *str);
void	ft_bzero(void *s, size_t n);
void	ft_putbits(unsigned char byte);
void	ft_puthexbyte(unsigned char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strcpy(char *dst, char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	ft_putbytes(void *bytes, size_t size);
void	*ft_memset(void *b, int c, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_puthex_bytes(void *bytes, size_t size, size_t space, size_t carr);

#endif
