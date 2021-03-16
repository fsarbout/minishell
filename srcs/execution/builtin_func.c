/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:27:45 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/16 12:56:01 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_valide_var(char *str)
{   
    if (!ft_isalpha(*str))
        return (0);
    str++;
    while (*str)
    {
        if (!(ft_isalnum(*str)) && *str != '_')
            return 0;
        str++;
    }
    return 1;
}

int is_valide_exit(char *str)
{
    if (*str== '+' || *str == '-')
        str++;
    while (*str)
    {
        if (!ft_isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}

int cd(t_command command, t_hash_map *env)
{
    char *temp;
    char *path;
    char *old_path;
    
    old_path = getcwd(NULL, 1024);
    if (command.args->next)
    {
        temp =(char*) command.args->next->content;
        if (temp[0]== '~')
            path = ft_strjoin("/home/htagrour", temp + 1);
        else
            path = ft_strdup(temp);
    }
    else
        path = ft_strdup("/home/htagrour");
    if (chdir(path) != 0)
        return (print_error("PATH not exist or a file", 1, env));
    set_value("OLDPWD", old_path, env);
    set_value("PWD", path, env);
    free(path);
    free(old_path);
    return (0);
}

int pwd()
{
    char *current_path;
    
    current_path = getcwd(NULL, 1024);
    ft_putendl_fd(current_path, STDOUT_FILENO, 1);
    free(current_path);
    return (0);
}

void add_env(char *str, t_hash_map *env)
{
    char *key;
    int i = 0;
    int k = ft_strlen(str);
    char *value;

    if (!ft_isalpha(*str) && *str != '_')
        print_error("not valide identifier", 1, env);
    if (!ft_strchr_eql(str , '='))
        set_value(str, 0, env);
    else
    {
        while (str[i])
        {
            if (!(ft_isalnum(str[i]) || str[i] == '_' || str[i] == '='))
                print_error("not valide identifier", 1, env);
            if (str[i] == '=')
            {
                key = ft_substr(str, 0 , i);
                value = ft_substr(str , i + 1, k - i);
                set_value(key, value, env);
                free(key);
                free(value);
            }
            i++;
        }
    }
}

int     export(t_command command, t_hash_map *env)
{
    char **str;
    t_list *temp;
    char **keys;
    int i = 0;
    char *value;
    
    temp = command.args->next;
    if (!temp)
    {
        keys = sorted_key(env);
        while (keys[i])
        {
            ft_putendl_fd("declare -x ", STDOUT_FILENO, 0);
            ft_putendl_fd(keys[i], STDOUT_FILENO, 0);
            value = get_value(keys[i], env);
            ft_putendl_fd("=\"", STDOUT_FILENO , 0);
            ft_putendl_fd(value, STDOUT_FILENO , 0);
            ft_putendl_fd("\"", STDOUT_FILENO , 1);
            free(value);
            i++;
        }
        //free_array((void**)envs);
        return (0);
    }
    while (temp)
    {
        add_env((char *)temp->content, env);
        temp = temp->next;
    }
    return (0);
}

int unset(t_command command, t_hash_map *env)
{
    t_list *temp;
    char *str;

    temp = command.args->next;
    while (temp)
    {   str = (char*)temp->content;
        if (is_valide_var(str))
            delet_value(str, env);
        else
            print_error("not valide identifier", 1, env);
        temp = temp->next;
    }
    return (0);
}

int echo(char **args)
{
    int flag;
   
    flag = 0;
    args++;
    if (*args)
    {
        echo_check_n(args, &flag);      
        if (flag)
            args += flag;
        while (*args)
        {
            ft_putstr_fd(*args, STDOUT_FILENO);
            if (*(args + 1))
                ft_putstr_fd(" ", STDOUT_FILENO);
            args++;
        }
    }
    if (!flag)
        ft_putstr_fd("\n", STDOUT_FILENO);
    return (0);
}

int env(char **args, t_hash_map *env)
{
    args++;
    char **envs;
    int i;

    if (!*args)
    {
        envs = hash_to_arr(env, 0);
	    i = -1;
        while(envs[++i])
            if (*envs[i])
                ft_putendl_fd(envs[i], STDOUT_FILENO, 1);
        free_array((void**)envs);
        return (0);
    }
    else
        return(print_error("env don't accept args", 1, env));
}

int exit_(t_command cmd, t_hash_map *env)
{
    t_list *temp;
    int exit_number;
    
    temp = cmd.args->next;
    if (!temp)
        exit(ft_atoi(get_value("?", env)));
    if (temp->next)
        return (print_error("exit: too many arguments", 1, env));
    if (!is_valide_exit((char*)temp->content))
        exit(print_error("exit: numeric argument required", 255, env));
    exit(ft_atoi((char*)temp->content));
    return (0);
}

int built_in1(t_command command, t_hash_map *env)
{
    char *cmd;
    int res;

    res = -1;
    cmd = (char*)command.args->content;
    if(!strcmp("cd", cmd))
        res = cd(command, env);
    if (!strcmp("unset", cmd))
        res = unset(command, env);
    if (!strcmp("export", cmd))
        res = export(command, env);
    if (!strcmp("exit", cmd))
        res = exit_(command, env);
    return (res);    
}
int built_in2(char **args, t_hash_map *envs)
{
    int res;
    
    res = 1;
    if (!strcmp(*args,"echo"))
        res = echo(args);
    if (!strcmp(*args, "pwd"))
        res = pwd();
    if (!strcmp(*args, "env"))
        res = env(args, envs);
    return (res);
}
