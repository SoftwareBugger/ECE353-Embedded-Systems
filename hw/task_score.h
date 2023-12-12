/**
 * @file task_score.h
 * @author Adam Boho, Han Lyu, Dom Valencia
 * @brief 
 * @version 0.1
 * @date 2023-08-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "main.h"
#ifndef __TASK_SCORE_H__
#define __TASK_SCORE_H__
#if ( configUSE_16_BIT_TICKS == 1 )
        typedef uint16_t     TickType_t;
        #define portMAX_DELAY              ( TickType_t ) 0xffff
#else
        typedef uint32_t     TickType_t;
        #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL
void task_score (void *pvParamete);
#ifdef ___int32_t_defined
#ifndef _INT32_T_DECLARED
typedef __int32_t int32_t ;
#define _INT32_T_DECLARED
#endif
#ifndef _UINT32_T_DECLARED
typedef __uint32_t uint32_t ;
#define _UINT32_T_DECLARED
#endif
#define __int32_t_defined 1
#endif /* ___int32_t_defined */
#endif
#endif