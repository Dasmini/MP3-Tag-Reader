#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

/**
 * @brief Displays and error message to the user.
 * @param message Error message to be displayed
 */
void display_error(const char *message);

/**
 * @brief Checks if ID3 tag is present in the file.
 * @param fp File pointer to the mp3 file to be checked.
 * @return 1 if an ID3 tag is present otherwise 0.
 */
int check_id3_tag_presence(FILE *fp);

#endif // ERROR_HANDLING_H
