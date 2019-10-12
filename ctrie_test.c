#include <stdlib.h>

#include "ctrie_test.h"

//======= HELPERS ==============================

// used for making values of different types
ctrie_value_t* make_value(ctrie_value_t val) {
	ctrie_value_t* val_ptr = (ctrie_value_t*)malloc(sizeof(ctrie_value_t));
	if (val_ptr == NULL)
		return NULL;

	*val_ptr = val;
}

void print_sub(const char* msg, unsigned level) {
	printf("%*s%s",
		level, "  ", msg);
}

//======= TESTS ================================


bool test_create_destroy() {
	puts("\ntest_create_destroy():");

	unsigned level = 1;
	bool result = true;

	ctrie* map = ctrie_create();
	if (result = (map != NULL))
		print_sub("create ok\n", level);
	else
		print_sub("create failed\n", level);

	ctrie_destroy(map);
	print_sub("destroy ok\n", level);
	
	return result;
}

bool test_add_lookup() {
	puts("\ntest_add_lookup():");

	ctrie* map = ctrie_create();

	const char* key = "thisissomeletters";
	ctrie_value_t value = 42;

	ctrie_add(map, key, value);

	ctrie_value_t val = ctrie_lookup(map, key);

	bool result = true;
	if (result &= (val == value))
		print_sub("add and lookup ok\n", 1);
	else
		print_sub("add and lookup failed\n", 1);

	ctrie_destroy(map);
	return result;
}

bool test_add() {
	puts("\ntest_add():");
	ctrie* map = ctrie_create();

	const char* valid_keys[] = { "wabce", "xyzt", "lmopq" };
	const ctrie_value_t valid_values[] = { 25, -5, 36 };
	for (size_t i = 0; i < 3; ++i)
		ctrie_add(map, valid_keys[i], valid_values[i]);

	const char* long_key = "ajfqwertyuioplkjhgfdsazxcvbnmlkjhgfdsaqwertyuiopplmoknijbuhvygvtfcrdxezsaq";
	const int long_value = 123456789;
	ctrie_add(map, long_key, long_value);

	const char* invalid_key = "abcdEfghijk";
	ctrie_add(map, invalid_key, 100);

	bool valid_result = true;
	ctrie_value_t val;
	for (size_t i = 0; i < 3; ++i) {
		val = ctrie_lookup(map, valid_keys[i]);
		valid_result &= (val == valid_values[i]);
	}		

	if(valid_result)
		print_sub("add valid ok\n", 1);
	else
		print_sub("add valid failed\n", 1);

	val = ctrie_lookup(map, long_key);
	bool long_result = val == long_value;
	if (long_result)
		print_sub("add long key ok\n", 1);
	else
		print_sub("add long key failed\n", 1);

	bool invalid_result = ctrie_lookup(map, invalid_key) == NULL;
	if (invalid_result)
		print_sub("add invalid key ok\n", 1);
	else
		print_sub("add invalid key failed\n", 1);
	
	ctrie_destroy(map);
	return valid_result && long_result&& invalid_result;
}

bool test_remove() {
	puts("\ntest_remove():");
	ctrie* map = ctrie_create();

	const char* keys[] = { "wabce", "xyzt", "lmopq" };
	const ctrie_value_t values[] = { 25, -5, 36 };
	for (size_t i = 0; i < 3; ++i)
		ctrie_add(map, keys[i], values[i]);

	bool add_result = true;
	for (size_t i = 0; i < 3; ++i)
		add_result &= (ctrie_lookup(map, keys[i]) == values[i]);

	if (add_result)
		print_sub("add ok\n", 1);
	else
		print_sub("add failed\n", 1);

	for (size_t i = 0; i < 3; ++i)
		ctrie_remove(map, keys[i]);

	bool remove_result = true;
	for (size_t i = 0; i < 3; ++i)
		remove_result &= ctrie_lookup(map, keys[i]) == NULL;

	if (remove_result)
		print_sub("remove ok\n", 1);
	else
		print_sub("remove failed\n", 1);

	ctrie_destroy(map);
	return add_result & remove_result;
}

bool test_re_add() {
	puts("\ntest_re_add():");
	ctrie* map = ctrie_create();

	const char* keys[] = { "wabce", "xyzt", "lmopq" };
	const ctrie_value_t values[] = { 25, -5, 36 };
	for (size_t i = 0; i < 3; ++i)
		ctrie_add(map, keys[i], values[i]);

	bool add_result = true;
	for (size_t i = 0; i < 3; ++i)
		add_result &= (ctrie_lookup(map, keys[i]) == values[i]);

	if (add_result)
		print_sub("add ok\n", 1);
	else
		print_sub("add failed\n", 1);

	for (size_t i = 0; i < 3; ++i)
		ctrie_remove(map, keys[i]);

	bool remove_result = true;
	for (size_t i = 0; i < 3; ++i)
		remove_result &= ctrie_lookup(map, keys[i]) == NULL;

	ctrie_value_t val;
	for (size_t i = 0; i < 3; ++i)
		val = ctrie_lookup(map, keys[i]);

	if (remove_result)
		print_sub("remove ok\n", 1);
	else
		print_sub("remove failed\n", 1);

	bool re_add_result = true;
	for (size_t i = 0; i < 3; ++i)
		ctrie_add(map, keys[i], values[i]);

	for (size_t i = 0; i < 3; ++i)
		re_add_result &= (ctrie_lookup(map, keys[i]) == values[i]);

	if (re_add_result)
		print_sub("re-add ok\n", 1);
	else
		print_sub("re-add failed\n", 1);

	ctrie_destroy(map);
	return add_result & remove_result && re_add_result;
}

/*

bool test_add() {
	puts("\ntest_add():");
	bool result = true;
	ctrie* map = ctrie_create();



	ctrie_destroy(map);
	return result;
}

*/