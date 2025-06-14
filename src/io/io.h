#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include "render_txt.h"
#include"../data/dynamic_array/dynamicarray.h"

#define is_ctrl(x) ((x) & 0x1f)


bool ListenKeys(int character, Cursor *cursor, Text** td,Dynamic_array* DA, char* filename);

bool LoadFile(char* filename, Text** T, Cursor *cursor);
bool SaveFile(char *filename,Text** T);

bool jumpnextline(Text * T, Dynamic_array*DA, Cursor *cursor);
bool jumppreviousline(Text * T, Dynamic_array*DA, Cursor *cursor);

bool inccurx(Cursor *cursor);
bool inccury(Cursor *cursor);
bool deccurx(Cursor *cursor);
bool deccury(Cursor *cursor);
uint32_t index_of_newline(Dynamic_array* DA, int num);


// Test

uint32_t get_line_length(Text* T, uint32_t line_number);
uint32_t get_total_lines(Text* T);
void update_cursor_pos(Text** T,Cursor *cursor);
