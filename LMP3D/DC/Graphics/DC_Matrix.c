#include <stdio.h>
#include <stdlib.h>

#ifdef DREAMCAST
#include <kos.h>

#include "LMP3D/LMP3D.h"
#include "LMP3D/DC/DC.h"


#define PAD_R1 0x10000
#define PAD_L1 0x20000

inline void DC_Matrix_Load(float *matrix)
{
	asm (

	"frchg		\n	" //LS
	"fmov		@%0+,fr0\n	" //LS
	"fmov		@%0+,fr1\n	" //LS
	"fmov		@%0+,fr2\n	" //LS
	"fmov		@%0+,fr3\n	" //LS

	"fmov		@%0+,fr4\n	" //LS
	"fmov		@%0+,fr5\n	" //LS
	"fmov		@%0+,fr6\n	" //LS
	"fmov		@%0+,fr7\n	" //LS

	"fmov		@%0+,fr8\n	" //LS
	"fmov		@%0+,fr9\n	" //LS
	"fmov		@%0+,fr10\n	" //LS
	"fmov		@%0+,fr11\n	" //LS

	"fmov		@%0+,fr12\n	" //LS
	"fmov		@%0+,fr13\n	" //LS
	"fmov		@%0+,fr14\n	" //LS
	"fmov		@%0+,fr15\n	" //LS
	"frchg		\n	" //LS


    ::"r"(matrix) : "memory");
}



void LMP3D_MatrixMultiply(float* dest,float* src1,float* src2)
{
	DC_Matrix_Load(src2);

	asm (

	"fmov		@%0+,fr0\n	" //LS
	"add		#16,%1\n	" //EX

	"fmov		@%0+,fr1\n	" //LS
	"fmov		@%0+,fr2\n	" //LS
	"fmov		@%0+,fr3\n	" //LS

	"ftrv		xmtrx,fv0\n	" //FE

	"fmov		@%0+,fr4\n	" //LS
	"fmov		@%0+,fr5\n	" //LS
	"fmov		@%0+,fr6\n	" //LS
	"fmov		@%0+,fr7\n	" //LS

	"fmov		fr3,@-%1\n	" //LS
	"fmov		fr2,@-%1\n	" //LS
	"fmov		fr1,@-%1\n	" //LS
	"fmov		fr0,@-%1\n	" //LS

	"ftrv		xmtrx,fv4\n	" //FE

	"fmov		@%0+,fr8\n	" //LS
	"add		#32,%1\n	" //EX

	"fmov		@%0+,fr9\n	" //LS
	"fmov		@%0+,fr10\n	" //LS
	"fmov		@%0+,fr11\n	" //LS

	"fmov		fr7,@-%1\n	" //LS
	"fmov		fr6,@-%1\n	" //LS
	"fmov		fr5,@-%1\n	" //LS
	"fmov		fr4,@-%1\n	" //LS

	"ftrv		xmtrx,fv8\n	" //FE

	"fmov		@%0+,fr12\n	" //LS
	"add		#32,%1\n	" //EX

	"fmov		@%0+,fr13\n	" //LS
	"fmov		@%0+,fr14\n	" //LS
	"fmov		@%0+,fr15\n	" //LS

	"fmov		fr11,@-%1\n	" //LS
	"fmov		fr10,@-%1\n	" //LS
	"fmov		fr9,@-%1\n	" //LS
	"fmov		fr8,@-%1\n	" //LS


	"ftrv		xmtrx,fv12\n	" //FE
	"add		#32,%1\n	" //EX

	"fmov		fr15,@-%1\n	" //LS
	"fmov		fr14,@-%1\n	" //LS
	"fmov		fr13,@-%1\n	" //LS
	"fmov		fr12,@-%1\n	" //LS

    ::"r"(src1) , "r"(dest) : "memory");
}


void LMP3D_MatrixProjection(float* matrix)
{
	matrix[(0<<2)+0] = 640.0f;
	matrix[(0<<2)+1] = 0;
	matrix[(0<<2)+2] = 0;
	matrix[(0<<2)+3] = 0;

	matrix[(1<<2)+0] = 0;
	matrix[(1<<2)+1] = 640.0f*1.3333;
	matrix[(1<<2)+2] = 0;
	matrix[(1<<2)+3] = 0;

	matrix[(2<<2)+0] = 320;
	matrix[(2<<2)+1] = 240;
	matrix[(2<<2)+2] = 1;
	matrix[(2<<2)+3] = 1;

	matrix[(3<<2)+0] = 0;
	matrix[(3<<2)+1] = 0;
	matrix[(3<<2)+2] = 10000;
	matrix[(3<<2)+3] = 0.0f;
}



void LMP3D_MatrixOrthogonal(float* matrix)
{
	matrix[(0<<2)+0] = 1;
	matrix[(0<<2)+1] = 0;
	matrix[(0<<2)+2] = 0;
	matrix[(0<<2)+3] = 0;

	matrix[(1<<2)+0] = 0;
	matrix[(1<<2)+1] = 1;
	matrix[(1<<2)+2] = 0;
	matrix[(1<<2)+3] = 0;

	matrix[(2<<2)+0] = 0;
	matrix[(2<<2)+1] = 0;
	matrix[(2<<2)+2] = 1;
	matrix[(2<<2)+3] = 0;

	matrix[(3<<2)+0] = 320;
	matrix[(3<<2)+1] = 240;
	matrix[(3<<2)+2] = 1;
	matrix[(3<<2)+3] = 1.0f;
}

#endif


