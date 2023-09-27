/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:16:31 by jbak              #+#    #+#             */
/*   Updated: 2022/11/21 21:47:55 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define INT_MIN -2147483648
# define INT_MAX 2147483647

# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strrncmp(const char *s1, const char *s2, size_t n);

void	ft_bzero(void *s, size_t len);
void	*ft_calloc(size_t nbyte, size_t size);
void	*ft_realloc(void *buf, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	*make_free(char ***split);

char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char **s1, char const *s2, int flag);
char	*ft_substr(char **s, unsigned int start, size_t len, int flag);
char	*get_next_line(int fd);

#endif
