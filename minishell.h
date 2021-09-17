
#ifndef MINISHELL_H
# define MINISHELL_H


typedef struct		s_env
{
	char			*var;		// var name exemple : PATH
	struct s_env	*next;
}					t_env;

#endif