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

#include "main.h"

static char *input;

#ifndef UNIT_TEST

/* ----------------------------------------------------------- */
int main(int argc, char **argv){

	int exit_code=0;

	/* Notice that explicitly passed parameters have precedence
	 * over environment */
	if((exit_code = parse_params(argc, argv)))
		return exit_code; /* not 0 - if something wrong or help */

	if((exit_code = process())){
		fprintf(stderr, "Can't process: internal error %d\n", exit_code);
		return exit_code;
	}

	return exit_code;
}

#endif

/*
 * Prints help message if something wrong with arguments
 */
static void wrong_args(){
	fprintf(stderr, "Wrong arguments. Try 'is -h' for reference.\n");
}


/* parse command-line options as usual and set globals */
static int parse_params(int argc, char **argv){

	int c, i;

	while ((c = getopt(argc, argv, "i:o:hdt")) != -1){
		switch (c){
			case 'i':
				/* input=optarg; */
				break;
			case 'o':
				/* outputfilename=optarg; */
				break;
			case 'h':
				help();
				return 1; /* help - no need in continuing: exit */
			case 'd':
				debug = 1;
				break;
			case 't':
				trace = 1;
				break;
	        /*
			case ':':
 				wrong_args();
				return -1;
			case '?':
				wrong_args();
				return -1;
				*/
			default :
				wrong_args();
				return -1; /* wron args - exit */
		}/* switch */
	}/* while (all args) */

	/* The rest - keys. See help screen (is -h) - for which functionality */

	/* if(debug)printf("arguments left: %d\n",(argc-optind)); */

	for(i=0 ; optind < argc; ++optind){
		/* if(debug)printf("argv[%d]='%s'\n", optind, argv[optind]); */
		if(i==0){
			input=argv[optind];
		}/*
		if(i==1)
			*/
		i++;
	}

	/* Implement instead of the following - reading from stdin - like md5 is doing */
	if(!input){
		help();
		return -1;
	}

	return 0;
}


static int process(){

	int exit_code=0, i;
	char output[RESULT_LENGTH+CHARACTERS_TO_SKIP+1];

    	MD5_CTX mdContext;
    	char sum[HASH_LENGTH];

	MD5Init (&mdContext);
    	MD5Update (&mdContext, input, strlen(input));

	memset(output, ' ', RESULT_LENGTH);

	MD5Final (&mdContext);

	for(i = 0; i < 16; i++)
	    sum[i]=mdContext.digest[i];


	if((exit_code = encode(HASH_LENGTH, sum, RESULT_LENGTH+CHARACTERS_TO_SKIP, output))){
		return exit_code;
	}

	output[RESULT_LENGTH+CHARACTERS_TO_SKIP]='\0';
	output[RESULT_LENGTH+CHARACTERS_TO_SKIP-2]='\0'; /* do not show last 2 '==' */

	printf("%s", output);

	if(debug){
		PRINT("%s", input);
		PRINT("%s", output);
		/* PRINT("md5=%s ", recPtr->result); */
	}
	return 0;
}


/*
 * Prints detailed help screen
 */
static void help(){

	fprintf(stdout, "\n\
NID Network Identificator Generating Tool \n\
Version 0.1\n\
\n\
SYNOPSIS\n\
	nid \"string\"\n\
	(for more examples see below)\n\
OPTIONS:\n\
    -h         Print this help screen\n\
    -d         Debug\n\
	\n\
EXAMPLES:\n\
   nid \"Firstname Secondname 01011968 myCatName articles\"\n\
\n\
");

}


