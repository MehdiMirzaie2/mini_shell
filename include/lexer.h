/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 23:34:10 by clovell           #+#    #+#             */
/*   Updated: 2023/10/05 14:25:21 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft_extra.h"
# include "standard.h"

typedef struct s_token	t_token;
typedef enum e_ttoken	t_ttoken;

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

/*** token_debug.c ***/
size_t		get_token_index(t_ttoken t);
char		*get_token_desc(t_ttoken t, int tostring);
void		tlst_print(t_token *start);

/*** lexer.c ***/

/* Given a string command returns a t_token linked list.
 * Each token contains a char* to the start of the token within `str`
 * Use tlst_dup_pass to convert the char* to unique string tokens
 */
t_token		*tlst_create(char *str);

/* Advances the string used by the lexer in certain ways:
 * For a quoted sequence it will advance until the end of a quoted sequence.
 * Otherwise it will advanced till the end of the current word.
 * (ie First occurance of `isspace`)
 */
char		*tokstr_advance(char *str, char c, bool quoted);

/* Converts tokens' string into proper groups
 *
 * Given a token linked list this function will convert the char* `str`'s
 * into proper extracted strings.
 *
 * For example given a token linked list made with
 * "echo hello 123"
 * Results in a linked list of
 * "echo hello 123" -> "hello 123" -> "123"
 * After passing that tlst to -tlst_dup_pass it will become
 * "echo" -> "hello" -> "123"
 */
t_token		*tlst_dup_pass(t_token *head);

/* Strdupctx function and other uses.
 *
 * Given the begining of a string `str`,
 * and as i iterates from 0 to strlen(str),
 * it will eventually return 2 for the end of an argument.
 *
 * For strings that don't have quotes in them or around, it will:
 * Return 2 when the end of the word is encountered.
 * For more advances strings with quotes:
 * Only return 2 if it reaches \0 or:
 * if it's not in a quote region and encounters an isspace char
 *
 * Quote Regions:
 * A quote region becomes active when str[i] see's a quote (' or ") and
 *  wasn't already in a quote region.
 * A quote region becomes in-active when str[i] see's same quote character type
 * that begun the a quote reigon
 *
 * Quote regions are tracked by the strdupctx context varaible, as a char[2].
 * context[0(check == false)] for dup mode (copies characters)
 * context[1(check == true)] for check mode (counts characters)
 * examples:
 * QR QuoteRegion
 * NQE Non-QuoteRegion
 * "<QR>'<QR>'"<NQR>'<QQ>"<QR>"'<NQ>
 *
 * Primarily used for `ft_strdupctx`
 * but could be used manually to say advanced a string to the next arg.
 */
t_sd_stat	sd_until_arg_end(char *str, int i, bool check, void *pctx);

/*** lexer_utils.c ***/
/* Returns true if the lexer should increment the string.
 * Such as when beginning a quoted sequence or
 * there are 2 char wide operators (<< >> && || etc)
 */
bool		istok_advancable(t_ttoken tok);

/* Returns the ttoken associated with the
 * first symbols sequence of a string
 */
t_ttoken	get_ttoken(char *str);

void		*tlst_destroy(t_token *token);
t_token		*tlst_token_new(char *str, t_ttoken type, t_token *parent);

#endif
