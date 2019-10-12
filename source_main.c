#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "win32_leak_check.h"
#include "ctrie_test.h"

#define MAX_TESTS 20
#define RESULT_BUFFER_SZ 50

void str_result(char* buffer, const char* name, const bool result);



int main(int argc, char** argv) {
#if defined(_DEBUG)
	int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;   // check block integrity
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF; // don't recycle memory
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;     // leak report on exit
	_CrtSetDbgFlag(dbgFlags);
#endif

	char results_buffer[MAX_TESTS][RESULT_BUFFER_SZ] = { 0 };

	str_result(results_buffer[0], "test_create_destroy()", test_create_destroy());
	str_result(results_buffer[1], "test_add_lookup()", test_add_lookup());
	str_result(results_buffer[2], "test_add()", test_add());
	str_result(results_buffer[3], "test_remove()", test_remove());
	str_result(results_buffer[4], "test_re_add()", test_re_add());

	unsigned width = 0;
	unsigned w;
	unsigned num_tests = 0;

	for (num_tests = 1; num_tests < MAX_TESTS && (w = strlen(results_buffer[num_tests-1])); ++num_tests) {
		if (w > width)
			width = w;
	}

	puts("\n");
	for (size_t i = 0; i < num_tests; ++i) {
		printf("% *s\n", width, results_buffer[i]);
	}
}

//==========================================




void str_result(char* buffer, const char* name, const bool result) {
	char pass_fail[10];
	//memset(pass_fail, 0, 100);

	if (result)
		sprintf_s(pass_fail, 10, "%s", "Pass");
	else
		sprintf_s(pass_fail, 10, "%s", "Fail");

	sprintf_s(buffer, RESULT_BUFFER_SZ, "%s: %s", name, pass_fail);
}



