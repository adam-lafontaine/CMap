#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "cmap_test.h"



//======= HELPERS ==============================



void print_sub(const char* msg, unsigned level) {
	printf("%*s%s",
		level, "  ", msg);
}

//======= TESTS ================================


bool test_create_destroy() {
	puts("\ntest_create_destroy():");

	unsigned level = 1;
	bool result = true;

	cmap* map = cmap_create();
	if (result = (map != NULL))
		print_sub("create ok\n", level);
	else
		print_sub("create failed\n", level);

	cmap_destroy(map);
	print_sub("destroy ok\n", level);
	
	return result;
}

bool test_add() {
	puts("\ntest_add():");
	cmap* map = cmap_create();

	const char* valid_keys[] = { "wabce", "xyzt", "lmopq" };
	const cmap_value_t valid_values[] = { 25, -5, 36 };
	for (size_t i = 0; i < 3; ++i)
		cmap_add(map, valid_keys[i], valid_values[i]);

	const char* long_key = "ajfqwertyuioplkjhgfdsazxcvbnmlkjhgfdsaqwertyuiopplmoknijbuhvygvtfcrdxezsaq";
	const cmap_value_t long_value = 123456789;
	cmap_add(map, long_key, long_value);

	const char* invalid_key = "abcdEfghijk";
	cmap_add(map, invalid_key, 100);

	bool valid_result = true;
	for (size_t i = 0; i < 3; ++i) {
		cmap_pair* pair = cmap_get(map, valid_keys[i]);
		valid_result &= pair != NULL && (pair->value == valid_values[i]);
	}		

	if(valid_result)
		print_sub("add valid ok\n", 1);
	else
		print_sub("add valid failed\n", 1);

	cmap_pair* pair = cmap_get(map, long_key);
	bool long_result = pair->value == long_value;
	if (long_result)
		print_sub("add long key ok\n", 1);
	else
		print_sub("add long key failed\n", 1);

	bool invalid_result = cmap_get(map, invalid_key) == NULL;
	if (invalid_result)
		print_sub("add invalid key ok\n", 1);
	else
		print_sub("add invalid key failed\n", 1);
	
	cmap_destroy(map);
	return valid_result && long_result&& invalid_result;
}

bool test_erase() {
	puts("\ntest_erase():");
	cmap* map = cmap_create();

	const char* keys[] = { "wabce", "xyzt", "lmopq" };
	const cmap_value_t values[] = { 25, -5, 36 };
	for (size_t i = 0; i < 3; ++i)
		cmap_add(map, keys[i], values[i]);

	bool add_result = true;
	for (size_t i = 0; i < 3; ++i)
		add_result &= (cmap_get(map, keys[i])->value == values[i]);

	if (add_result)
		print_sub("add ok\n", 1);
	else
		print_sub("add failed\n", 1);

	for (size_t i = 0; i < 3; ++i)
		cmap_erase(map, keys[i]);

	bool erase_result = true;
	for (size_t i = 0; i < 3; ++i)
		erase_result &= cmap_get(map, keys[i]) == NULL;

	if (erase_result)
		print_sub("erase ok\n", 1);
	else
		print_sub("erase failed\n", 1);

	cmap_destroy(map);
	return add_result && erase_result;
}

bool test_re_add() {
	puts("\ntest_re_add():");
	cmap* map = cmap_create();

	const char* keys[] = { "wabce", "xyzt", "lmopq" };
	const cmap_value_t values[] = { 25, -5, 36 };
	for (size_t i = 0; i < 3; ++i)
		cmap_add(map, keys[i], values[i]);

	bool add_result = true;
	for (size_t i = 0; i < 3; ++i)
		add_result &= (cmap_get(map, keys[i])->value == values[i]);

	if (add_result)
		print_sub("add ok\n", 1);
	else
		print_sub("add failed\n", 1);

	for (size_t i = 0; i < 3; ++i)
		cmap_erase(map, keys[i]);

	bool erase_result = true;
	for (size_t i = 0; i < 3; ++i)
		erase_result &= cmap_get(map, keys[i]) == NULL;

	if (erase_result)
		print_sub("erase ok\n", 1);
	else
		print_sub("erase failed\n", 1);

	bool re_add_result = true;
	for (size_t i = 0; i < 3; ++i)
		cmap_add(map, keys[i], values[i]);

	for (size_t i = 0; i < 3; ++i)
		re_add_result &= (cmap_get(map, keys[i])->value == values[i]);

	if (re_add_result)
		print_sub("re-add ok\n", 1);
	else
		print_sub("re-add failed\n", 1);

	cmap_destroy(map);
	return add_result & erase_result && re_add_result;
}

bool test_get() {
	puts("\ntest_get():");
	cmap* map = cmap_create();

	const char* keys[] = { "wabce", "xyzt", "lmopq" };
	const cmap_value_t values[] = { 25, -5, 36 };
	for (size_t i = 0; i < 3; ++i)
		cmap_add(map, keys[i], values[i]);

	bool add_result = true;
	for (size_t i = 0; i < 3; ++i)
		add_result &= (cmap_get(map, keys[i])->value == values[i]);

	if (add_result)
		print_sub("add ok\n", 1);
	else
		print_sub("add failed\n", 1);

	bool key_result = true;
	bool value_result = true;
	for (size_t i = 0; i < 3; ++i) {
		cmap_pair* pair = cmap_get(map, keys[i]);
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

	cmap_destroy(map);
	return add_result && key_result && value_result;
}


bool test_get_first() {
	puts("\ntest_get_first():");
	cmap* map = cmap_create();

	const char* key1 = "adam";
	const char* key2 = "gary";
	const char* key3 = "peter";

	cmap_value_t val1 = 89;
	cmap_value_t val2 = -5874;
	cmap_value_t val3 = 42;

	bool empty_res = cmap_get_first(map) == NULL;
	if (empty_res)
		print_sub("empty ok\n", 1);
	else
		print_sub("empty failed\n", 1);

	cmap_add(map, key3, val3);
	cmap_add(map, key1, val1);
	cmap_add(map, key2, val2);
	
	cmap_pair* pair = cmap_get_first(map);
	bool first_res = pair != NULL && strcmp(pair->key, key1) == 0 && pair->value == val1;
	if (first_res)
		print_sub("first ok\n", 1);
	else
		print_sub("first failed\n", 1);

	cmap_erase(map, key1);
	pair = cmap_get_first(map);
	bool erase_res = pair != NULL && strcmp(pair->key, key2) == 0 && pair->value == val2;
	if (erase_res)
		print_sub("erase ok\n", 1);
	else
		print_sub("erase failed\n", 1);

	cmap_erase(map, key2);
	cmap_erase(map, key3);
	bool erase_all_res = cmap_get_first(map) == NULL;
	if (erase_all_res)
		print_sub("erase all ok\n", 1);
	else
		print_sub("erase all failed\n", 1);

	cmap_destroy(map);
	return empty_res && first_res;
}


bool test_get_next() {
	puts("\ntest_get_next():");
	cmap* map = cmap_create();

	const char* key1 = "adam";
	const char* key2 = "gary";
	const char* key3 = "peter";

	cmap_value_t val1 = 89;
	cmap_value_t val2 = -5874;
	cmap_value_t val3 = 42;

	cmap_add(map, key3, val3);
	cmap_add(map, key1, val1);
	cmap_add(map, key2, val2);

	cmap_pair* first = cmap_get_first(map);
	if (first == NULL) {
		print_sub("first failed\n", 1);
		return NULL;
	}	
	
	cmap_pair* second = cmap_get_next(map, first->key);
	if (second == NULL) {
		print_sub("second failed\n", 1);
		return false;
	}

	cmap_pair* third = cmap_get_next(map, second->key);
	if (third == NULL) {
		print_sub("third failed\n", 1);
		return false;
	}

	bool res_1 = strcmp(second->key, key2) == 0 && second->value == val2;
	if (res_1)
		print_sub("second key-value ok\n", 1);
	else
		print_sub("second key-value failed\n", 1);

	
	bool res_2 = third != NULL && strcmp(third->key, key3) == 0 && third->value == val3;
	if (res_2)
		print_sub("third ok\n", 1);
	else
		print_sub("third failed\n", 1);

	
	bool res_last = cmap_get_next(map, third->key) == NULL;
	if (res_last)
		print_sub("last ok\n", 1);
	else
		print_sub("last failed\n", 1);

	cmap_erase(map, key2);
	cmap_pair* new_second = cmap_get_next(map, first->key);
	bool res_erase = new_second != NULL && strcmp(new_second->key, key3) == 0 && new_second->value == val3;
	if (res_erase)
		print_sub("erase ok\n", 1);
	else
		print_sub("erase failed\n", 1);

	cmap_erase(map, key1);
	cmap_erase(map, key3);
	bool res_all = cmap_get_next(map, key1) == NULL;
	if (res_all)
		print_sub("erase all ok\n", 1);
	else
		print_sub("erase all failed\n", 1);

	cmap_destroy(map);
	return res_1 && res_2 && res_last && res_erase && res_all;
}


bool test_iterate() {
	puts("\ntest_iterate():");
	cmap* map = cmap_create();

	char keys[][20] = { 
		"ioefkasdjj", "wertyu", "lkjhg", "cvbnnm", "okmijnuhbygv",
		"asdfg", "lkjhgf", "asdfghjkl", "qwsdewq", "okmnjiuhjkouiy"
	};
	qsort(keys, 10, sizeof keys[0], strcmp);

	for (int i = 0; i < 10; ++i)
		cmap_add(map, keys[i], i);

	bool key_result = true;
	bool val_result = true;
	int i = 0;
	for (cmap_pair* pair = cmap_get_first(map); pair != NULL; pair = cmap_get_next(map, pair->key), ++i) {
		key_result &= strcmp(pair->key, keys[i]) == 0;
		val_result &= pair->value == i;
	}

	if (key_result)
		print_sub("keys ok\n", 1);
	else
		print_sub("keys failed\n", 1);

	if (val_result)
		print_sub("values ok\n", 1);
	else
		print_sub("values failed\n", 1);

	cmap_destroy(map);
	return key_result && val_result;
}

bool test_remove() {
	puts("\ntest_remove():");
	cmap* map = cmap_create();

	const char* keys[] = { "wabce", "xyzt", "lmopq" };
	const cmap_value_t values[] = { 25, -5, 36 };
	size_t num_ele = 3;

	for (size_t i = 0; i < num_ele; ++i)
		cmap_add(map, keys[i], values[i]);

	bool add_result = true;
	for (size_t i = 0; i < num_ele; ++i)
		add_result &= (cmap_get(map, keys[i])->value == values[i]);

	if (add_result)
		print_sub("add ok\n", 1);
	else
		print_sub("add failed\n", 1);

	bool remove_result = true;
	bool erase_result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		cmap_pair* pair = cmap_remove(map, keys[i]);
		remove_result &= pair != NULL && strcmp(pair->key, keys[i]) == 0 && pair->value == values[i];
		erase_result &= cmap_get(map, keys[i]) == NULL;

		free(pair); // only if pair has no pointer
	}
		

	if (remove_result)
		print_sub("remove ok\n", 1);
	else
		print_sub("remove failed\n", 1);

	if (erase_result)
		print_sub("erase ok\n", 1);
	else
		print_sub("erase failed\n", 1);

	cmap_destroy(map);
	return add_result && remove_result && erase_result;
}

bool test_empty() {
	puts("\ntest_empty():");
	cmap* map = cmap_create();

	bool create_result = cmap_empty(map);

	if (create_result)
		print_sub("create ok\n", 1);
	else
		print_sub("create failed\n", 1);

	size_t num_ele = 3;
	const char* keys[] = { "wabce", "xyzt", "lmopq" };
	const cmap_value_t values[] = { 25, -5, 36 };

	bool add_result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		cmap_add(map, keys[i], values[i]);
		add_result &= !cmap_empty(map);
	}
		
	if (add_result)
		print_sub("add ok\n", 1);
	else
		print_sub("add failed\n", 1);
	
	bool erase_result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		erase_result &= !cmap_empty(map);
		cmap_erase(map, keys[i]);
	}
	erase_result &= cmap_empty(map);

	if (erase_result)
		print_sub("erase ok\n", 1);
	else
		print_sub("erase failed\n", 1);

	for (size_t i = 0; i < num_ele; ++i)
		cmap_add(map, keys[i], values[i]);

	bool remove_result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		remove_result &= !cmap_empty(map);
		cmap_pair* pair = cmap_remove(map, keys[i]);
		free(pair);
	}
	remove_result &= cmap_empty(map);

	if (remove_result)
		print_sub("remove ok\n", 1);
	else
		print_sub("remove failed\n", 1);

	cmap_destroy(map);
	return create_result && add_result && erase_result && remove_result;
}

/*

bool test_add() {
	puts("\ntest_add():");
	bool result = true;
	cmap* map = cmap_create();



	cmap_destroy(map);
	return result;
}

*/