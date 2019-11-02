#ifndef __CMAP_TEST_H__
#define __CMAP_TEST_H__

#include <stdbool.h>

#include "cmap.h"

bool test_create_destroy();

bool test_add();

bool test_erase();

bool test_re_add();

bool test_get();

bool test_get_first();

bool test_get_next();

bool test_iterate();

bool test_remove();

bool test_empty();



#endif // __CMAP_TEST_H__