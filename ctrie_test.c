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

bool test_get() {
	puts("\ntest_get():");
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

	bool key_result = true;
	bool value_result = true;
	for (size_t i = 0; i < 3; ++i) {
		ctrie_pair* pair = ctrie_get(map, keys[i]);
		key_result &= strcmp(pair->key, keys[i]) == 0;
		value_result &= pair->value == values[i];
	}

	if (key_result)
		print_sub("get key ok\n", 1);
	else
		print_sub("get key failed\n", 1);

	if (value_result)
		print_sub("get value ok\n", 1);
	else
		print_sub("get value failed\n", 1);

	ctrie_destroy(map);
	return add_result && key_result && value_result;
}


bool test_get_first() {
	puts("\ntest_get_first():");
	ctrie* map = ctrie_create();

	const char* key1 = "adam";
	const char* key2 = "gary";
	const char* key3 = "peter";

	ctrie_value_t val1 = 89;
	ctrie_value_t val2 = -5874;
	ctrie_value_t val3 = 42;

	bool empty_res = ctrie_get_first(map) == NULL;
	if (empty_res)
		print_sub("empty ok\n", 1);
	else
		print_sub("empty failed\n", 1);

	ctrie_add(map, key3, val3);
	ctrie_add(map, key1, val1);
	ctrie_add(map, key2, val2);
	
	ctrie_pair* pair = ctrie_get_first(map);
	bool first_res = pair != NULL && strcmp(pair->key, key1) == 0 && pair->value == val1;
	if (first_res)
		print_sub("first ok\n", 1);
	else
		print_sub("first failed\n", 1);

	ctrie_remove(map, key1);
	pair = ctrie_get_first(map);
	bool remove_res = pair != NULL && strcmp(pair->key, key2) == 0 && pair->value == val2;
	if (remove_res)
		print_sub("remove ok\n", 1);
	else
		print_sub("remove failed\n", 1);

	ctrie_remove(map, key2);
	ctrie_remove(map, key3);
	bool remove_all_res = ctrie_get_first(map) == NULL;
	if (remove_all_res)
		print_sub("remove all ok\n", 1);
	else
		print_sub("remove all failed\n", 1);

	ctrie_destroy(map);
	return empty_res && first_res;
}


bool test_get_next() {
	puts("\ntest_get_next():");
	ctrie* map = ctrie_create();

	const char* key1 = "adam";
	const char* key2 = "gary";
	const char* key3 = "peter";

	ctrie_value_t val1 = 89;
	ctrie_value_t val2 = -5874;
	ctrie_value_t val3 = 42;

	ctrie_add(map, key3, val3);
	ctrie_add(map, key1, val1);
	ctrie_add(map, key2, val2);

	ctrie_pair* first = ctrie_get_first(map);
	
	ctrie_pair* second = ctrie_get_next(map, first->key);
	bool res_1 = second != NULL && strcmp(second->key, key2) == 0 && second->value == val2;
	if (res_1)
		print_sub("first ok\n", 1);
	else
		print_sub("first failed\n", 1);

	ctrie_pair* third = ctrie_get_next(map, second->key);
	bool res_2 = third != NULL && strcmp(third->key, key3) == 0 && third->value == val3;
	if (res_2)
		print_sub("second ok\n", 1);
	else
		print_sub("second failed\n", 1);

	bool res_last = ctrie_get_next(map, third->key) == NULL;
	if (res_2)
		print_sub("last ok\n", 1);
	else
		print_sub("last failed\n", 1);

	ctrie_remove(map, key2);
	ctrie_pair* new_second = ctrie_get_next(map, first->key);
	bool res_remove = new_second != NULL && strcmp(new_second->key, key3) == 0 && new_second->value == val3;
	if (res_remove)
		print_sub("remove ok\n", 1);
	else
		print_sub("remove failed\n", 1);

	ctrie_remove(map, key1);
	ctrie_remove(map, key3);
	bool res_all = ctrie_get_next(map, key1) == NULL;
	if (res_all)
		print_sub("remove all ok\n", 1);
	else
		print_sub("remove all failed\n", 1);

	ctrie_destroy(map);
	return res_1 && res_2 && res_last && res_remove && res_all;
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