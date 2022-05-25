/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:10:26 by tdelicia          #+#    #+#             */
/*   Updated: 2022/04/27 13:49:26 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t size);

static char const	*skip_spaces(char const *s, char c)
{
	while (*s)
	{
		if (*s != c)
			return (s);
		s++;
	}
	return (s);
}

static char const	*skip_word(char const *s, char c)
{
	while (*s)
	{
		if (*s == c || *s == '\0')
			return (s);
		s++;
	}
	return (s);
}

static char	**res_malloc(char const *s, char c, int *n_words, int *kek)
{
	int		n;
	char	**res;

	if (s == 0)
		return (0);
	*kek = 0;
	n = 0;
	while (*s)
	{
		s = skip_spaces(s, c);
		if (*s != '\0')
			n++;
		s = skip_word(s, c);
	}
	*n_words = n;
	res = malloc((n + 1) * sizeof(char *));
	if (!res)
		exit (errno);
	res[n] = 0;
	return (res);
}

static int	word_len(char const *s, char c)
{
	int	l;

	l = 0;
	while (s[l] != c && s[l])
	{
		l++;
	}
	return (l);
}

char	**ft_split(char const *s, char c)
{
	int		n_words;
	char	**res;
	int		i;
	int		wl;

	res = res_malloc(s, c, &n_words, &i);
	if (!res)
		return (0);
	while (i < n_words)
	{
		s = skip_spaces(s, c);
		wl = word_len(s, c);
		res[i] = malloc(wl + 1);
		if (!res[i])
			exit(errno);
		ft_strlcpy(res[i++], s, wl + 1);
		s = skip_word(s, c);
	}
	return (res);
}
