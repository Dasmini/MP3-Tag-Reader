/**
 * @file id3_writer.c
 * @brief Implementation of functions for writing and editing ID3 tags in MP3 files.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "id3_writer.h"
#include "id3_reader.h"
#include "id3_utils.h"

/**
 * @brief Writes the ID3 tags to an MP3 file.
 * 
 * @param filename The name of the MP3 file.
 * @param data Pointer to the TagData structure containing the ID3 tags.
 * @return 0 on success, non-zero on failure.
 */
int read_size(int size, FILE *fp)
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

void read_write_data(int size, FILE *fp, FILE *temp_fp)
{
    int ch;
    for (int i = 0; i < size; i++)
    {
        ch = getc(fp);
        putc(ch, temp_fp);
    }
}

void skip_bytes(int size, FILE *fp)
{
    for (int i = 0; i < size; i++)
    {
        getc(fp);
    }
}

char *get_encode_BOM(int *value_size, int *size, FILE *fp)
{
    char *ch = malloc(5);    //first element represents the number of cells
    int enc;
    switch(enc = fgetc(fp))
    {
        case 0:
            printf("Inside 0\n");
            *value_size += 1;
            *size -=1;
            *ch = 1;
            *(ch + 1) = enc;
            *(ch + 2) = '\0';
            break;
        case 1:
            printf("Inside 1\n");   
            *ch = 3;
            *(ch + 1) = enc;
            *(ch + 2) = fgetc(fp);
            *(ch + 3) = fgetc(fp);
            *(ch + 4) = '\0';
            *value_size += 3;
            *size -= 3;
            break;
        case 2:
            *value_size += 1;
            *size -= 1;
            *ch = 1;
            *(ch + 1) = enc;
            *(ch + 2) = '\0';
            break;
        default:
            printf("Enc is %d\n",enc);
            printf("Encode byte found not for ID3V2.3!\n");
            break;
    }
    return ch;
}

void write_size_msb(int size, FILE *temp_fp)
{
    unsigned char size_bytes[4];
            
    size_bytes[0] = (size >> 24) & 0xFF;
    size_bytes[1] = (size >> 16) & 0xFF;
    size_bytes[2] = (size >> 8) & 0xFF;
    size_bytes[3] = size & 0xFF;

    fwrite(size_bytes, 4, 1, temp_fp);
    printf("%s\n", size_bytes);
}

void write_rem_data(FILE *fp, FILE *temp_fp)
{
    int ch;
    while((ch = getc(fp)) != EOF)
    {
        putc(ch, temp_fp);
    }
}

void read_till_frame(const char *frame, const char *value, FILE *fp, FILE *temp_fp)
{
    /* read header 10 bytes*/
    char ch[10];
    int size;
    fread(ch, 10, 1, fp); 
    fwrite(ch, 10, 1, temp_fp);
    for(int i = 0; i < FRAMES; i++)
    {
        fread(ch, 4, 1, fp);
        ch[4] = '\0';
        fwrite(ch, 4, 1, temp_fp);
        printf("Tag %d : %s\n", i, ch);
        if(strcmp(ch, frame) == 0)
        {
            char flag_value[2] = {0, 0};
            size = read_size(4, fp);
            printf("Original frame size : %d\n", size);
            skip_bytes(2, fp);
            int value_size = strlen(value) + 1;
            printf("New frame size      : %d\n", value_size);
            char *encode_content = get_encode_BOM(&value_size, &size, fp);
            printf("Remaining after BOM : %d\n", size);
            printf("New frame size after BOM : %d\n", value_size);
            skip_bytes(size, fp);
            write_size_msb(value_size, temp_fp);
            fwrite(&flag_value, 2, 1, temp_fp);
            for (int i = 1; i <= encode_content[0]; i++)
            {
                putc(encode_content[i], temp_fp);
            }
            //Write the actual edited content
            while(*value != '\0')
            {
                putc(*value, temp_fp);
                //putc(flag_value[0], temp_fp);
                value++;
            }
            putc(flag_value[0], temp_fp);
        }
        else
        {
            int flag;
            char size_bytes[4];
            size = read_size(4, fp);
            write_size_msb(size, temp_fp);
            //fwrite(size_bytes, 4, 1, temp_fp);
            flag = getc(fp);
            putc(flag, temp_fp);
            flag = getc(fp);
            putc(flag, temp_fp);
            read_write_data(size, fp, temp_fp);
        }
        
    }
    write_rem_data(fp, temp_fp);
    return;
}

int write_id3_tags(const char *filename, const TagData *data) {
    // Implementation for writing ID3 tags
    return 0;
}

/** TODO: Add documentation as sample given above */
int edit_tag(const char *filename, const char *tag, const char *value) {
    /*TagData *data = read_id3_tags(filename);
    if (!data) {
        return 1;
    }*/
    // Implementation for writing ID3 tags to file
    //-t/-T/-a/-A/-y/-c/-g
    FILE *temp_fp, *fp;
    fp = fopen(filename, "rb");
    temp_fp = fopen("temp.mp3", "wb");
    if(!strcmp(tag, "-t") || !strcmp(tag, "-T"))
    {
        printf("Editing Title...\n");
        read_till_frame("TIT2", value, fp, temp_fp);
    }
    else if(!strcmp(tag, "-y"))
    {
        printf("Editing Year...\n");
        read_till_frame("TYER", value, fp, temp_fp);
    }
    else if(!strcmp(tag, "-A"))
    {
        printf("Editing Artist...\n");
        read_till_frame("TPEI", value, fp, temp_fp);
    }
    else if(!strcmp(tag, "-a"))
    {
        printf("Editing Album...\n");
        read_till_frame("TALB", value, fp, temp_fp);
    }
    else if(!strcmp(tag, "-g"))
    {
        printf("Editing Genre...\n");
        read_till_frame("TCON", value, fp, temp_fp);
    }
    else if(!strcmp(tag, "-c"))
    {
        printf("Editing Composer...\n");
        read_till_frame("TCOM", value, fp, temp_fp);
    }
    
    fclose(fp);
    fclose(temp_fp);
}
