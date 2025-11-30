/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:33:04 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/30 14:44:08 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define LOWER_BASE "0123456789abcdef"
# define UPPER_BASE "0123456789ABCDEF"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

int		ft_atoi(const char *str);
char	*ft_itoa(int n);

void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *buffer, int c, size_t n);

char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char*s1, const char *s2, size_t n);
char	*ft_strnstr(const char *str, const char *find, size_t n);
char	*ft_strrchr(const char *str, int c);
char	*ft_strtrim(const char *str, const char *set);
char	*ft_substr(const char *str, unsigned int start, size_t len);

char	**ft_split(char const *s, char c);
void	ft_striteri(char *str, void (*f)(unsigned int, char *));
char	*ft_strmapi(char *str, char (*f)(unsigned int, char));

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *str, int fd);

void	ft_lstadd_back(t_list **list, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *list);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

char	*get_next_line(int fd);
size_t	ft_strlen_gnl(const char *str);
char	*ft_strchr_gnl(const char *str, int c);
char	*ft_substr_gnl(char const *str, unsigned int start, size_t len);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strcmp(const char *s1, const char *s2);

int		ft_printf(const char *format, ...);
int		ft_conv_printf(char c, va_list args);
int		ft_putchar_printf(char c);
int		ft_putstr_printf(char *str);
int		ft_putnbr_printf(int n);
int		ft_putnbr_unsigned_printf(unsigned int n);
int		ft_puthex_printf(char c, unsigned long n);
int		ft_putptr_printf(void *ptr);
int		ft_putpercent_printf(void);

#endif