//
// Created by Christopher Szatmary on 2018-02-19.
//

#include <stdlib.h>
#include <config.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "install.h"
#include "utils.h"

/* Steps taken by install function
 * Check if file exists
 * Check that it's an executable
 * Check that the install directory exists
 * Copy executable to install directory
 * symlink executable to /usr/local/bin
 */

int install(const char *file_name) {
    struct stat sb;

    printf("Installing %s ...\n", file_name);
    verbose_print("Checking %s\n", file_name);

    // Check if file exists
    if (stat(file_name, &sb) == -1) {
        fprintf(stderr, "ERROR: File does not exist!\n");
        return EXIT_FAILURE;
    }

    // Check if user has execute permissions
    verbose_print("Checking if file is executable\n");
    if(!(sb.st_mode & S_IXUSR)) {
        fprintf(stderr, "ERROR: Not a valid executable. Cannot install.\n");
        return EXIT_FAILURE;
    }

    // Check if the install directory exists
    verbose_print("Checking if install directory exists\n");
    if (!check_file_exists(config_data->install_location)) {
        fprintf(stderr, "ERROR: %s does not exist!\nRun `attic setup` to set it up\n", config_data->install_location);
        return EXIT_FAILURE;
    }

    verbose_print("Install directory exists\n");

    printf("Moving %s to %s\n", file_name, config_data->install_location);

    char path[PATH_SIZE];
    join_path(config_data->install_location, file_name, path, PATH_SIZE);

    copy_file(file_name, path, MAX_RX_PERM);
    printf("Symlinking %s to /usr/local/bin\n", file_name);

    char symlink_path[PATH_SIZE];
    join_path("/usr/local/bin", file_name, symlink_path, PATH_SIZE);

    // Try symlinking to /usr/local/bin and report any errors
    if (symlink(path, symlink_path) == -1) {
        fprintf(stderr, "Error occurred while symlinking:\n%s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Successfully installed %s!\n", file_name);
    return EXIT_SUCCESS;
}