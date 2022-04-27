// 내기 전에 삭제 필수!!!!!!!!!!!!

#include "minishell.h"

void	print_test(t_cmd **head)
{
	printf("head : %p\n", *head);
	for (t_cmd *cur = *head; cur != NULL; cur = cur->next)
	{
		printf("command : %s\n", cur->cmd);
		printf("pipe_tyep:%d\n",cur->is_pipe);
		printf("path?:%d\n",cur->is_path);
		printf("prev:%p\n",cur->prev);
		printf("next:%p\n",cur->next);
		printf("argv : %p\n", cur->argv);
		for (char **cur_arg = cur->argv; *cur_arg != NULL; cur_arg++)
			printf("argv : %s\n", *cur_arg);
		printf("input_head : %p\n", cur->input);
		for (t_redir *cur_in = cur->input; cur_in != NULL; cur_in = cur_in->next)
			printf("input : %s\n", cur_in->file_name);
		printf("output_head : %p\n", cur->output);
		for (t_redir *cur_out = cur->output; cur_out != NULL; cur_out = cur_out->next)
			printf("output type:%d : %s\n", cur_out->type, cur_out->file_name);
		printf("heredoc : %s\n", cur->here_filename);
		printf("--------------------\n");
	}
	//system("leaks minishell");
}
