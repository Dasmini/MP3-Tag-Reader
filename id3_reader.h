#ifndef ID3_READER_H
#define ID3_READER_H

#include "id3_utils.h"

/**
* @brief
* @param
* @return
 */
int open_read_file(const char *filename, TagData *data);

/**
* @brief
* @param
* @return
 */
int check_file_identifier(FILE *fp);

/**
* @brief
* @param
* @return
 */
int check_version(FILE *fp);

/**
* @brief
* @param
* @return
 */
int read_integers(int size, FILE *fp);

/**
* @brief
* @param
* @return
 */
void read_character_data(int size,char *data, FILE *fp);

/**
* @brief
* @param
* @return
 */
void read_encode_BOM(int *size, FILE *fp);

/**
* @brief
* @param
* @return
 */
int frame_data(FILE *fp);

/**
* @brief
* @param
* @return
 */
char *get_byte_red_size(int *size, int bytes , FILE *fp);

/**
* @brief
* @param
* @return
 */
void skip_read_bytes(int size, FILE *fp);

/**
* @brief
* @param
* @return
 */
TagData* read_id3_tags(const char *filename);

/**
* @brief
* @param
* @return
 */
void display_metadata(const TagData *data);

/**
* @brief
* @param
* @return
 */
void view_tags(const char *filename);

#endif // ID3_READER_H
