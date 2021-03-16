#include "includes/minishell.h"
void get_external_env(char **envs, t_hash_map *env)
{
    char **temp;

    while (*envs)
    {
        temp = ft_split(*envs, '=');
        set_value(temp[0], temp[1], env);
        free_array((void**)temp);
        envs++;
    }
}
void print(char **tab)
{
    while (*tab)
    {
        printf("%s\n", *tab);
        tab++;
    } 
}
int main(int a, char *args[], char **envs)
{
    t_hash_map *env;

    env = init_hash_map(10);
    set_value("hello", NULL, env);
    get_external_env(envs, env);
    return (0);

}