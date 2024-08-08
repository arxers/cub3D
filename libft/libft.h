/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 10:46:11 by jaslim            #+#    #+#             */
/*   Updated: 2024/08/07 19:13:44 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <aio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

// get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// libft
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *str);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);
int					ft_atoi(const char *nptr);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_tolower(int c);
int					ft_toupper(int c);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*safe_strjoin(char *s1, const char *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstdel_char(void *ptr);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

// printf
void				ft_putchar(int fd, int c, int *count);
void				ft_putstr(int fd, char *s, int *count);
void				ft_putnbr(int fd, long long n, int *count);
void				ft_putunbr(int fd, unsigned long long n, int *count);
void				ft_puthex(int fd, unsigned long long n, char *base,
						int *count);
void				ft_putptr(int fd, void *n, int *count);
void				ft_checkcase(int fd, va_list a, char c, int *count);
int					ft_printf(const char *s, ...);
int					ft_dprintf(int fd, const char *s, ...);
int					ft_sprintf(char *str, const char *format, ...);

// get_next_line
char				*ft_strdup_gnl(char *s);
char				*ft_strjoin_gnl(char *s1, char *s2);
void				ft_free_gnl(char **c, char **u, char **m);
int					check_nl(char *mem);
int					read_and_append(char **mem, char **buf_left, int fd);
char				*assign_leftovers(char **mem);
char				*assign_line(char *mem);
char				*get_next_line(int fd);

// misc
void				*ft_free_void(void **ptr);
void				*ft_free(char **s);
void				*ft_free_2d(char ***s);
void				*ft_free_3d(char ****s);
long				ft_atol(const char *nptr);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_count_digits(long long n);
int					ft_isspace(char c);
char				**ft_lst_to_arr(t_list **lst);
char				*ft_strtok(char *str, const char *delim);
char				*ft_strtok_dup(char *str, const char *delim);
void				ft_print_fd(int fd);
int					ft_count_strings(char **array);
int					ft_only_c(char *s, char c);

#endif
