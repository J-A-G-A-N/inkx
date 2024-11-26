#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include "render_txt.h"
#include"../data/dynamic_array/dynamicarray.h"
#define is_ctrl(x) ((x) & 0x1f)
bool ListenKeys(int character, uint32_t *cury, uint32_t *curx, Text** td,Dynamic_array* DA, char* filename);
//bool ListenKeys(int character, int cury, int curx, Text** td, char* filename);
bool LoadFile(char* filename, Text** T, uint32_t* cury, uint32_t* curx);
bool SaveFile(char *filename,Text** T);
bool jumpnextline(Text * T, Dynamic_array*DA, uint32_t cury, uint32_t curx);
bool jumppreviousline(Text * T, Dynamic_array*DA, uint32_t cury, uint32_t curx);
bool inccurx(uint32_t cury, uint32_t curx);
bool inccury(uint32_t cury, uint32_t curx);
bool deccurx(uint32_t cury, uint32_t curx);
bool deccury(uint32_t cury, uint32_t curx);
uint32_t index_of_newline(Dynamic_array* DA, int num);


// Test

uint32_t get_line_length(Text* T, uint32_t line_number);
uint32_t get_total_lines(Text* T);
void update_cursor_pos(Text** T, uint32_t cury, uint32_t curx);
