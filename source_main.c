#include <stdio.h>

#include "win32_leak_check.h"
#include "ctrie.h"


int main(int argc, char** argv) {
#if defined(_DEBUG)
	int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;   // check block integrity
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF; // don't recycle memory
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;     // leak report on exit
	_CrtSetDbgFlag(dbgFlags);
#endif

	ctrie* map = ctrie_create_test();



	printf("value: %d", ctrie_test_value(map));

	ctrie_destroy(map);
}