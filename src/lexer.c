typedef struct s_lexeme t_lexeme;
typedef struct s_str	t_str;

struct s_lexeme
{
	char *str;
	t_lexeme *next;
};

/* string text region */
struct s_stregion
{
	char	*line;
	int		end;
	int		start;
}

struct s_str
{
	char *str;
	int	len;
};

static t_str tstrcpyc(char *line, char c)
{
	t_str str;

	str.len = 0;
	while (line[str.len] != c && line[str.len])
		str.len++;
	str.str = calloc(sizeof(char), str.len + 1);
	strlcpy(str.str, line, str.len);
	return (str);
}

/* t_str copy region */
static t_str tstrcpyr(char *line, char c)
{
	t_str str;

	str.len = 0;
	if (c == '(')
		c = ')';
	else if (c == '{')
		c == 
	if (isspace(c))
	{
		while (isspace(line[str.len]) && line[str.len])
			str.len++;
	}
	else
	{
		while (line[str.len] != c && line[str.len])
			str.len++;
	}
	str.str = calloc(sizeof(char), str.len + 1);
	strlcpy(str.str, line, str.len);
	return (str);
}

static char	getendc(char c)
{
	if (c == '(')
		c = ')';
	else if (c == '{')
		c = '}';
	else if (c == '[')
		c = ']';
	return (o);
}

static void	start_region(char **str)
{
	while (isspace(**str) || **str)
		*str++;
	reg->start = i;
}

static t_str copy_region(char *str)
{
	const char	start = *str;
	char		end;
 	int			depth;
	t_stregion	reg;

	region.str = str;
	depth = 0;
	while (*str)
	{
		
		str++;
	}
}

static t_str tstrcpyw(char *line, char c)
{
	t_str str;
	
	str.len = 0;
	while (!isspace(line[str.len]) && line[str.len])
		str.len++;
	str.str = calloc(sizeof(char), str.len + 1);
	strlcpy(str.str, line, str.len);
	return (str);
}


void	*destroy_lexeme(t_lexeme *lexeme)
{
	if (lexeme == NULL)
		return (NULL);
	destroy_lexeme(lexeme->next);
	free(lexeme);
	return (NULL);
}

/* Lexer states:
 *
 * E_NS -- No state
 * E_SQ -- Single quote
 * E_DQ -- Double quote
 */

enum e_lexstate
{
	E_NS = 0,
	E_QM = 1,
	E_SQ = 2 | E_QM,
	E_DQ = 4 | E_QM
};

bool try_continue(bool try, int *i, int inc)
{
	*i += inc;
	return (try);
}



t_lexeme *create_lexeme_lst(char *line)
{
	int	i;
	t_lexeme *first;
	t_str recent;
	char	cpynext;

	first = calloc(sizeof(s_lexeme), 1);
	i = 0;
	while (line[i])
	{
		cpynext = '\0';
		if (try_continue(isspace(line[i]), &i, 1))
			continue;
		else if (line[i] == '\'' || line[i] == '\"' || line[i] == '(')
			cpynext = line[i];
		if (cpynext != '\0')
			recent = strcpyr(&line[i + 1], cpynext);
		else
			recent = strcpyr(&line[i + 1]);
		i += recent.len;
	}
	
}
