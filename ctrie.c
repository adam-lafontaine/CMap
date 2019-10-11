#include <stdlib.h>
#include <stdbool.h>

#include "ctrie.h"

static const char KEY_CHARS[] = { '0', '1' };

#define CTRIE_KEY_LENGTH sizeof(KEY_CHARS)

//======= HELPERS ===========================

size_t c_idx(char* c) {
	return *c - 48;
}



//======= NODE ==============================

typedef struct ctrie_node_t {
	ctrie* child[CTRIE_KEY_LENGTH];
	ctrie* parent;
	ctrie_value_t* value;
} ct_node;


ct_node* create_node() {
	ct_node* node = (ct_node*)malloc(sizeof(ct_node));

	if (node == NULL)
		return NULL;

	node->parent = NULL;
	node->value = NULL;

	size_t i = 0;
	while (i < CTRIE_KEY_LENGTH)
		node->child[i++] = NULL;

	return node;
}

void destroy_node(ct_node* node) {
	if (node == NULL)
		return;

	for (size_t i = 0; i < CTRIE_KEY_LENGTH; ++i)
		if (node->child[i] != NULL)
			destroy_node(node->child[i]);

	if (node->value != NULL)
		free(node->value);

	free(node);
}

bool has_child_node(ct_node* node, size_t index){
	return node->child[index] != NULL;
}

bool is_empty_node(ct_node* node) {
	if (node->value != NULL)
		return false;

	for (size_t i = 0; i < CTRIE_KEY_LENGTH; ++i)
		if (node->child[i] != NULL)
			return false;

	return true;
}

bool is_root_node(ct_node* node) {
	return node->parent == NULL;
}


void add_child_node(ct_node* node, size_t index) {
	ct_node* child = create_node();
	child->parent = node;

	destroy_node(node->child[index]);		

	node->child[index] = child;
}

ct_node* lookup_node(ct_node* node, char* s) {
	while (*s != '\0') {
		size_t idx = c_idx(s++);
		if (!has_child_node(node, idx))
			return NULL;

		node = node->child[idx];
	}

	return node;
}


//===== PUBLIC ==================================

struct ctrie_t {

	ct_node* root;
};


ctrie* ctrie_create() {
	ctrie* map = (ctrie*)malloc(sizeof(ctrie));

	if (map == NULL)
		return NULL;

	map->root = create_node();
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


void ctrie_add(ctrie* map, char* s, ctrie_value_t* value) {

	ct_node* node = map->root;

	while (*s != '\0') {
		size_t idx = c_idx(s++);
		if (!has_child_node(node, idx))
			add_child_node(node, idx);

		node = node->child[idx];
	}

	node->value = value;
}

void ctrie_remove(ctrie* map, char* s) {
	ct_node* node = lookup_node(map->root, s);
	if (node == NULL)
		return;
	
	free(node->value);
	
	while (!is_root_node(node)) {
		node = node->parent;

		for(size_t i = 0; i < CTRIE_KEY_LENGTH; ++i)
			if (is_empty_node(node->child[i]))
				destroy_node(node->child[i]);
	}
}

ctrie_value_t* ctrie_lookup(ctrie* map, char* s) {
	ct_node* node = lookup_node(map->root, s);
	if (node == NULL)
		return NULL;

	return node->value;
}

//======= TESTING FUNCTIONS ================

ctrie* ctrie_create_test() {
	ctrie* map = ctrie_create();

	map->root->value = (ctrie_value_t*)malloc(sizeof(ctrie_value_t));
	if (map->root->value != NULL)
		*map->root->value = 2;

	size_t i = 0;
	while (i < CTRIE_KEY_LENGTH) {
		ct_node* node = (map->root->child[i++] = create_node());
		node->value = (ctrie_value_t*)malloc(sizeof(ctrie_value_t));
		if (node->value != NULL)
			*node->value = 42;		
	}		

	return map;
}

size_t ctrie_test_value(ctrie* map) {
	return sizeof(map->root->child);
}