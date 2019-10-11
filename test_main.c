#include <stdio.h>
#include <stdbool.h>

#include "win32_leak_check.h"
#include "ctrie.h"

#define NUM_TESTS 2
#define RESULT_BUFFER 50

void str_result(char* buffer, const char* name, const bool result);

bool test_create_destroy();
bool test_add_lookup();



int main(int argc, char** argv) {
#if defined(_DEBUG)
	int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;   // check block integrity
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF; // don't recycle memory
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;     // leak report on exit
	_CrtSetDbgFlag(dbgFlags);
#endif

	char results_buffer[NUM_TESTS][RESULT_BUFFER] = { 0 };

	str_result(results_buffer[0], "test_create_destroy()", test_create_destroy());
	str_result(results_buffer[1], "test_add_lookup()", test_add_lookup());


	unsigned width = 30;

	for (size_t i = 0; i < NUM_TESTS; ++i) {
		printf("% *s\n", width, results_buffer[i]);
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

ctrie_value_t* make_value_copy(ctrie_value_t val) {
	ctrie_value_t* val_ptr = (ctrie_value_t*)malloc(sizeof(ctrie_value_t));
	if (val_ptr == NULL)
		return NULL;

	*val_ptr = val;
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

	puts("\n");
	return c_result;
}

bool test_add_lookup() {
	puts("test_add_lookup():");

	ctrie* map = ctrie_create();

	char* key = "0110";
	ctrie_value_t val = 42.0;
	ctrie_value_t* value = make_value_copy(val);

	ctrie_add(map, key, value);

	ctrie_value_t* ptr = ctrie_lookup(map, key);

	bool result = true;
	if(result = (*ptr == val))
		print_sub("add and lookup ok\n", 1);
	else
		print_sub("add and lookup failed\n", 1);

	ctrie_destroy(map);

	puts("\n");
	return result;
}