
/* dir_list_sys.c */
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

int main() {
    char buffer[512];
    
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    const char *header = "Name                           Size\n";
    write(1, header, strlen(header));

    struct dirent *entry;
    struct stat file_stat;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        int len = snprintf(buffer, sizeof(buffer), "%-30s %10lld\n", 
                           entry->d_name, (long long)file_stat.st_size);
        
        if (len > 0) {
            write(1, buffer, len);
        }
    }

    closedir(dir);

    return 0;
}
