/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:27:45 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/17 19:32:38 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_valide_key(char *str)
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

int change_dir(t_command command, char **path, char **old_path,t_hash_map *env)
{
    char *temp;

    
    if (command.args->next)
    {
        temp =(char*) command.args->next->content;
        if (!strcmp(temp,"-"))
            *path = get_value("OLDPWD", env);
        else
        {
            if (temp[0]== '~')
                *path = ft_strjoin("/Users/htagrour", temp + 1);
            else
                *path = ft_strdup(temp);
        }
    }
    else
        *path = ft_strdup("/Users/htagrour");
    *old_path = getcwd(NULL, 1024); 
    if (chdir(*path) != 0)
        return (print_error("PATH not exist or a file", 1, env));
    return (0);
}
int cd(t_command command, t_hash_map *env)
{
    char *path;
    char *old_path;
    
    if (!change_dir(command, &path, &old_path, env))
    {
        set_value("OLDPWD", old_path, env);
        set_value("PWD", path, env);
    }
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

int  add_env(char *str, t_hash_map *env)
{
    char *key;
    int i = 0;
    int index;
    char *value;

    index = ft_strchr_eql(str , '=');
    key = ft_substr(str, 0, index);
    if (!is_valide_key(key))
    {
        free(key);
        return (print_error("not a valide identifier", 1, env));
    }
    if (str[index] != '=')
        set_value(key, NULL, env);
    else
        set_value(key, str + index + 1, env);
    free(key);
    return (0);
}

int print_env(t_hash_map *env)
{
    char *value;
    int i = 0;
    char **keys;

        keys = sorted_key(env);
        while (keys[i])
        {
            ft_putendl_fd("declare -x ", STDOUT_FILENO, 0);
            ft_putendl_fd(keys[i], STDOUT_FILENO, 0);
            value = get_value(keys[i], env);
            if (value)
            {   
                ft_putendl_fd("=\"", STDOUT_FILENO , 0);
                ft_putendl_fd(value, STDOUT_FILENO , 0);
                ft_putchar_fd('\"', STDOUT_FILENO);
                free(value);
            }
            ft_putchar_fd('\n', STDOUT_FILENO);
            i++;
        }
        free_array((void**)keys);
    return (0);
}

int     export(t_command command, t_hash_map *env)
{
    char **str;
    t_list *temp;
    
    temp = command.args->next;
    if (!temp)
        return (print_env(env));
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
    char *key;

    temp = command.args->next;
    while (temp)
    {   key = (char*)temp->content;
        if (is_valide_key(key))
            delet_value(key, env);
        else
            print_error("not valide identifier", 1, env);
        temp = temp->next;
    }
    return (0);
}

int echo(char **args)
{
    // echo '' >file \" >foile2 echo souad "hana"souad
    //echo "" "" '' '' '' "" '' "" hamza|cat -e
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

int built_in1(t_command command, t_hash_map *env, int flag)
{
    char *cmd;
    int res;
    int out_fd;

    out_fd = STDOUT_FILENO;
    cmd = (char*)command.args->content;
    if (cmd && (res = is_buitin1(cmd)) == -1)
            return (-1);
    if (flag)
        if (get_in_fd(command, &out_fd)|| get_out_fd(command, &out_fd))
            return(print_error("FIle ERROR", 1,env));
    if(res == 1)
        return (cd(command, env));
    if (res == 2)
        return (export(command, env));
    if (res == 3)
        return (unset(command, env));
    if (res == 4)
        return (exit_(command, env));
    return (-1);
}

int built_in2(char **args, t_hash_map *envs)
{
    int res;
    
    res = -1;
    if (!strcmp(*args,"echo"))
        res = echo(args);
    if (!strcmp(*args, "pwd"))
        res = pwd();
    if (!strcmp(*args, "env"))
        res = env(args, envs);
    return (res);
}
