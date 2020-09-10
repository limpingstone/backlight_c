#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/stat.h>

#define BL_PATH "/sys/class/backlight/amdgpu_bl0/brightness"


void print_usage() {
    fprintf(stderr, "Usage: backlight [OPTION] [VALUE]\nChange screen backlight brightness\n");
}


int inc_brightness(char* str_current, char* str_inc) {

    char* endptr;
    int current_val = strtol(str_current, &endptr, 10);
    if (*endptr != '\0') {
        return -1;
    }

    current_val += strtol(str_inc, &endptr, 10);
    if (*endptr != '\0') {
        return -1;
    }

    return (current_val > 255) ? 255 : current_val;
}


int dec_brightness(char* str_current, char* str_dec) {

    char* endptr;
    int current_val = strtol(str_current, &endptr, 10);
    if (*endptr != '\0') {
        return -1;
    }

    current_val -= strtol(str_dec, &endptr, 10);
    if (*endptr != '\0') {
        return -1;
    }

    return (current_val < 0) ? 0 : current_val;
}


void write_to_file(int fd, int new_val) {
    char write_buff[64];
    sprintf(write_buff, "%d", new_val);

    if (write(fd, write_buff, strlen(write_buff)) < 0) {
        perror("write");
    }
}


int main(int argc, char *argv[]) {

    if (argc != 3) {
        print_usage();

    } else {
        // open file for changing screen brightness
        int fd = open(BL_PATH, O_RDWR);

        // If the brightness file is successfully opened
        if (fd > -1) {
            char fd_buff[64];
            memset(fd_buff, 0, sizeof(fd_buff));

            // read in current brightness
            for (size_t i = 0; i < sizeof(fd_buff); i++) {

                // read error
                if (read(fd, fd_buff + i, 1) < 0) {
                    perror("read");
                    return 1;
                }

                // reached end of file
                if (fd_buff[i] == '\n') {
                    fd_buff[i] = '\0';
                    break;
                }
            }

            printf("current brightness: %s\n", fd_buff);

            // increase or decrease brightness
            int current_val = -1;
            if (!strcmp(argv[1], "inc")) {
                current_val = inc_brightness(fd_buff, argv[2]);

            } else if (!strcmp(argv[1], "dec")) {
                current_val = dec_brightness(fd_buff, argv[2]);

            } else {
                fprintf(stderr, "invalid option \'%s\'\n\n", argv[1]);
                print_usage();
            }

            printf("current brightness: %d\n", current_val);

            // if new brightness value is valid then write to file
            if (current_val > -1)
                write_to_file(fd, current_val);


            // close the file after changing brightness
            if (close(fd) < 0)
                perror("close");

            return 0;
        }

        perror("open");
    }

    return -1;
}

