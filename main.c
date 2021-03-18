#include "includes/minishell.h"

int	main (int argc, char *argv[], char **envs)
{
	char		*line;
	t_hash_map	*env;
	int			i;

	i = 1;
	env = init_hash_map(30);
	get_external_env(envs, env);
	ignore_signals();
	// int fd = open("test.txt", O_RDONLY);
	while (i > 0)
	{
		print_shell();
		i = get_next_line(STDIN_FILENO, &line);
		if (line[0])
			process_line(line, env);
		free(line);
	}
	free_hash_map(env);
	return (0);
}

void	prints(void *str)
{
	printf("%s|\n", ((t_redx*)str)->file);
}

void	printss(void *str)
{
	printf("%s\n", (char*)str);
}

void	print_command(t_command commands, t_hash_map *env)
{
	ft_lstiter(commands.args, &printss);
	printf("in file: ");
	ft_lstiter(commands.in_redx, &prints);
	printf("\nout file: ");
	ft_lstiter(commands.out_redx, &prints);
	printf("---------------------------------------\n");
}

void	print_shell(void)
{
	ft_putstr_fd(BGRN, STDOUT_FILENO);
	// ft_putstr_fd("my_shell>", STDOUT_FILENO);
	ft_putstr_fd("minishell😎$", STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
}
