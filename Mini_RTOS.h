/****************************************************************************************
* ALI SAHBAZ
*
*
* ASOS mini RTOS for TM4C129
*
* Date          : 12.05.2021
* By            : Ali Sahbaz
* e-mail        : ali_sahbaz@outlook.com
*/
#ifndef Mini_RTOS_H
#define Mini_RTOS_H




typedef struct {
    void *sp; 
	
	  char priority; 
	
		char priority_counter;
	
} os_thread_t;

typedef void (*os_thread_handler)(void);

void my_os_init(void);
 
void my_os_scheduleing(void);
 
void my_os_run(void);
 
void os_on_startup(void);

void my_os_thread_start(
    os_thread_t *me,
    os_thread_handler thread_handler,
    void *stk_sto,
		char Priority, 
		unsigned int stkSize);

		
		
		
#endif /* MIROS_H */

