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

void get_hist(t_list **temp, int flag)
{
    if (flag && *temp && (*temp)->next)
        *temp = (*temp)->next;
    if (!flag && *temp && (*temp)-> prev)
        *temp = (*temp)->prev;
}

// void arrow_down(t_list **hist)
// {
//     if (*hist)
//     {
//         print_shell();
//         if ((*hist)->content)
//             ft_putendl_fd((char*)(*hist)->content, STDOUT_FILENO,0);
//         if ((*hist)->prev)
//             *hist = (*hist)->prev;
//     }
// }

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


int get_line(char **line, int fd, t_list **hist)
{
    int c;
    t_list *current;
    t_list *temp;
    int i;

    temp = copy_list(*hist);
    // temp = *hist;
    ft_lstadd_front(&temp, ft_lstnew(ft_strdup("")));
    while (1)
    {
        i = ft_get_char(&c, fd);
        if (c >= 0 && c <= 255)
        {
            if (c == '\n')
                break;
            if (c >= 32 && c < 127)
                change_current(&temp, c, 1);
            if (c == CTR_D && !*(char*)temp->content)
                exit (0);
            if (c == ARROW_UP)
                get_hist(&temp, 1);
            if (c == ARROW_DOWN)
                get_hist(&temp, 0);
            if (c == DELETE)
                change_current(&temp, 0, 0);
            refresh(temp);
        }
    }
    if (temp)
        *line = ft_strdup((char*)temp->content);
    else
        *line = ft_strdup("");
    ft_lstclear(&temp, free);
    return (i);
}