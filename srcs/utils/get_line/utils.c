#include "get_next_line.h"

int put_char(int i)
{
    
    write(STDOUT_FILENO, &i, sizeof(int));
    return (0);
}

void just_print(char *line)
{
    int len;

    len = 13;
    while (*line)
    {
        // if (len >= tgetnum("co"))
        // {
        //     ft_putchar_fd('\n', STDOUT_FILENO);
        //     len = -1;
        // }
        ft_putchar_fd(*line, STDOUT_FILENO);
        line++;
        len++;
    }
}

void refresh(t_list *current)
{
    char *temp;
    

    if (current)
    {
        temp = (char*)current->content;
        if (temp)
        {
            tputs(tgetstr("rc",NULL ), 1, put_char);
            write(1,"\r", 1);
            tputs(tgetstr("cd", NULL), 1,put_char);
            print_shell();
            ft_putstr_fd(temp, STDOUT_FILENO);
        }
    }
}