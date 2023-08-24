#include "shell.h"

void	ft_cd(const char *path, t_env *our_env)
{
	t_env	*ref;
	t_env	*ref2;

	ref = our_env;
	if (chdir(path) != 0){
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
	}
	while (!ft_strncmp(ref->name, "PWD", 3))
		ref = ref->next;
	while (!ft_strncmp(ref2->name, "PWD", 3))
		ref2 = ref2->next;
	free(ref2->args);
	ref2->args = ref->args;
	ref->args = ft_strdup(getenv("PWD"));
}
