#ifndef CMAP_CONFIG_STACK_H__
#define CMAP_CONFIG_STACK_H__

// include desired character options for string keys
static const char KEY_CHARS[] = "abcdefghijklmnopqrstuvwxyz";

typedef double cmap_value_t;

// do not touch
#define CMAP_KEY_LENGTH sizeof KEY_CHARS


// defines how a character is mapped to an array index
// implementation in cmap_config.c
size_t c_idx(char* c);

#endif