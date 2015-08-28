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

#include "utils.h"


void rtrim(char * string, char trim){
	int i;
	for(i = strlen(string)-1; (i >= 0) && (strchr (string + i, trim)!=NULL); i--)
		string[i] = '\0';
}

/* not efficient - please rewrite me! */
void ltrim(char * string, char trim){
	while((*string != '\0') && (strchr (string, trim)!=NULL))
		memmove(string, string+1, strlen(string));
}


