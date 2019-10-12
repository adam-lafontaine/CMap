#ifndef __CTRIE_CONFIG_H__
#define __CTRIE_CONFIG_H__

// include desired character options for string keys
static const char KEY_CHARS[] = "abcdefghijklmnopqrstuvwxyz";

// define value type
typedef int ctrie_value_t;

// do not touch
#define CTRIE_KEY_LENGTH sizeof KEY_CHARS 


// defines how a character is mapped to an array index
// implementation in ctrie_config.c
size_t c_idx(char* c);

#endif // !__CTRIE_CONFIG_H__
