#include <Utilities/Debug.h>
#include <CCINIClass.h>
#include <Helpers/Macro.h>

/*
* issue #288 Proper INI Inheritance
* Author: secsome
* Last updated: 2021/7/12 1:06 (GMT+8)
*/

DEFINE_HOOK(0x525D76, INIClass_Load_ProcessInherit, 0x8)
{
	GET(CCINIClass*, pThis, EBP);

	UNREFERENCED_PARAMETER(pThis);

	return 0;
}