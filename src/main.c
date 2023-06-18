#include "../include/fontinstaller.h"


void help_message(char* executable_name) {
    printf("\n\033[36mUsage\033[0m:\n    %s <command> <subcommand>\n\n    (\n       \033[35mlist\033[0m    [available|installed]\n       \033[35mremove\033[0m  <font-name>\n       \033[35minstall\033[0m <font-name>\n       \033[35mset\033[0m     <font-name>\n    )\n\n", executable_name);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        help_message(*argv);
        return 1;
    }

    if (memcmp(argv[1], "list", strlen(argv[1])) == 0) {
        if (memcmp(argv[2], "installed", strlen(argv[2])) == 0)
            cli_list_installed_fonts();
        
        else if (memcmp(argv[2], "available", strlen(argv[2])) == 0)
            cli_list_available_fonts();

        else {
            fprintf(stderr, "%s: Unknown subcommand \"%s\".\n", *argv, argv[2]);
        }
    } else if (memcmp(argv[1], "remove", strlen(argv[1])) == 0)
        cli_remove(*argv, argv[2]);

    else if (memcmp(argv[1], "install", strlen(argv[1])) == 0)
        cli_install(*argv, argv[2]);

    else if (memcmp(argv[1], "set", strlen(argv[1])) == 0)
        cli_set(*argv, argv[2]);

    else
        fprintf(stderr, "%s: Unknown command \"%s\".\n", *argv, argv[1]);
}
