
void	*strlst_destroy(t_strlst **elem)
{
	t_strlst	*curr;
	t_strlst	*next;

	curr = *elem;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr->dup != 0)
			free(curr->str);
		curr->str = NULL;
		free(curr);
		curr = next;
	}
	*elem = NULL;
	return (NULL);
}

t_strlst *strlst_add(char *str, int dup, t_strlst **head)
{
	t_strlst	*next;
	t_strlst	*elem;

	next = *head;
	elem = malloc(sizeof(t_strlst));
	if (elem == NULL)
		return (NULL);
	elem->dup = dup != 0;
	elem->str = str;
	if (dup)
		elem->str = ft_strdup(str);
	if (elem->str == NULL)
		return (strlst_destroy(head));
	while (next != NULL && next->next != NULL)
		next = next->next;
	if (next != NULL)
		next->next = elem;
	return (elem);
}
