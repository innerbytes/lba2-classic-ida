//****************************************************************************
#ifndef	LIB_3D_ROTMAT
#define	LIB_3D_ROTMAT

//****************************************************************************
#include	"datamat.h"

//****************************************************************************
#ifdef	__cplusplus
extern	"C"	{
#endif

//****************************************************************************
typedef	void (Func_RotateMatrix)(TYPE_MAT *MatDst, TYPE_MAT *MatSrc, S32 x, S32 y, S32 z) ;

#pragma aux Arg_RotateMatrix	"*"	       		\
	parm caller	[edi] [esi] [eax] [ebx] [ecx]	\
	modify		[edx]

#pragma	aux (Arg_RotateMatrix)	Func_RotateMatrix

//****************************************************************************
// !! Please do not call this anymore from C/C++. Those assmebly functions need to use stack arguments.
// extern	Func_RotateMatrix	*RotateMatrix	;

#pragma aux	RotateMatrix		"*"

//****************************************************************************
// These functions should not be called directly but through the above pointer
// which auto-initalize to point to the right routine at runtime.
// 
// !! Please do not call those from C/C++ at all. They need to use stack arguments if you do.
// extern	Func_RotateMatrix	RotateMatrixI	; // optimized for Integer
// extern	Func_RotateMatrix	RotateMatrixU	; // general routine

//****************************************************************************
#ifdef	__cplusplus
}
#endif

//****************************************************************************
#endif//LIB_3D_ROTMAT

//****************************************************************************

