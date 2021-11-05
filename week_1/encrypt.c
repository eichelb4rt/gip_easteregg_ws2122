#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_file(const char* filename) {
    FILE* f = fopen(filename, "rt");
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* buffer = (char*) malloc(length + 1);
    buffer[length] = '\0';
    fread(buffer, 1, length, f);
    fclose(f);
    return buffer;
}

int write_file(const char* filename, const char* content) {
    FILE* f;
    f = fopen(filename, "w");
    fprintf(f, "%s", content);
    fclose(f);
    return 0;
}

int encrypt(char* clear_text, const char key) {
    char num_key = key - 'a';
    for (int i = 0; i < strlen(clear_text); ++i) {
        char clear_char = clear_text[i];
        char crypt_char = clear_char;
        if (clear_char >= 'a' && clear_char <= 'z') {
            int new_pos = (clear_char - 'a' + num_key) % 26;
            crypt_char = 'a' + new_pos;
        } else if (clear_char >= 'A' && clear_char <= 'Z') {
            int new_pos = (clear_char - 'A' + num_key) % 26;
            crypt_char = 'A' + new_pos;
        }
        clear_text[i] = crypt_char;
    }
    return 0;
}

int main(int argc, char const* argv[]) {
    if (argc != 3) {
        printf("Wrong number of arguments: %d.\n", argc);
        exit(1);
    }
    const char* filename = argv[1];
    const char key = argv[2][0];
    char* content = read_file(filename);
    encrypt(content, key);
    write_file(filename, content);
    return 0;
}

// Usage: encrypt filename key
// Example: encrypt crypt.txt n
// Oehhhhuuu