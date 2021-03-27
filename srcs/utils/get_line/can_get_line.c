#include "get_next_line.h"

int str_to_int(char *str)
{
    int i = 0;

    while(*str)
    {
        i += *str;
        str++;
    }
    return (i);
}

int ft_get_char(int *c, int fd)
{
    int i;
    char *temp;
    struct termios  termios_new;
    struct termios  termios_backup;
    

    ft_bzero(&termios_new, sizeof(struct termios));
    tcgetattr(STDIN_FILENO, &termios_backup);
    termios_new = termios_backup;
    termios_new.c_lflag &= ~(ICANON | ECHO);
    termios_new.c_cc[VMIN] = 1;
    termios_new.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_new);
    temp = malloc(sizeof(char)* 4);
    i = read(fd, temp, 4);
    temp[i] = 0;
    *c = str_to_int(temp);
    free(temp);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_backup);
    return (i);
}

/*
    add delete button
    add historique
*/

int get_line(char **line, int fd)
{
    int c;
    int i = 1;
    char *temp;

    *line = ft_strdup("");
    while (i > 0)
    {
        i = ft_get_char(&c, fd);
        if (c == '\n')
            return (1);

        ft_putchar_fd(c, STDOUT_FILENO);
        if (c >= 32 && c < 127)
        {
            temp = *line;
            *line = ft_add_char(*line, c);
            free(temp);
        }
        if (c == CTR_D && !**line)
            i = 0;
        if (c == ARROW_UP)
            ft_putchar_fd('2', STDOUT_FILENO);
    }
    return (i);
}