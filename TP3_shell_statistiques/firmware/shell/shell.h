/*
 * shell.h
 *
 *  Created on: 7 juin 2019
 *      Author: laurent
 */

#ifndef INC_LIB_SHELL_SHELL_H_
#define INC_LIB_SHELL_SHELL_H_

#include <stdint.h>
#include "cmsis_os.h"

#define ARGC_MAX 8
#define BUFFER_SIZE 40
#define SHELL_FUNC_LIST_MAX_SIZE 64

#define STACK_DEPTH	500

struct h_shell_struct;

typedef uint8_t (* drv_shell_transmit_t)(char * pData, uint16_t size);
typedef uint8_t (* drv_shell_receive_t)(char * pData, uint16_t size);


typedef struct{
	char c;
	int (* func)(struct h_shell_struct* shell, int argc, char ** argv);
	char * description;
} shell_func_t;

typedef struct drv_shell_struct
{
	drv_shell_transmit_t transmit;
	drv_shell_receive_t receive;
} drv_shell_t;


typedef struct h_shell_struct{
	int shell_func_list_size;
	char print_buffer[BUFFER_SIZE];

	shell_func_t shell_func_list[SHELL_FUNC_LIST_MAX_SIZE];
	drv_shell_t	 uart;

	BaseType_t xReturned;
	TaskHandle_t shellTaskHandler;
}h_shell_t;



void shell_init(h_shell_t* shell);
int shell_add(h_shell_t* shell, char c, int (* pfunc)(h_shell_t* shell, int argc, char ** argv), char * description);
int shell_run(h_shell_t* shell);
void shell_start(h_shell_t* shell);
char uart_read(h_shell_t* shell);

#endif /* INC_LIB_SHELL_SHELL_H_ */
