/******************************************************************************
* Filename              :   freertos.c
* Author                :   Giulio Dalla Vecchia
* Origin Date           :   9 apr 2021
*
* THIS SOFTWARE IS PROVIDED BY EAS ELETTRONICA "AS IS" AND ANY EXPRESSED
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL EAS ELETTRONICA OR ITS CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/

/** @file freertos.c
 *  @brief This is the source file for doxygen comments function
 */

/*****************************************************************************
* Includes
******************************************************************************/
#include <stdio.h>
#include "FreeRTOS.h"
#include "project_settings.h"
#include "task.h"

/*****************************************************************************
* Module Preprocessor Constants
******************************************************************************/

#define IDLE_STACK_SIZE ((uint32_t)128U * sizeof(StackType_t))

/*****************************************************************************
* Module Preprocessor Macros
******************************************************************************/

/*****************************************************************************
* Module Typedefs
******************************************************************************/

/*****************************************************************************
* Function Prototypes
******************************************************************************/

/* Hook prototypes */
void vApplicationStackOverflowHook(struct tskTaskControlBlock* xTask, char* pcTaskName);
void vApplicationMallocFailedHook(void);

/*****************************************************************************
* Module Variable Definitions
******************************************************************************/

/*****************************************************************************
* Function Definitions
******************************************************************************/

/**
 *
 * @param xTask
 * @param pcTaskName
 */
void
vApplicationStackOverflowHook(struct tskTaskControlBlock* xTask, char* pcTaskName) {
    (void)xTask;

#ifdef DEBUG
    printf("STACK OVERFLOW ON TASK %s\r\n", pcTaskName);
    while (1) {};
#else
    HAL_NVIC_SystemReset();
#endif
    /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}

/**
 *
 */
void
vApplicationMallocFailedHook(void) {
#ifdef DEBUG
    printf("MALLOC FAIL! \r\n");
    while (1) {};
#else
    HAL_NVIC_SystemReset();
#endif
    /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}

/**
 * Funzione per allocare in modo statico la memoria necessaria al IDLE task
 */
void
vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer, StackType_t** ppxIdleTaskStackBuffer,
                              uint32_t* pulIdleTaskStackSize) {
    static StaticTask_t task_tcb;
    static StackType_t task_stack[IDLE_STACK_SIZE];

    *ppxIdleTaskTCBBuffer = &task_tcb;
    *ppxIdleTaskStackBuffer = &task_stack[0];
    *pulIdleTaskStackSize = IDLE_STACK_SIZE;
}

/**
 * Funzione richiamata dal RTOS ad ogni tick (systick)
 */
void
vApplicationTickHook(void) {
#ifdef USE_EDF_FRAMEWORK
    edf_tick_FromISR();
#endif
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
