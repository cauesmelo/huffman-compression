#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char *read_file(char *filename) {
    // open file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open file '%s'\n", filename);
        return NULL;
    }

    // jump to end of file
    fseek(fp, 0, SEEK_END);

    // file size in bytes
    long size = ftell(fp);

    // allocate an array big enough (+1 for '\0')
    char *buffer = malloc(size + 1);

    // jump back to beginning
    fseek(fp, 0, SEEK_SET);

    // buffer -> destination
    // 1 -> size of each item in bytes
    // size -> how many items to read
    // fp -> file to read from
    fread(buffer, 1, size, fp);

    // add null-terminate so it works as a string
    buffer[size] = '\0';

    // close file
    fclose(fp);

    // return string pointer, caller is responsible for calling free
    return buffer;
}

int *build_freq_map(const char *text) {
    int *freq = calloc(256, sizeof(int));

    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char ch_code = text[i];

        freq[ch_code]++;
    }

    return freq;
}

void print_freq_map(int *freq) {
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            if (i >= 32 && i <= 126) {
                printf("'%c' (%d): %d\n", i, i, freq[i]);
            } else {
                printf("0x%02X (%d): %d\n", i, i, freq[i]);
            }
        }
    }
}

typedef struct Node {
    unsigned char ch;
    int freq;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(unsigned char ch, int freq, Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

int main() {
    // Step one: read text
    char *text = read_file("small_sample.txt");

    // Step two: Build frequency map
    int *freq_map = build_freq_map(text);
    print_freq_map(freq_map);

    // Step three: Build a priority queue

    free(text);
    free(freq_map);

    return 0;
}
