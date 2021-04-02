#include "get_next_line.h"

char *all_char(int c)
{
    char *ptr;

    ptr = malloc(1);
    *ptr = c;
    return (ptr);
}

int put_char(int i)
{
    write(1, &i, sizeof(int));
    return (0);
}

void just_print(void *content)
{
    char *str;

    str = (char*)content;
    if (str)
        ft_putchar_fd(*str, STDOUT_FILENO);
}

void refresh(t_list *current)
{
    char *temp;

    if (current)
    {
        temp = (char*)current->content;
        if (temp)
        {
            write(1,"\r", 1);
            tputs(tgetstr("ce", NULL), 1,put_char);
            if (ft_strlen(temp) + 12 >= tgetnum("co"))
                ft_putchar_fd('\n', STDIN_FILENO);
            else
                print_shell();
            ft_putstr_fd(temp, STDOUT_FILENO);
        }
    }
}