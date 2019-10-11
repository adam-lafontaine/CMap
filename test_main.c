#include <stdio.h>
#include <stdbool.h>

#include "win32_leak_check.h"
#include "ctrie.h"

#define NUM_TESTS 1
#define RESULT_BUFFER 50

bool test_create_destroy();
void str_result(char* buffer, const char* name, const bool result);


int main(int argc, char** argv) {
#if defined(_DEBUG)
	int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;   // check block integrity
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF; // don't recycle memory
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;     // leak report on exit
	_CrtSetDbgFlag(dbgFlags);
#endif

	char results_buffer[1][RESULT_BUFFER] = { 0 };

	str_result(results_buffer[0], "test_create_destroy()", test_create_destroy());

	puts("\n");

	for (size_t i = 0; i < NUM_TESTS; ++i) {
		puts(results_buffer[i]);
		puts("\n");
	}
}

//==========================================


void print_sub(const char* msg, unsigned level) {
	printf("%*s%s", 
		level, " ", msg);
}

void str_result(char* buffer, const char* name, const bool result) {
	char pass_fail[10];
	//memset(pass_fail, 0, 100);

	if (result)
		sprintf_s(pass_fail, 10, "%s", "Pass");
	else
		sprintf_s(pass_fail, 10, "%s", "Fail");

	sprintf_s(buffer, RESULT_BUFFER, "%s: %s", name, pass_fail);
}

bool test_create_destroy() {
	puts("test_create_destroy():");

	unsigned level = 1;
	bool c_result = true;

	ctrie* map = ctrie_create();
	if (c_result = (map != NULL))
		print_sub("create ok\n", level);
	else
		print_sub("create failed\n", level);

	ctrie_destroy(map);
	print_sub("destroy ok", level);

	return c_result;
}