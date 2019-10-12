#include <stdlib.h>
#include <stdbool.h>

#include "ctrie.h"

//======= NODE ==============================

struct ctrie_node_t;
typedef struct ctrie_node_t ct_node;

typedef struct ctrie_node_t {
	size_t id;
	ct_node* child[CTRIE_KEY_LENGTH];
	ct_node* parent;
	ctrie_value_t value;
};


void clear_value(ct_node* node) {
#ifdef CTRIE_VALUE_IS_PTR

	if (node->value != NULL) {
		free(node->value);		
	}

#endif // !CTRIE_VALUE_IS_PTR

	node->value = NULL;
}


ct_node* create_node(const size_t id) {
	ct_node* node = (ct_node*)malloc(sizeof(ct_node));

	if (node == NULL)
		return NULL;

	node->id = id;
	node->parent = NULL;
	clear_value(node);

	size_t i = 0;
	while (i < CTRIE_KEY_LENGTH)
		node->child[i++] = NULL;

	return node;
}

void destroy_node(ct_node* node) {
	if (node == NULL)
		return;

	for (size_t i = 0; i < CTRIE_KEY_LENGTH; ++i) {
		if (node->child[i] != NULL)
			destroy_node(node->child[i]);
	}

	clear_value(node);
	node->parent = NULL;

	free(node);
}

bool has_child_node(const ct_node* node, size_t index){
	return node->child[index] != NULL;
}

bool is_empty_node(const ct_node* node) {
	if (node == NULL || node->value != NULL)
		return false;

	for (size_t i = 0; i < CTRIE_KEY_LENGTH; ++i) {
		if (node->child[i] != NULL)
			return false;
	}

	return true;
}

bool is_root_node(const ct_node* node) {
	return node->parent == NULL;
}


void add_child_node(ct_node* node, size_t index) {
	ct_node* child = create_node(index);
	child->parent = node;

	destroy_node(node->child[index]);		

	node->child[index] = child;
}

ct_node* lookup_node(const ct_node* node, char* s) {
	ct_node* found = node;

	while (*s != '\0') {
		size_t idx = c_idx(s++);
		if (!has_child_node(found, idx))
			return NULL;

		found = found->child[idx];
	}

	return found;
}

//======= HELPERS =================================

bool is_valid_char(const char c) {
	return strchr(KEY_CHARS, c) != NULL;
}


//======= PUBLIC ==================================

struct ctrie_t {
	ct_node* root;
};


ctrie* ctrie_create() {
	ctrie* map = (ctrie*)malloc(sizeof(ctrie));

	if (map == NULL)
		return NULL;

	map->root = create_node(0);
	if (map->root == NULL) {
		free(map);
		return NULL;
	}

	return map;
}


void ctrie_destroy(ctrie* map) {
	if (map->root == NULL)
		return;
	
	destroy_node(map->root);

	free(map);
}


void ctrie_add(ctrie* map, const char* s, const ctrie_value_t value) {
	char* c = s;

	while (*c != '\0') {
		if (!is_valid_char(*c++))
			return;
	}

	ct_node* node = map->root;
	c = s;

	while (*c != '\0') {
		size_t idx = c_idx(c++);
		if (!has_child_node(node, idx))
			add_child_node(node, idx);

		node = node->child[idx];
	}

	node->value = value;
}

void ctrie_remove(ctrie* map, const char* key) {
	ct_node* node = lookup_node(map->root, key);
	if (node == NULL)
		return;
	
	clear_value(node);
	
	// cleanup
	while (!is_root_node(node)) {
		size_t child_id = node->id;
		node = node->parent;

		if (is_empty_node(node->child[child_id])) {
			destroy_node(node->child[child_id]);
			node->child[child_id] = NULL;
		}			
	}
}

ctrie_value_t ctrie_lookup(const ctrie* map, const char* s) {
	ct_node* node = lookup_node(map->root, s);
	if (node == NULL)
		return NULL;

	return node->value;
}