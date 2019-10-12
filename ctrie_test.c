#include <stdlib.h>

#include "ctrie_test.h"

//======= HELPERS ==============================

ctrie_value_t* make_value_copy(ctrie_value_t val) {
	ctrie_value_t* val_ptr = (ctrie_value_t*)malloc(sizeof(ctrie_value_t));
	if (val_ptr == NULL)
		return NULL;

	*val_ptr = val;
}

//======= TESTS ================================


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

	char* key = "thisissomeletters";
	ctrie_value_t val = 42;
	ctrie_value_t* value = make_value_copy(val);

	ctrie_add(map, key, value);

	ctrie_value_t* ptr = ctrie_lookup(map, key);

	bool result = true;
	if (result = (*ptr == val))
		print_sub("add and lookup ok\n", 1);
	else
		print_sub("add and lookup failed\n", 1);

	ctrie_destroy(map);

	puts("\n");
	return result;
}