//──────────────────────────────────────────────────────────────────────────
#ifndef	LIB_SYSTEM_PATCH
#define LIB_SYSTEM_PATCH

//──────────────────────────────────────────────────────────────────────────
#ifdef	__cplusplus
extern	"C"	{
#endif

//──────────────────────────────────────────────────────────────────────────
#ifdef	_WIN32

//──────────────────────────────────────────────────────────────────────────
// This is not used anymore! If ever using it from C/CPP - 
// change assembly function to read arguments from stack!
// If you do so, make sure the assembly that calls this function uses the correct calling convention too.
// 
// S32	AllowPatch(void *start, void *len)	;
// #pragma aux AllowPatch	"*"	\
// 	parm caller	[eax] [edx]	\
// 	modify 	[ecx]

//──────────────────────────────────────────────────────────────────────────
#else //YAZ_WIN32

//──────────────────────────────────────────────────────────────────────────
#define	AllowPatch(start, end)

//──────────────────────────────────────────────────────────────────────────
#endif//YAZ_WIN32

//──────────────────────────────────────────────────────────────────────────
#ifdef	__cplusplus
}
#endif

//──────────────────────────────────────────────────────────────────────────
#endif//LIB_SYSTEM_PATCH

//──────────────────────────────────────────────────────────────────────────
