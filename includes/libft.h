/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:59:12 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/14 18:58:32 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <sys/types.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

size_t	ft_strlen(const char *s);
size_t	ft_strnlen(const char *s, size_t maxlen);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_stpcpy(char *dst, const char *src);
char	*ft_strcpy(char *dst, const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchrnul(const char *s, int c);
char	*ft_strchrnul_diff(const char *s, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strstr_diff(const char *haystack, const char *needle);
char	*ft_strstrnul(const char *haystack, const char *needle);
char	*ft_strstrnul_diff(const char *haystack, const char *needle);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strpbrk(const char *s, const char *accept);
char	*ft_strpbrk_diff(const char *s, const char *reject);
char	*ft_strpbrknul(const char *s, const char *accept);
char	*ft_strpbrknul_diff(const char *s, const char *reject);
char	*ft_strrpbrkend_diff(const char *s, const char *reject);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);

void	*ft_mempcpy(void *dest, const void *src, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_mempset(void *s, int c, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

ssize_t	ft_atol_base(const char *nptr, char **endptr, const char *base);
size_t	ft_atoul_base(const char *nptr, char **endptr, const char *base);
int		ft_atoi(const char *nptr);
char	*ft_itoa_base(int nbr, const char *base);
char	*ft_itoa(int n);

ssize_t	ft_putchar_fd(char c, int fd);
ssize_t	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_freearray(void **array, void (*free_memb)(void *));
size_t	ft_word_count(char const *s, char c);
char	**ft_split(char const *s, char c);
size_t	ft_digit_count(ssize_t nbr, unsigned int base);
size_t	ft_nbrlen(ssize_t nbr, unsigned int base);
size_t	ft_udigit_count(size_t nbr, unsigned int base);
double	ft_ipow(double base, size_t exponent);
void	ft_putlong_base_fd(ssize_t nbr, const char *base, int fd);
void	ft_putulong_base_fd(size_t nbr, const char *base, int fd);
size_t	ft_abs(ssize_t j);
size_t	ft_static_ltoa_base(ssize_t nbr, char **sptr, const char *base);
size_t	ft_static_ultoa_base(size_t nbr, char **sptr, const char *base);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
