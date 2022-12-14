#include "BlittersFix.h"
#include <Utilities/Macro.h>
// Author: Apollo

#pragma region C3 Z-aware SHP translucency fixes

// 50% translucency blitter pt. 1
DEFINE_DYNAMIC_PATCH(Blit50TranslucencyFix1, 0x4987F7,
	0x66, 0xBA, 0xDE, 0xF7);		// mov	dx, 0xF7DE

// 50% translucency blitter pt. 2
DEFINE_DYNAMIC_PATCH(Blit50TranslucencyFix2, 0x498817,
	0x8B, 0x04, 0x41,			// mov    eax, DWORD PTR [ecx+eax*2]
	0x89, 0xC1,					// mov    ecx, eax
	0x33, 0x0B,					// xor    ecx, DWORD PTR [ebx]
	0x21, 0xD1,					// and    ecx, edx
	0xD1, 0xE9,					// shr    ecx, 1
	0x0B, 0x03,					// or     eax, DWORD PTR [ebx]
	0x29, 0xC8,					// sub    eax, ecx
	0x90, 0x90, 0x90, 0x90);	// nop nop nop nop

// 75% translucency blitter
DEFINE_DYNAMIC_PATCH(Blit75TranslucencyFix, 0x4985FE,
	0x66, 0xBE, 0xDE, 0xF7,					// mov    si, 0xF7DE
	0x66, 0x8B, 0x0A,						// mov    cx, WORD PTR [edx]
	0x31, 0xC0,								// xor    eax, eax
	0x66, 0x8B, 0x44, 0x4D, 0x00,			// mov    ax, WORD PTR [ebp+ecx*2+0x0]
	0x8B, 0x4C, 0x24, 0x18,					// mov    ecx, DWORD PTR [esp+0x18]
	0x81, 0xE1, 0xFF, 0x00, 0x00, 0x00,		// and    ecx, 0xFF
	0x8B, 0x6C, 0x24, 0x2C,					// mov    ebp, DWORD PTR [esp+0x2C]
	0x09, 0xC8,								// or     eax, ecx
	0x8B, 0x4C, 0x24, 0x10,					// mov    ecx, DWORD PTR [esp+0x10]
	0x8B, 0x49, 0x04,						// mov    ecx, DWORD PTR [ecx+0x4]
	0x8B, 0x04, 0x41,						// mov    eax, DWORD PTR [ecx+eax*2]
	0x89, 0xC1,								// mov    ecx, eax
	0x33, 0x0F,								// xor    ecx, DWORD PTR [edi]
	0x21, 0xF1,								// and    ecx, esi
	0xD1, 0xE9,								// shr    ecx, 1
	0x0B, 0x07,								// or     eax, DWORD PTR [edi]
	0x29, 0xC8,								// sub    eax, ecx
	0x89, 0xC1,								// mov    ecx, eax
	0x33, 0x07,								// xor    eax, DWORD PTR [edi]
	0x09, 0xC1,								// or     ecx, eax
	0x21, 0xF0,								// and    eax, esi
	0xD1, 0xE8,								// shr    eax, 1
	0x29, 0xC1,								// sub    ecx, eax
	0x8B, 0x44, 0x24, 0x20,					// mov    eax, DWORD PTR [esp+0x20]
	0x66, 0x89, 0x0F,						// mov    WORD PTR [edi], cx
	0x47,									// inc    edi
	0x47);									// inc    edi

// 25% translucency blitter
DEFINE_DYNAMIC_PATCH(Blit25TranslucencyFix, 0x4989EE,
	0x66, 0xBE, 0xDE, 0xF7,					// mov    si, 0xF7DE
	0x66, 0x8B, 0x0A,						// mov    cx, WORD PTR [edx]
	0x31, 0xC0,								// xor    eax, eax
	0x66, 0x8B, 0x44, 0x4D, 0x00,			// mov    ax, WORD PTR [ebp+ecx*2+0x0]
	0x8B, 0x4C, 0x24, 0x18,					// mov    ecx, DWORD PTR [esp+0x18]
	0x81, 0xE1, 0xFF, 0x00, 0x00, 0x00,		// and    ecx, 0xDD
	0x8B, 0x6C, 0x24, 0x2C,					// mov    ebp, DWORD PTR [esp+0x2C]
	0x09, 0xC8,								// or     eax, ecx
	0x8B, 0x4C, 0x24, 0x10,					// mov    ecx, DWORD PTR [esp+0x10]
	0x8B, 0x49, 0x04,						// mov    ecx, DWORD PTR [ecx+0x4]
	0x8B, 0x04, 0x41,						// mov    eax, DWORD PTR [ecx+eax*2]
	0x89, 0xC1,								// mov    ecx, eax
	0x33, 0x0F,								// xor    ecx, DWORD PTR [edi]
	0x21, 0xF1,								// and    ecx, esi
	0xD1, 0xE9,								// shr    ecx, 1
	0x50,									// push   eax
	0x0B, 0x07,								// or     eax, DWORD PTR [edi]
	0x29, 0xC8,								// sub    eax, ecx
	0x59,									// pop    ecx
	0x31, 0xC1,								// xor    ecx, eax
	0x09, 0xC8,								// or     eax, ecx
	0x21, 0xF1,								// and    ecx, esi
	0xD1, 0xE9,								// shr    ecx, 1
	0x29, 0xC8,								// sub    eax, ecx
	0x66, 0x89, 0x07,						// mov    WORD PTR [edi], ax
	0x47,									// inc    edi
	0x47);									// inc    edi

void BlittersFix::Apply()
{
	Blit25TranslucencyFix->Apply();
	Blit50TranslucencyFix1->Apply();
	Blit50TranslucencyFix2->Apply();
	Blit75TranslucencyFix->Apply();
}
#pragma endregion
