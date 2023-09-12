/*
    A simple CSV file parser for easier data loading from .csv file to a 2D C-array.
    Author: Hubert F. Espinola I
    Written: September 12, 2023
*/

#include <stdlib.h>


long CURRENT_FILE_SIZE = 0;

short check_file_existence(FILE fptr);
char* read_file(const char* fpath);
char** read_csv(const char* fpath);

// reads the file bytes and returns
char* read_file(const char* fpath) {
    long file_length;
    char* buffer;

    fileptr = fopen(fpath, "rb");
    fseek(fileptr, 0, SEEK_END);

    file_length = ftell(fileptr);
    rewind(fileptr);

    buffer = (char*)malloc(file_length * sizeof(char));
    fread(buffer, file_length, 1, fileptr);
    fclose(fileptr);

    return buffer;
}