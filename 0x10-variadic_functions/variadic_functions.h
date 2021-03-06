#ifndef VARIADIC_FUNCTIONS_H
#define VARIADIC_FUNCTIONS_H
#include <stdio.h>
#include <stdarg.h>
/**
 * struct ops - struct for va_list functions
 * @ch: char
 * @ptr: function ptr type void
 *
 */
typedef struct ops
{
	char *ch;
	void (*ptr)(va_list);
} op_t;

void print_all(const char * const format, ...);
void print_strings(const char *separator, const unsigned int n, ...);
int sum_them_all(const unsigned int n, ...);
void print_numbers(const char *separator, const unsigned int n, ...);

#endif
