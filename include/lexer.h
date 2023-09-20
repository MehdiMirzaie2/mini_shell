/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 23:34:10 by clovell           #+#    #+#             */
/*   Updated: 2023/09/16 02:53:50 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "standard.h"

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token t_token;
typedef enum e_ttoken t_ttoken;

/*
 *	E_TTNA: Not applicable (no token)
 *	E_TTDQ: Double Quote Word
 *	E-TTSQ: Single Quote Word
 *	E_TTLA: Left Arrow (Stdin redirect)
 *	E_TTRA: Right Arrow (Stdout redirect)
 *	E_TTLLA: Double Left Arrow (Heredoc redirect)
 *	E_TTRRA: Double Right Arrorw (Stdout Append redirect)
 *	E_WD: Word
 *	E_TTNCP: Next command pipe (Stdout to Stdin)
 *	E_TTNCA: Next comamnd and (Exectute next command if first success)
 *	E_TTNCO: next command or (Execute next command if first failed)
 *	E_TTGS: Grouped Sequence, Either Single or Double Quote.
 *	E_TTLR: Left or Right, Either LA, RA, LLA or RRA.
 *	E_TTWG: Word Group, Either WD or GS.
 *	E_TTNC: Next command, Either P or OR or AND
 *
 *	IMPLEMENTATION NOTES:
 *	This struct is not a bitfield/flags.
 *
 *	But it is using some concepts from bitfields.
 *	The E_TTLR (redirects) are the first because we use,
 *	pointer function array maps, having them first means that at most
 *	the array maps will be at least 4 in size, if we move them downer further
 *	all the elements above them will also have to exist in the array, even when
 *	they would never be mapped.
 */
enum e_ttoken
{
	E_TTNA = 0, 
	E_TTLA = 0x1,
	E_TTRA = 0x2,
	E_TTLLA = 0x3,
	E_TTRRA = 0x4,
	E_TTDQ = 1 << 3,
	E_TTSQ = 1 << 4,
	E_TTWD = 1 << 5,
	E_TTNCP = 1 << 6,
	E_TTNCA = 1 << 7,
	E_TTNCO = 1 << 8,
	E_TTLR = E_TTLA | E_TTRA | E_TTLLA | E_TTRRA,
	E_TTGS = E_TTDQ | E_TTSQ,
	E_TTWG = E_TTGS | E_TTWD,
	E_TTNC = E_TTNCO | E_TTNCP | E_TTNCA
};

/* Represents a fundamental unit of a/many command/s.
 *
 * type:	The type that this token represents, see e_ttoken.
 *
 * str:	The start of the string that is linked with this token.
 * 		if 'dup' is false this string may overlap other tokens.
 * 
 * dup:	true when str is a filtered copy of the input.
 * 		false when str is just the pointer inside the input.
 *
 * next:	The next token in the list.
 */
struct s_token
{
	t_ttoken	type;
	char		*str;
	bool		dup;

	t_token		*next;
};

/* token.c */



/* token_debug.c */
size_t	get_token_index(t_ttoken t);
char	*get_token_desc(t_ttoken t, int tostring);
void	tlst_print(t_token *start);

/* lexer.c */
void	*tlst_destroy(t_token *token);
t_token	*tlst_dup_pass(t_token *head);
t_token	*tlst_token_new(char *str, t_ttoken type, t_token *parent);
t_token	*tlst_create(char *str);

/* lexer_utils.c */
/* Returns true if the lexer should increment the string.
 * Such as when beginning a quoted sequence or 
 * there are 2 char wide operators (<< >> && || etc)
 */
bool		istok_advancable(t_ttoken tok);

/* Returns the ttoken associated with the 
 * first symbols sequence of a string 
 */
t_ttoken	get_ttoken(char *str);

/* Advances the string used by the lexer in certain ways:
 * For a quoted sequence it will advance until the end of a quoted sequence.
 * Otherwise it will advanced till the end of the current word.
 * (ie First occurance of `isspace`)
 */
char	*tokstr_advance(char *str, char c, bool quoted);
#endif
