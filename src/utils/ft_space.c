/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:19:50 by clovell           #+#    #+#             */
/*   Updated: 2023/10/05 14:10:01 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	int	is;

	is = c == ' ' || c == '\t' || c == '\v';
	is = is || c == '\r' || c == '\f';
	return (is);
}

int	ft_isalnum(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}
