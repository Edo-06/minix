#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void print_tree(const char *dir_path, int depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char path[1024];

    if (!(dir = opendir(dir_path))) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        if (lstat(path, &statbuf) == -1) continue;

        for (int i = 0; i < depth; i++) {
            printf("│   ");
        }

        if (S_ISDIR(statbuf.st_mode)) {
            printf("├── [%s]\n", entry->d_name);
        
            print_tree(path, depth + 1);
        } else {
            printf("└── %s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *start_node;

    if (argc < 2) {
        start_node = ".";
    } else {
        start_node = argv[1];
    }

    printf("%s\n", start_node);
    print_tree(start_node, 0);

    return 0;
}