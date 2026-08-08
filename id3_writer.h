#ifndef ID3_WRITER_H
#define ID3_WRITER_H

#define WIDTH 50
#include "id3_utils.h"


/**
 * @brief Copies the content of the file that needs to be editted to a 
 *                  temporary file and edits the contents there
 * 
 * @param frame Name of the frame that needs to be editted
 * @param value The value that needs to be editted with.
 * @param fp Pointer to the file whose data needs to be editted
 * @param temp_fp Pointer to the temporary file to which data is copied and editted there.
 * @return 1 if edit is done successfully, otherwise 0.
 */
int copy_and_edit_frame(const char *frame, const char *value, FILE *fp, FILE *temp_fp);

/**
 * @brief Reads the size of the frame from binary and converts to decimal.
 * 
 * @param size Number of bytes to be read.
 * @param fp Pointer to the file from where the size is read.
 * @return Decimal format of the size.
 */
int read_size(int size, FILE *fp);

/**
 * @brief Reads one byte from one file and writes to another for fixed number of times
 * 
 * @param size Number of times the read and write to be done.
 * @param fp Pointer to the file whose data needs to be read
 * @param temp_fp Pointer to the file to witch data is wrote.
 */
void read_write_data(int size, FILE *fp, FILE *temp_fp);

/**
 * @brief Skips a specified number of bytes
 * 
 * @param size Number of bytes that needs to be skipped.
 * @param fp Pointer to the file where the bytes are skipped
 */
void skip_bytes(int size, FILE *fp);

/**
 * @brief Reads the encoding and BOM bytes and updates the frame and
 *        edited value sizes accordingly.
 * 
 * @param value_size Pointer to the size of the new value being edited.
 * @param size Size of the frame in the original file.
 * @param fp Pointer to the file from which the encoding and BOM bytes
 *           are read.
 * @return Pointer to a string containing the encoding and BOM bytes,
 *         or NULL if memory allocation fails.
 */
char *get_encode_BOM(int *value_size, int *size, FILE *fp);

/**
 * @brief Writes the size to the temporary file in big endian system
 * 
 * @param size The size that needs to be wrote.
 * @param temp_fp Pointer to the file where the size is written
 */
void write_size_msb(int size, FILE *temp_fp);

/**
 * @brief Writes the remaining data from the original file to the 
 *                              temporary file after edit is done.
 * 
 * @param fp Pointer to the original file.
 * @param Pointer to the temporary file
 */
void write_rem_data(FILE *fp, FILE *temp_fp);

/**
 * @brief Handles the entire bytes read and write from the original to the temporary file
 * @param fp Pointer to the file whose data needs to be read
 * @param temp_fp Pointer to the file to which data is wrote.
 * @param value Pointer to the new value to be assigned to the selected tag.
 * @return 1 if edit is done successfully, otherwise 0.
 */
int write_edit_data(FILE *fp, FILE *temp_fp, const char *value);

/**
 * @brief Prints Output headings in equal lengths
 * 
 * @param value Pointer to the frame name that is editted
 */
void print_headings(const char *value);

//int write_id3_tags(const char *filename, const TagData *data);
/**
 * @brief Writes the ID3 tags to an MP3 file.
 * 
 * @param filename The name of the MP3 file.
 * @param frame Pointer to the frame name that needs to be editted
 * @param value New value to be assigned to the selected tag.
 * @return 1 on success, 0 on failure.
 */
int write_id3_tags(const char *filename, const char *frame, const char *value);

/**
 * @brief Handles the edit option and modifies the selected ID3 tag.
 * 
 * @param filename Name of the file to be editted.
 * @param tag Pointer to the tag selected to edit.
 * @param value New value to be assigned to the selected tag.
 * @return 1 on failure and 0 on success.
 */
int edit_tag(const char *filename, const char *tag, const char *value);

#endif // ID3_WRITER_H
