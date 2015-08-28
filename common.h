/**
 * Copyright (C) 2001 Vasili Gavrilov <vgavrilov AAAATTTTT users.sourceforge.net>
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/file.h>
/* #include <openssl/evp.h> */
#include "md5.h"

#define BOOL	int
#define TRUE	1
#define FALSE	0

char *strdup(const char *str); /* duplicate string - when not 2001 POSIX (XSI). Noticed that it is used only in mappings, so we have no problems with deallocating in this program */
unsigned int mysnprintf(char *buf, size_t size, const char *fmt, ...); /* if snprintf is not availbale */
extern int debug;
extern int trace;

/**********************
 * Logging stuff below
 **********************/
int LOG(char* fmt, ...);

/* variadic macros working only with C99 compilers: */
#define PRINT(mesg, ...) fprintf(stdout, mesg, __VA_ARGS__)

#ifdef DEBUG
#define DPRINT(mesg, ...) fprintf(stdout, mesg, __VA_ARGS__)
#else
#define DPRINT(mesg, ...)
#endif

#define OUT_OF_MEM() { \
			fprintf(stderr, "Out of memory: %s:%d", __FILE__, __LINE__); \
			exit(-1); \
		}

#define FATAL(X){ \
		fprintf(stderr, X); \
		exit(-1); \
	}

#define PRINTN(X, ...){ \
	}

#endif /* __COMMON_H__ */
