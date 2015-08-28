/**
 *
 * The original algorithm is written by Lew Pitcher
 *
 * http://www.thecodingforums.com/threads/sample-for-base64-encoding-in-c-language.516606/
 * http://computer-programming-forum.com/47-c-language/073976883ef440e8.htm
 * etc
 */

static char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int encode(unsigned s_len, char *src, unsigned d_len, char *dst){
	unsigned triad;

	for(triad = 0; triad < s_len; triad += 3){
		unsigned long int sr = 0;
		unsigned byte;

		for(byte = 0; (byte<3)&&(triad+byte<s_len); ++byte){
			sr <<= 8;
			sr |= (*(src+triad+byte) & 0xff);
		}

		sr <<= (6-((8*byte)%6))%6; /*shift left to next 6bit alignment*/

		if (d_len < 4) return 1000; /* error - dest too short */

		*(dst+0) = *(dst+1) = *(dst+2) = *(dst+3) = '=';
		switch(byte){
		case 3:
			*(dst+3) = base64[sr&0x3f];
			sr >>= 6;
		case 2:
			*(dst+2) = base64[sr&0x3f];
			sr >>= 6;
		case 1:
			*(dst+1) = base64[sr&0x3f];
			sr >>= 6;
			*(dst+0) = base64[sr&0x3f];
		}
		dst += 4; d_len -= 4;
	}



	return 0;

}

/*
 ** DECODE BASE64 into RAW
 */

/* determine which sextet value a Base64 character represents */
int tlu(int byte){
	int index;

	for (index = 0; index < 64; ++index)
		if (base64[index] == byte)
			break;
	if (index > 63) index = -1;
	return index;

}

/*
 ** Decode source from Base64 encoded string into raw data
 **
 ** Returns: 0 - Success
 ** 1 - Error - Source underflow - need more base64 data
 ** 2 - Error - Chunk contains half a byte of data
 ** 3 - Error - Decoded results will overflow output buffer
 */
int decode(unsigned s_len, char *src, unsigned d_len, char *dst){
	unsigned six, dix;

	dix = 0;

	for (six = 0; six < s_len; six += 4){
		unsigned long sr;
		unsigned ix;

		sr = 0;
		for (ix = 0; ix < 4; ++ix)
		{
			int sextet;

			if (six+ix >= s_len)
				return 1;
			if ((sextet = tlu(*(src+six+ix))) < 0)
				break;
			sr <<= 6;
			sr |= (sextet & 0x3f);
		}

		switch (ix){
		case 0: /* end of data, no padding */
			return 0;

		case 1: /* can't happen */
			return 2;

		case 2: /* 1 result byte */
			sr >>= 4;
			if (dix > d_len) return 3;
			*(dst+dix) = (sr & 0xff);
			++dix;
			break;

		case 3: /* 2 result bytes */
			sr >>= 2;
			if (dix+1 > d_len) return 3;
			*(dst+dix+1) = (sr & 0xff);
			sr >>= 8;
			*(dst+dix) = (sr & 0xff);
			dix += 2;
			break;

		case 4: /* 3 result bytes */
			if (dix+2 > d_len) return 3;
			*(dst+dix+2) = (sr & 0xff);
			sr >>= 8;
			*(dst+dix+1) = (sr & 0xff);
			sr >>= 8;
			*(dst+dix) = (sr & 0xff);
			dix += 3;
			break;
		}
	}
	return 0;

}

/******************************************************
 ** Test bed program to encode and decode base64 data **
 ******************************************************/
#ifdef BASE64_TEST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char Bin_array[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 };
	char Str_array[64];
	char Raw_array[64];
	int binsize, bufsize;

	printf("Test 1 - increasing size binary data\n");
	for (binsize = 0; binsize < 7; ++binsize)
	{
		memset(Str_array,0,64);
		if (encode(binsize,Bin_array,64,Str_array) == 0)
		{
			int Strsize;

			printf("%d bytes becomes >%s<\n",binsize,Str_array);

			Strsize = strlen(Str_array);
			if (decode(Strsize,Str_array,binsize,Raw_array) == 0)
			{
				if (memcmp(Bin_array,Raw_array,binsize) == 0)
					printf("values match\n");
				else printf("values differ\n");
			}
			else printf("decode failed\n");
		}
		else printf("%d bytes failed to encode\n");
	}

	printf("\nTest 2 - decreasing size buffer\n");
	for (bufsize = 10; bufsize > 0; --bufsize)
	{
		printf("** %d byte buffer\n",bufsize);
		for (binsize = 0; binsize < 7; ++binsize)
		{
			memset(Str_array,0,64);
			if (encode(binsize,Bin_array,bufsize,Str_array) == 0)
			{
				int Strsize;

				printf("%d bytes becomes >%s<\n",binsize,Str_array);

				Strsize = strlen(Str_array);
				if (decode(Strsize,Str_array,binsize,Raw_array) == 0)
				{
					if (memcmp(Bin_array,Raw_array,binsize) == 0)
						printf("values match\n");
					else printf("values differ\n");
				}
				else printf("decode failed\n");
			}
			else printf("%d bytes failed to encode\n",binsize);
		}
	}
	return EXIT_SUCCESS;

}

#endif
