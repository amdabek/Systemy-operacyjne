#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_PATH_LEN 2048

int main(void) {
    char input_dir[MAX_PATH_LEN], output_dir[MAX_PATH_LEN];

    printf("Podaj ścieżkę do katalogu wejściowego: ");
    if (scanf("%2047s", input_dir) != 1) {
        fprintf(stderr, "Błąd wczytywania katalogu wejściowego.\n");
        return 1;
    }
    printf("Podaj ścieżkę do katalogu wyjściowego: ");
    if (scanf("%2047s", output_dir) != 1) {
        fprintf(stderr, "Błąd wczytywania katalogu wyjściowego.\n");
        return 1;
    }

    DIR *opened_dir = opendir(input_dir);
    if (!opened_dir) {
        fprintf(stderr, "Błąd: nie można otworzyć katalogu: %s\n", input_dir);
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(opened_dir)) != NULL) {
        char input_path[MAX_PATH_LEN], output_path[MAX_PATH_LEN];

        struct stat st;
        if (stat(input_path, &st) == 0 && S_ISREG(st.st_mode)) {
            size_t len = strlen(entry->d_name);
            if (len >= 4 && strcmp(entry->d_name + len - 4, ".txt") == 0) {
                FILE *input_file = fopen(input_path, "r");
                if (!input_file) {
                    fprintf(stderr, "Błąd otwarcia pliku do odczytu: %s\n", input_path);
                    continue;
                }
                FILE *output_file = fopen(output_path, "w");
                if (!output_file) {
                    fprintf(stderr, "Błąd otwarcia pliku do zapisu: %s\n", output_path);
                    fclose(input_file);
                    continue;
                }
                char file_line[1000];
                while (fgets(file_line, sizeof(file_line), input_file)) {
                    size_t llen = strlen(file_line);
                    if (llen > 0 && file_line[llen - 1] == '\n') {
                        file_line[llen - 1] = '\0';
                        llen--;
                    }
                    for (size_t i = 0; i < llen / 2; i++) {
                        char tmp = file_line[i];
                        file_line[i] = file_line[llen - 1 - i];
                        file_line[llen - 1 - i] = tmp;
                    }
                    fprintf(output_file, "%s\n", file_line);
                }
                fclose(input_file);
                fclose(output_file);
            }
        }
    }

    closedir(opened_dir);
    printf("Zakończono przetwarzanie.\n");
    return 0;
}
