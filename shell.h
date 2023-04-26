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
int string_to_integer(char *str);
int is_delimiter(char c, char *delimiters);
int is_alphabetic(int c);
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *alias_str);
int print_alias(list_t *node);
int _myalias(info_t *info);
int _myenv(info_t *info);
char *_getenv(info_t *info, const char *name);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _erratoi(char *s);
void print_error(info_t *info, char *estr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);
char *_strncpy(char *destination, const char *source, int num_chars);
char *_strncat(char *destination, const char *source, int max_bytes);
char *_strchr(char *s, char c);
char **get_environ(info_t *info);
int _unsetenv(info_t *info, const char *var);
int _setenv(info_t *info, const char *var, const char *value);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head);
size_t list_len(const list_t *head);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);
int bfree(void **ptr);
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);
char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
int is_interactive_mode(info_t *info);
int is_delimiter(char c, char *delimiters);
int is_alphabetic(int c);
int string_to_integer(char *str);

#endif
