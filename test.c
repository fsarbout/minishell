#include "includes/minishell.h"

int main()
{
    t_list *lst;

    lst = NULL;
    ft_lstadd_front(&lst, ft_lstnew(all_char('h')));
    ft_lstadd_front(&lst, ft_lstnew(all_char('a')));
    ft_lstdelone(&lst, free);
    ft_lstdelone(&lst, free);
    ft_lstiter(lst, just_print, 0);
    return (0);
}