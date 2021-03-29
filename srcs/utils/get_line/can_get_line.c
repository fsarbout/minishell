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
    termios_new.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_new);
    temp = malloc(sizeof(char)* 4);
    i = read(fd, temp, 4);
    temp[i] = 0;
    *c = str_to_int(temp);
    free(temp);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_backup);
    return (i);
}

void arrow_up(t_list **hist)
{

    if (*hist)
    {
        write(1,"\r", 1);
        tputs(tgetstr("ce", NULL), 1,put_char);
        print_shell();
        if ((*hist)->content)
            ft_putendl_fd((char*)(*hist)->content, STDOUT_FILENO,0);
        if ((*hist)->next)
            *hist = (*hist)->next;
    }
}

void arrow_down(t_list **hist)
{
    if (*hist)
    {
        print_shell();
        if ((*hist)->content)
            ft_putendl_fd((char*)(*hist)->content, STDOUT_FILENO,0);
        if ((*hist)->prev)
            *hist = (*hist)->prev;
    }
}


int get_line(char **line, int fd, t_list *hist)
{
    int c;
    t_list *current;
    t_list *tem;
    int i;

    current = NULL;
    while (1)
    {
        i = ft_get_char(&c, fd);
        if (c == '\n')
            break;
        if (c >= 32 && c < 127)
            ft_lstadd_front(&current, ft_lstnew(all_char(c)));
        if (c == CTR_D && !**line)
            i = 0;
        if (c == ARROW_UP)
            arrow_up(&hist);
        if (c == ARROW_DOWN)
            arrow_down(&hist);
        if (c == DELETE)
            ft_lstdelone(&current, free);
        refresh(current);
    }
    ft_lstclear(&current, free);
    return (i);
}