#ifndef ID3_READER_H
#define ID3_READER_H

#include "id3_utils.h"

/**
TODO: Add documention as sample given
 */
int open_read_file(const char *filename, TagData *data);

int check_file_identifier(FILE *fp);

int check_version(FILE *fp);

int read_integers(int size, FILE *fp);

void read_character_data(int size,char *data, FILE *fp);

void read_encode_BOM(int *size, FILE *fp);

int frame_data(FILE *fp);
/**
TODO: Add documention as sample given
 */
TagData* read_id3_tags(const char *filename);

/**
TODO: Add documention as sample given 
 */
void display_metadata(const TagData *data);

/**
TODO: Add documention as sample given
 */
void view_tags(const char *filename);

#endif // ID3_READER_H
