#ifndef ID3_WRITER_H
#define ID3_WRITER_H

#include "id3_utils.h"

/**
 * @brief Writes the ID3 tags to an MP3 file.
 * 
 * @param filename The name of the MP3 file.
 * @param data Pointer to the TagData structure containing the ID3 tags.
 * @return 0 on success, non-zero on failure.
 */

void read_till_frame(const char *frame, const char *value, FILE *fp, FILE *temp_fp);

int read_size(int size, FILE *fp);

void read_write_data(int size, FILE *fp, FILE *temp_fp);

void skip_bytes(int size, FILE *fp);

char *get_encode_BOM(int *value_size, int *size, FILE *fp);

void write_size_msb(int size, FILE *temp_fp);

void write_rem_data(FILE *fp, FILE *temp_fp);

int write_id3_tags(const char *filename, const TagData *data);

/**
TODO: Add documention as sample given above
 */
int edit_tag(const char *filename, const char *tag, const char *value);

#endif // ID3_WRITER_H
