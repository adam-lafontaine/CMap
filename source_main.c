#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#include "win32_leak_check.h"
#endif

#define TEST_FOR_LEAKS

#include "cmap_test.h"

#define MAX_TESTS 20
#define RESULT_BUFFER_SZ 50



void str_result(char* buffer, const char* name, const bool result);



int main(int argc, char** argv) {
#if defined(_WIN32) && defined(_DEBUG) && defined(TEST_FOR_LEAKS)
	int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;   // check block integrity
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF; // don't recycle memory
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;     // leak report on exit
	_CrtSetDbgFlag(dbgFlags);
#endif

	char results_buffer[MAX_TESTS][RESULT_BUFFER_SZ] = { 0 };

	str_result(results_buffer[0], "test_create_destroy()", test_create_destroy());
	str_result(results_buffer[1], "test_add()", test_add());	
	str_result(results_buffer[2], "test_erase()", test_erase());
	str_result(results_buffer[3], "test_re_add()", test_re_add());
	str_result(results_buffer[4], "test_get()", test_get());
	str_result(results_buffer[5], "test_get_first()", test_get_first());
	str_result(results_buffer[6], "test_get_next()", test_get_next());
	str_result(results_buffer[7], "test_iterate()", test_iterate());
	str_result(results_buffer[8], "test_remove()", test_remove());
	str_result(results_buffer[9], "test_empty()", test_empty());

	unsigned width = 0;
	unsigned w;
	unsigned num_tests = 0;

	for (num_tests = 1; num_tests < MAX_TESTS && (w = strlen(results_buffer[num_tests-1])); ++num_tests) {
		if (w > width)
			width = w;
	}
	++width;

	puts("\n\nTest Summary:\n");
	for (size_t i = 0; i < num_tests; ++i) {
		printf("% *s\n", width, results_buffer[i]);
	}
}

//==========================================




void str_result(char* buffer, const char* name, const bool result) {
	char pass_fail[10];

	if (result)
		sprintf_s(pass_fail, 10, "%s", "Pass");
	else
		sprintf_s(pass_fail, 10, "%s", "Fail");

	sprintf_s(buffer, RESULT_BUFFER_SZ, "%s: %s", name, pass_fail);
}



