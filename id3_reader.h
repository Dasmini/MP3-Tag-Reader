#ifndef ID3_READER_H
#define ID3_READER_H

#include "id3_utils.h"

/**
 * @brief Opens the files to read.
 * @param filename Name of the file needs to be opened.
 * @param data Pointer to the TagData structure where the file pointer is stored.
 * @return 1 on successful opening, otherwise 0.
 */
int open_read_file(const char *filename, TagData *data);

/**
 * @brief Checks the version of the mp3 tag
 * @param fp Pointer to the file needs to be checked
 * @return 1 on finding of specific version, otherwise 0.
 */
int check_version(FILE *fp);

/**
 * @brief Converts the binary to integer value.
 * @param size Number of bytes to be read.
 * @param fp Pointer to the file bytes are read from.
 * @return the integer value of the read bytes.
 */
int read_integers(int size, FILE *fp);

/**
 * @brief Converts the read binary to character value/string.
 * @param size Number of bytes to be read.
 * @param data Pointer to the character array where the converted string is stored.
 * @param Pointer to the file bytes are read from.
 */
void read_character_data(int size,char *data, FILE *fp);

/**
 * @brief Checks the encoding byte and reads BOM.
 * @param size Pointer to the frame size variable.
 * @param fp Pointer to the file needs to be checked.
 */
void read_encode_BOM(int *size, FILE *fp);

/**
 * @brief Reads the frame header details and determines the remaining data size.
 * @param fp Pointer to the file needs to be checked.
 * @return Number of data bytes remaining in the frame after processing the encoding and BOM.  
 */
int frame_data(FILE *fp);

/**
 * @brief Reads bytes nad converts it to string and reduces the size by the number of bytes read.
 * @param size Pointer to the frame size variable.
 * @param bytes Number of bytes to read.
 * @param fp Pointer to the file needs to be read.
 * @return A char pointer to the converted string.
 */
char *get_byte_reduced_size(int *size, int bytes , FILE *fp);

/**
 * @brief Skips the specified number of bytes from the file.
 * @param size Number of bytes to be skipped
 * @param fp Pointer to the file needs to be read.
 */
void skip_read_bytes(int size, FILE *fp);

/**
 * @brief Reads the ID3 tag data.
 * @param filename Name of the file that needs to be read
 * @return Pointer to the TagData structure containing the extracted
 *         tag information, or NULL if reading fails.
 */
TagData* read_id3_tags(const char *filename);

/**
 * @brief Displays all extracted ID3 tag metadata in the output terminal.
 * @param data Pointer to the Tagdata structure containing the extracted frame data.
 */
void display_metadata(const TagData *data);

/**
 * @brief Handles the view option and initiates the metadata reading process.
 * @param filename Name of the file that needs to be read
 */
void view_tags(const char *filename);

#endif // ID3_READER_H
