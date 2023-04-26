#ifndef __MAIN__
#define __MAIN__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include "types_defines.h"

/* env.c */
char **init_env(unsigned int empty_slot);
void free_env(void);
unsigned long int get_env_length(char *env[]);
char *_getenv(char *name);
char *_setenv(char *name, char *value, int overwrite);

/* Shell mode helpers */
size_t read_line(char **);
int interactive_mode(void);
int exec_mode(char *args[]);
int pipe_mode(void);
void exit_interactive(void);
void safe_exit(char const *exit_msg, int exit_code);
int exec_from_line(char *readed, int show_errors);
int exec_args(char **args, int show_errors);

/* path.c */
char *_which(char *filename);
StringNode *get_path_list(void);

/* stringA.c */
unsigned int _strlen(char *str);
char *_strtok(char *str, char *delim);
char *_strstr(char *str, char *needle);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);

/* stringB.c */
char *_strncpy(char *dest, char *src, unsigned int n);
StringNode *_strsplit(char *str, char *delim);

/* listsA.c */
StringNode *add_string_node(StringNode **list_head, char *str);
int get_list_length(StringNode *head);
int delete_a_node_at_given_index(StringNode **, unsigned int);
void free_list(StringNode *);
char **array_from_string_list(StringNode *head);

/* listsB.c */
void free_string_array(char **arr);
StringNode *insert_at_index(StringNode **head, unsigned int index, char *data);
size_t display_the_string_of_list(const StringNode *);
size_t print_list_str(StringNode *h);

/*history.c file*/
int change_index_of_history(data_t *data);
int read_history(StringNode *data);
int write_history(data_t *data);
int build_history_list(data_t *data, char *my_buffer, int line_counter);
char *get_history_file(data_t *data);

/*error_handling.c*/
int _puts_char(char ch);
void _string_puts(char *);
char *_duplicate_string(const char *);
int set_my_enviroment(data_t *);
int my_enviroment(data_t *);
int unset_my_enviroment(data_t *);

/*string_handling file*/
char *_copy_string(char *, char *);
int _get_string_length(char *);

/* memory_handling.c*/
void *_reallocation_of_memory(void *, unsigned int, unsigned int);
int free_memory(void **);
char *_set_const_memory(char *, char, unsigned int);
void free_string_of_strings(char **);

/*exits.c*/
char *copy_string(char *, char *, int);
char *_string_concatinate(char *, char *, int);
char *_character_string(char *, char);
char *_num_converter(long int, int, int);
void _comment_handler(char *);


/* environ.c*/

StringNode *node_prefix(StringNode *, char *, char);
char *_getenv_2(data_t *, const char *);

/* variable_handling.c*/

int change_alias(data_t *);

/**info_handling.c*/

void initialize_data(data_t *, char **);

#endif
