/**
 * @file id3_reader.c
 * @brief Implementation of functions for reading ID3 tags from MP3 files.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "id3_reader.h"
#include "error_handling.h"


int open_read_file(const char *filename, TagData *data)
{
    data -> fptr = fopen(filename, "r");
    if(data -> fptr == NULL)
    {
        return 0;
    }
    return 1;
}

/**
TODO: Add documention as sample given
 */
int check_id3_tag_presence(const char *filename)
{
    return 0;
}

int check_file_identifier(FILE *fp)
{
    unsigned char ch[4];
    fread(ch, 3, 1, fp);
    ch[4] = '\0';
    if(strcmp(ch, "ID3") == 0)
    {
        printf("ID3 read!");
        return 1;
    }
        
    return 0;
}
int check_version(FILE *fp)
{
    printf("checking version..\n");
    char version[2];
    for (int i = 0; i < 2; i++)
    {
        version[i] = getc(fp);
    }
    if(version[0] == 3)
        return 1;
    return 0;
}

int read_integers(int size, FILE *fp)
{
    char read_data[size];
    unsigned int integer_value = 0;
    for (int i = 0; i < size; i++)
    {
        read_data[i] = getc(fp);
        integer_value |= read_data[i] << (8 * (size - i - 1));
    }
    return integer_value;
}

void read_character_data(int *size,char *data, FILE *fp)
{
    int ch;
    int index = 0;
    
    for(int i = 0; i < *size; i++)
    {
        ch = getc(fp);
        if(ch != '\0')
        {
            data[index] = ch;
            index++;
        }
        
    }
    data[index] = '\0';
}

void read_encode_BOM(int *size, FILE *fp)
{
    switch(fgetc(fp))
    {
        case 0:
            return;
        case 1:
            fgetc(fp);
            fgetc(fp);
            *size -= 3;
            return;
        case 2:
            return;
        default:
            printf("Encode byte found not for ID3V2.3!\n");
            break;
    }
    return;
}

/**
TODO: Add documention as sample given
 */
TagData* read_id3_tags(const char *filename) {
    // Implementation for reading ID3 tags
    TagData *data = malloc(sizeof(TagData));
    /*open file*/
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        perror("fopen");
        return NULL;
    }
    
    /*Check ID3 presence*/
    if(check_file_identifier(fp) == 0)
        return NULL;

    /*check version*/
    if(check_version(fp) == 0)
        return NULL;
    
    //get tags
    char ch[50];
    fseek(fp, 10, SEEK_SET);
    for(int i = 0; i < 4; i++)
    {
        fread(ch, 4, 1, fp);
        ch[4] = '\0';
        printf("Tag %d : %s\n", i, ch);
        if(strcmp(ch, "TALB") == 0)
        {
            int size = read_integers(4, fp);
            read_integers(2, fp);  // To read and skip the flag bytes
            read_encode_BOM(&size, fp);
            //char read_data[size + 1];
            data -> album = malloc(size + 1);
            read_character_data(&size, data -> album, fp);    
        }
        if(strcmp(ch, "TPE1") == 0)
        {
            int size = read_integers(4, fp);
            read_integers(2, fp);  // To read and skip the flag bytes
            read_encode_BOM(&size, fp);
            //char read_data[size + 1];
            data -> artist = malloc(size + 1);
            read_character_data(&size, data ->artist , fp); 
        }
        if(strcmp(ch, "COMM") == 0)
        {
            int size = read_integers(4, fp);
            read_integers(2, fp);
            for(int i = 0; i < size; i++)
            {
                getc(fp);
            }

        }
    }
    


    return data;
}

/**
TODO: Add documention as sample given
 */
void display_metadata(const TagData *data) {
    // Implementation for displaying metadata
    printf("Artist : %s\n", data -> artist);
    printf("Album : %s\n", data -> album);
}

/**
 * @brief Displays error message
 * @param Error message
 */
void display_error(const char *message)
{
    printf("%s", message);
}


/**
TODO: Add documention as sample given
 */
void view_tags(const char *filename) {
    TagData *data;
    /*if(open_read_file(filename, data))
        printf("File opened successfully\n");
    else{
        printf("Failed to open file");
        return;
    }*/
    data = read_id3_tags(filename);
    if (!data) {
        display_error("Failed to read ID3 tags.\n");
        return;
    }
    display_metadata(data);
    free_tag_data(data);
}
