/*
 * Copyright (c) 2014-2016 Alibaba Group. All rights reserved.
 * License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#ifndef __LITE_UTILS_H__
#define __LITE_UTILS_H__

#include <stdarg.h>
#if defined(_PLATFORM_IS_LINUX_)
#include <assert.h>
#endif

#include "lite-list.h"
#include "lite-log.h"

#if defined(_PLATFORM_IS_LINUX_)
#define LITE_ASSERT(expr)           assert(expr)
#else
#define LITE_ASSERT(expr) \
    do { \
        if (!(expr)) { \
            HAL_Printf("### %s | %s(%d): ASSERT FAILED ###: %s is FALSE\r\n", \
                            __FILE__, __func__, __LINE__, #expr); \
        } \
    } while(0)
#endif

#define LITE_malloc(size)           LITE_malloc_internal(__func__, __LINE__, size)
#define LITE_free(ptr)              \
    do { \
        if(!ptr) { \
            log_err("%s == NULL! LITE_free(%s) aborted.", #ptr, #ptr); \
            break; \
        } \
        \
        LITE_free_internal((void *)ptr); \
        ptr = NULL; \
    } while(0)

void       *LITE_malloc_internal(const char *f, const int l, int size);
void        LITE_free_internal(void *ptr);
void        LITE_free_routine(void *ptr);

void        LITE_dump_malloc_free_stats(int level);

#endif  /* __LITE_UTILS_H__ */
