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
    temp = malloc(sizeof(char)* 5);
    i = read(fd, temp, 4);
    temp[i] = 0;
    *c = str_to_int(temp);
    free(temp);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_backup);
    return (i);
}

void get_hist(t_list **current, int flag)
{
    if (flag && *current && (*current)->next)
        *current = (*current)->next;
    if (!flag && *current && (*current)->prev)
        *current = (*current)->prev;
}

void change_current(t_list**current, int c, int flag)
{
    char **str;
    char *temp;

    if (*current)
    {
        str = (char **)(&(*current)->content);
        temp = *str;
        if (flag)
            *str = ft_add_char(*str, c);
        else
            if (*str)
                *str = ft_del_char(*str);
        free(temp);
    }
    else
    {
        if (flag)
        {
            temp = ft_strdup(" ");
            temp[0] = c;
            ft_lstadd_front(current, ft_lstnew((void*)temp));
        }
    }
}

void adjust_hist(t_list **hist, char **line)
{

    if (g_var.current->content)
        *line = ft_strdup((char*)g_var.current->content);
    else
        *line = ft_strdup("");
    if (!g_var.current->prev)
    {
        ft_lstclear(hist, free);
        *hist = copy_list(g_var.current);
    }
    else
        ft_lstadd_front(hist, ft_lstnew(ft_strdup(*line)));
}

int get_line(char **line, int fd, t_list **hist)
{
    int c;
    int i;
    
    g_var.current = copy_list(*hist);
    ft_lstadd_front(&g_var.current, ft_lstnew(ft_strdup("")));
    print_shell();
    while (1)
    {
        i = ft_get_char(&c, fd);
        if (c >= 0 && c <= 255)
        {
            if (c == '\n')
                break;
            if (c >= 32 && c < 127)
                change_current(&g_var.current, c, 1);
            if (c == CTR_D && (!g_var.current || 
                            !g_var.current->content ||
                            !*(char*)g_var.current->content))
                return (ft_lstclear(&g_var.current, free));
            if (c == ARROW_UP)
                get_hist(&g_var.current, 1);
            if (c == ARROW_DOWN)
                get_hist(&g_var.current, 0);
            if (c == DELETE)
                change_current(&g_var.current, 0, 0);
        }
        refresh(g_var.current);
    }
    adjust_hist(hist, line);
    ft_lstclear(&g_var.current, free);
    return (1);
}