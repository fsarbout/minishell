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
        write(1,"\r", 1);
        tputs(tgetstr("ce", NULL), 1,put_char);
        print_shell();
        ft_lstiter(current, just_print, 0);
}