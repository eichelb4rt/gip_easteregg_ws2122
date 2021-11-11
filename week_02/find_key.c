#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPH_LEN ('z' - 'a' + 1)
#define MAXCHAR 1024

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

float* count_emp_probs(const char* text) {
    long* letter_frequency = malloc(ALPH_LEN * sizeof(long));
    for (int i = 0; i < ALPH_LEN; ++i) {
        letter_frequency[i] = 0;
    }

    size_t len = strlen(text);
    long letter_count = 0;
    for (long i = 0; i < len; ++i) {
        char letter = text[i];
        if (letter >= 'A' && letter <= 'Z') {
            letter += 'a' - 'A';
        }
        if (letter < 'a' || letter > 'z') {
            continue;
        }
        int p_idx = letter - 'a';
        ++letter_count;
        ++letter_frequency[p_idx];
    }

    float* probabilities = malloc(ALPH_LEN * sizeof(float));
    for (int i = 0; i < ALPH_LEN; ++i) {
        probabilities[i] = letter_frequency[i] / (float) letter_count;
    }
    free(letter_frequency);

    return probabilities;
}

const char* getfield(char* line, int num) {
    const char* tok;
    for (tok = strtok(line, ",");
        tok && *tok;
        tok = strtok(NULL, ",")) {
        if (!--num)
            return tok;
    }
    return NULL;
}

float* read_emp_probs(const char* filename) {
    float* probabilities = malloc(ALPH_LEN * sizeof(float));
    FILE* f = fopen(filename, "r");

    char row[MAXCHAR];
    int row_number = 0;
    while (fgets(row, MAXCHAR, f)) {
        if (row_number++ == 0) {
            continue;
        }

        char* dup;
        dup = strdup(row);
        char letter = getfield(dup, 1)[0];
        dup = strdup(row);
        float prob = atof(getfield(dup, 2));
        free(dup);

        int p_idx = letter - 'a';
        probabilities[p_idx] = prob;
    }

    return probabilities;
}

float distance(const float* lang, const float* emp_probs, const int shift) {
    float distance = 0;
    for (int i = 0; i < ALPH_LEN; ++i) {
        float lang_prob = lang[i];
        float emp_prob = emp_probs[(i + shift) % ALPH_LEN];
        float diff = (lang_prob - emp_prob);
        distance += diff * diff;
    }
    return distance;
}

char find_key(const float* lang, const float* emp_probs) {
    int min_shift = 0;
    float min_dist = __FLT_MAX__;
    for (int shift = 0; shift < ALPH_LEN; ++shift) {
        float dist = distance(lang, emp_probs, shift);
        if (dist < min_dist) {
            min_shift = shift;
            min_dist = dist;
        }
    }
    return 'a' + min_shift;
}

int main(int argc, char const* argv[]) {
    if (argc != 3) {
        printf("Wrong number of arguments: %d.\n", argc);
        exit(1);
    }
    char* content = read_file("text_copy.txt");
    float* emp_probs = count_emp_probs(content);
    float* lang = read_emp_probs("braten.csv");
    char key = find_key(lang, emp_probs);
    printf("Text can probably be decrypted with: %c\n", key);
    return 0;
}

// Usage: find_key filename lang
// Example: find_key crypt.txt braten.csv