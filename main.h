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

#ifndef __MAIN_H
#define __MAIN_H

#include <getopt.h>
#include "common.h"
#include "utils.h"
#include "constants.h"
#include "utils.h"

static void wrong_args();
static void help();
static int parse_params(int argc, char **argv);
static int process();
int encode(unsigned s_len, char *src, unsigned d_len, char *dst);


#endif
