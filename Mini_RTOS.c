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
#include <stdint.h>
#include "main.h"
#include "Mini_RTOS.h"

static os_thread_t * volatile OS_curr;    // suan bulunan threadin pointeri
static  os_thread_t * volatile OS_next;   // siradaki threadin pointeri
static  os_thread_t *OS_thread[32 + 1];   // tanimlanan tasklarin Thread Control Block'lari (yani stack pointer ve priority gibi) bu diziye kaydedilir , suan 32 den fazla thread olusturulamaz
static  uint8_t   OS_threadNum;           // toplam thread sayisi
static  uint8_t   OS_currIdx;             // OS_thread'nin indexi, sira yönetimi için

void my_os_init(void) 
{
	 //  PendSV kesinti önceligini en düsük 0xFF seviyesine ayarlanir
    *(uint32_t volatile *)0xE000ED20 |= (0xFFU << 16);    
}

void my_OS_Scheduleing(void) {

/*********** Threads Kuyruk Yönetimi  ********************/	
    
	  if(OS_curr->priority > 1)
		{
				if(OS_curr->priority_counter <= OS_curr->priority )
				{	
						*(uint32_t volatile *)0xE000ED04 = (1U << 28);  // PendSV-SVCall'yi tetiklenir
				}
				else
				{
						OS_curr->priority_counter = 0;
					
						++OS_currIdx;

						if (OS_currIdx == OS_threadNum) 
						{
								OS_currIdx = 0U;
						}

						OS_next = OS_thread[OS_currIdx];

						if (OS_next != OS_curr) 
						{
								*(uint32_t volatile *)0xE000ED04 = (1U << 28);  // PendSV-SVCall'yi tetiklenir
						}
				}
				
				OS_curr->priority_counter++;
			
		}
		else
		{
			  ++OS_currIdx;
			
				if (OS_currIdx == OS_threadNum) 
				{
						OS_currIdx = 0U;
				}
				
				OS_next = OS_thread[OS_currIdx];
				
				if (OS_next != OS_curr) 
				{
						*(uint32_t volatile *)0xE000ED04 = (1U << 28);  // PendSV-SVCall'yi tetiklenir
				}
		}
	
}

void my_os_run(void) {
  
	// Systick Hardware_Unit'de degilde burada çalismaya baslarsa daha iyi olur ve NVIC_SetPriority(SysTick_IRQn, 0U) önceligi böyle olmali
	
    __disable_irq();
    my_OS_Scheduleing();
    __enable_irq();

	// HATA ; KOD BURAYA ASLA DÜSMEMELI
    
}

/***
my_OS_Thread_Start
- Özet: ilgili taska threadHandler kadar yani örnegin "stack_blinky1[40]" 40 byte yer ayrilir
				'me' struct'i içerisine ilgili taskin ilgili parametreleri kaydedilir.
        stack pointer adresi, priority kaydedilir ve yigin içerisinde siraya alinir.
        "my_OS_Scheduleing" bu sirayi yönetir ve threadler çalisir durumdadir.
***/
void my_OS_Thread_Start(
    os_thread_t *me,
    os_thread_handler thread_handler,
    void *stkSto, 
	  char Priority,
		uint32_t stkSize)
{
    /* 
    * NOT: ARM Cortex-M yigini yüksekten -> düsük bellege gider
    */
    uint32_t *sp = (uint32_t *)((((uint32_t)stkSto + stkSize) / 8) * 8);  // 8 byte yuvarlama
    uint32_t *stk_limit;
    
    *(--sp) = (1U << 24);  /* xPSR */
    *(--sp) = (uint32_t)thread_handler; /* PC */
    *(--sp) = 0x0000000EU; /* LR  */
    *(--sp) = 0x0000000CU; /* R12 */
    *(--sp) = 0x00000003U; /* R3  */
    *(--sp) = 0x00000002U; /* R2  */
    *(--sp) = 0x00000001U; /* R1  */
    *(--sp) = 0x00000000U; /* R0  */
    /* fake registers      R4-R11 */
    *(--sp) = 0x0000000BU; /* R11 */
    *(--sp) = 0x0000000AU; /* R10 */
    *(--sp) = 0x00000009U; /* R9  */
    *(--sp) = 0x00000008U; /* R8  */
    *(--sp) = 0x00000007U; /* R7  */
    *(--sp) = 0x00000006U; /* R6  */
    *(--sp) = 0x00000005U; /* R5  */
    *(--sp) = 0x00000004U; /* R4  */

    /* Kaydedilmesi gereken datalar kaydediliyor */
    me->sp = sp;
    me->priority = Priority;
		me->priority_counter = 1;
		
    // 0xDEADBEEFU Bu debug sirasinda Ram memoriy stackini izlerken nereye neyin yazildigini görmemizde kolaylik sagliyor, yiginin kullanilmayan kismi zaten
    stk_limit = (uint32_t *)(((((uint32_t)stkSto - 1U) / 8) + 1U) * 8);
    for (sp = sp - 1U; sp >= stk_limit; --sp) {
        *sp = 0xDEADBEEFU;     												  }

    //Q_ASSERT(OS_threadNum < Q_DIM(OS_thread)); // hata durumu kontrolü

    // Isletim sistemine ilgili taskin stack registeri kaydediliyor örnegin blinky1 fonksiyon task threadi için 
    OS_thread[OS_threadNum] = me;
    ++OS_threadNum;
}


/**
PendSV_Handler <=> SVCall
- Yazilimsal kesme olusturur
- Kullanim amaci: Örnegin yaptiginiz islem veya kod parçacigi Uart gibi bir kesme tarafindan kesilmesini istemiyorsaniz, Yazilimsal Kesme olan SVCall'u tetikleyip islemleri içinde yapabilirsiniz.
- "my_OS_Scheduleing" fonksiyonu içinde tetiklenmektedir
- SVCall, PendSV_Handler, PendSV interrupt hepsi ayni 
**/
__asm void PendSV_Handler(void) {
	
	  /* extern variable */
    IMPORT  OS_curr  
    IMPORT  OS_next  
   
    /* __disable_irq(); */
    CPSID         I

    /* if (OS_curr != (OSThread *)0) { */ 
    LDR           r1,=OS_curr
    LDR           r1,[r1,#0x00]
    CBZ           r1,PendSV_restore

    /*     push registers r4-r11 on the stack */
    PUSH          {r4-r11}    

    /*     OS_curr->sp = sp; */ 
    LDR           r1,=OS_curr
    LDR           r1,[r1,#0x00]
    STR           sp,[r1,#0x00]
    /* } */

PendSV_restore    
    /* sp = OS_next->sp; */
    LDR           r1,=OS_next
    LDR           r1,[r1,#0x00]
    LDR           sp,[r1,#0x00]

    /* OS_curr = OS_next; */
    LDR           r1,=OS_next
    LDR           r1,[r1,#0x00]
    LDR           r2,=OS_curr
    STR           r1,[r2,#0x00]

    /* pop registers r4-r11 */ 
    POP           {r4-r11}    

    /* __enable_irq(); */
    CPSIE         I

    /* return to the next thread */
    BX            lr    
}
