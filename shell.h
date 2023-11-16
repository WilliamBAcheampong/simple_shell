#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/* 1 if using system getline() */
#define USE_GETLINE 0u
#define USE_STRTOK 0

/* for cmd chaining */
#define MY_COMMAND_NORM    0
#define MY_COMMAND_OR      1
#define MY_COMMAND_AND     2
#define MY_COMMAND_CHAIN   3

/* for write, read or write buffers */
#define MY_READ_BUFFER_SIZE	1024
#define MY_WRITE_BUFFER_SIZE	1024
#define MY_BUFFER_FLUSH		-1

#define MY_HISTORY_FILE    ".My custom shell history"
#define MY_HISTORY_MAX     5037

/* for _convertingnumber() */
#define TO_LOWCASE    1
#define TO_UNSIGNED        2


extern char **environ;

/**
 * struct my_list_string - Singly linked list.
 * @numb: the number field
 * @str: a string
 * @nextn: points to the next node
 */
typedef struct my_list_string
{
int numb;
char *str;
struct my_list_string *nextn;
}
list_t;

/**
 * struct passpseudoarginfo - pseudo-arguments container
* @path: current command for string path
  * @argv: array of strings gotten from arg
* @argc: arg counter
* @status: last executed command’s return status
 * @errline_cnt: counter for errors
 * @err_number: exit()s errorcode
* @linecnt_flag: linecount flag
* @cmd_buffer: cmd_buffer address pointer
*@fname: filename for the program
 * @env: linked- list for copy of environment
 * @history: node for history
* @readfd: line input is read from this
* @alias: node for alias
*@environ: environment
* @arg: string gotten from getline which contains arguments
* @env_change: this is active for environment change
* @cmd_buffer_type: type of cmd
* @history_cnt: line number count for history
 */
typedef struct passpseudoarginfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int errline_cnt;
int err_number;
int linecnt_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_change;
int status;

char **cmd_buffer; /* pointer to chain buffer,cmd ; memory management */
int cmd_buffer_type; /* CMD_type ||, &&, ; */
int readfd;
int history_cnt;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - builtin string and its function container
* @funct: this is the function
 * @type: command flag of builtin
 */
typedef struct builtin
{
char *type;
int (*funct)(info_t *);
} builtin_table;

/********* my_loop_code.c *****/
int look_for_builtin(info_t *);
int hshell(info_t*, char **);
void getcmd(info_t *);
void fork_cmd(info_t *);




/**** my_loop_hshell.c *******/
int my_loop_hshell(char **);



/****** acterrors_code.c **********/
int _myputchar(char);
void _myputs(char *);
int _my_putfd(char c, int fd);
int _my_putsfd(char *str, int fd);

/***** willeststring1_code.c*************/
char *my_strdup(const char *);
char *_strcpy(char *, char *);
int my_putchar(char);
void _willputs(char *);




/************** exit_code.c****/
char *my_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *my_strncat(char *, char *, int);

/********* my_string.c ***/
int _strcmp(char *, char *);
char *my_starts_with(const char *, const char *);
char *my_strcat(char *, char *);
int my_strlen(char *);



/*** my_tokenmaker_code.c *********/
char **my_strtow(char *, char *);
char **my_strtow1(char *, char);


/**** willest_inbuilt_code.c *****/
int my_help(info_t *);
int my_mcd(info_t *);
int my_exit(info_t *);

/**** est_parser_code.c *******/
char *my_dupli_chars(char *, int, int);
int my_is_cmd(info_t*, char *);
char *_get_path(info_t*, char *, char *);



/***  willest_reallocation_code.c */
void *_realloc(void *, unsigned int, unsigned int);
void my_jfree(char **);
char *my_setmemory(char *, char, unsigned int);



/******* mem_code.c ****/
int my_dfree(void **);



/********** estee_err.c ***/
void delete_comment(char *);
int e_atoi(char *);
char *my_change_num(long int, int, int);
int my_print_p(int, int);
void error_print(info_t *, char *);




/****** my_atoi.c***/
int wi_atoi(char *);
int is_delimiter(char, char *);
int my_omega(int);
int my_interactive(info_t *);




/***** inbuiltb_code.c ************/
int _ouralias(info_t *);
int my_history(info_t *);

/**** _getline.c***/
ssize_t my_get_input(info_t *);
int _my_getline(info_t*, char **, size_t *);
void handle_sigint(int);

/********** _get_info.c ******/
void my_free_info(info_t *, int);
void my_remove_info(info_t *);
void my_info_intialise(info_t*, char **);


/******** environment.c ***/
char *_getenv(info_t *, const char *);
int _oursetenv(info_t *);
int _ourenv(info_t *);
int my_fill_env_list(info_t *);
int _myunsetenv(info_t *);


/* _getenviron.c ****/
char **my_get_environ(info_t *);
int my_unsetenv(info_t *, char *);
int my_setenv(info_t *, char *, char *);



/*** our_history_code.c **********/
char *my_get_history_file(info_t *info);
int _history_write(info_t *info);
int historyBuild_list(info_t *info, char *buf, int linecnt);
int my_history_read(info_t *info);
int my_hist_reassign(info_t *info);


/********** ourshell_vars_code.c ***/
int ischain(info_t *, char *, size_t *);
int my_var_change(info_t *);
int change_alias(info_t *);
void my_check_chain(info_t *, char *, size_t *, size_t, size_t);
int my_str_change(char **, char *);




/* mylists_code.c */
size_t my_string_list_print(const list_t *);
list_t *add_end_node(list_t **, const char *, int);
int remove_index_node(list_t **, unsigned int);
void my_free_list(list_t **);
list_t *my_nodeAddition(list_t **, const char *, int);


/**** ourlists1.c ***********/
size_t list_print(const list_t *);
list_t *node_start(list_t *, char *, char);
char **tostr_list(list_t *);
ssize_t get_indexOf_node(list_t *, list_t *);
size_t len_ofList(const list_t *);



#endif
