#include "../include/fontinstaller.h"

static char* Ongoing = NULL;

void cli_list_installed_fonts(void) {
    char** installed_fonts = list_installed_fonts();

    if (!installed_fonts) {
        printf("You have no installed fonts yet.\n");
        return;
    }

    printf("\n\033[36mInstalled fonts:\033[0m\n");

    for (int i = 0; installed_fonts[i]; i++)
        printf("    %s\n", installed_fonts[i]);
    
    putc('\n', stdout);
}

void cli_list_available_fonts(void) {
    char* available_fonts[55] = {
        _3270->name,
        AGAVE->name,
        ANONYMICE_PRO->name,
        ARIMO->name,
        AURULENT_SANS_MONO->name,
        BIG_BLUE_TERM->name,
        BITSTROM_WERA_SANS_MONO->name,
        CASCAYDIA_COVE->name,
        BLEX_MONO->name,
        CODE_NEW_ROMAN->name,
        COMIC_SHANNS_MONO->name,
        COUSINE->name,
        DADDY_TIME_MONO->name,
        DEJAVU_SANS_MONO->name,
        DROID_SANS_MONO->name,
        FANTASQUE_SANS_MONO->name,
        FIRA_CODE->name,
        FIRA_MONO->name,
        GOHU->name,
        GO_MONO->name,
        HACK->name,
        HASKLUG->name,
        HEAVY_DATA->name,
        HURMIT->name,
        IM_WRITING->name,
        INCONSOLATA->name,
        INCONSOLATA_GO->name,
        INCONSOLATA_LGC->name,
        IOSEVKA->name,
        IOSEVKA_TERM->name,
        JETBRAINS_MONO_LIGATURES->name,
        JETBRAINS_MONO_NO_LIGATURES->name,
        LEKTON->name,
        LIBERATION_MONO->name,
        LILEX->name,
        MESLO->name,
        MONOFUR->name,
        MONOID->name,
        MONONOKI->name,
        M_PLUS_CODE->name,
        NOTO_MONO->name,
        OPEN_DYSLEXIC_MONO->name,
        OVERPASS_MONO->name,
        PRO_FONT->name,
        PROGGY_CLEAN->name,
        ROBOTO_MONO->name,
        SHURE_TECH_MONO->name,
        SAUCE_CODE_MONO->name,
        SPACE_MONO->name,
        SYMBOLS_ONLY->name,
        TERMINESS->name,
        TINOS->name,
        UBUNTU->name,
        UBUNTU_MONO->name,
        VICTOR_MONO->name
    };

    putc('\n', stdout);

    for (int i = 0; i < 55; i++) {
        printf("    - %s", available_fonts[i]);
        bool is_installed = font_is_installed(available_fonts[i]);
        
        for (unsigned short j = 0; j < get_terminal_width() / 2 - strlen(available_fonts[i]); j++)
            putc(' ', stdout);

        printf("%s\n\n", is_installed ? "\033[32minstalled\033[0m" : "\033[37mnot installed\033[0m");
    }
}

void cli_remove(char* executable_name, char* name) {
    char** installed_fonts = list_installed_fonts();
    char *name_as_path = font_name_as_path(name);
    char* path = path_by_font_name(name);
    
    if (!installed_fonts) {
        printf("You have no installed fonts yet.\n");
        return;
    }

    for (int i = 0; installed_fonts[i]; i++)
        if (memcmp(installed_fonts[i], name_as_path, strlen(installed_fonts[i])) == 0) {
            printf("Are you sure? (y/N): ");
        
            if (getch() == 'y')
                remove(path);

            putc('\n', stdout);
            return;
        }

    printf("%s: \"%s\" is not installed therefore not removed.\n", executable_name, name);
}

void cleanup(int sig) {
    (void) sig;

    if (Ongoing) {
        printf("\ncleaning...\n");
        remove(Ongoing);
        printf("\e[?25h");
        exit(0);
    }
}

int random_range(int minimum, int maximum) {
    return rand() % (maximum + 1 - minimum) + minimum;
}

int download_progress(void* pointer, double total_to_download, double now_downloaded, double total_to_upload, double now_uploaded) {
    (void) pointer;
    (void) total_to_upload;
    (void) now_uploaded;

    if (total_to_download <= 0.0) {
        return 0;
    }

    int total_space = get_terminal_width() / 2;
    double fraction_downloaded = now_downloaded / total_to_download;

    int space = (int) round(fraction_downloaded * total_space);

    printf("\033[2K\r%3.0f%% [", fraction_downloaded * 100);

    int i = 0;

    for (; i < space; i++)
        printf("\033[32m=");

    printf(">\033[0m");

    for (; i < total_space - 1; i++)
        putc(' ', stdout);

    printf("]");
    fflush(stdout);
    return 0; 
}

void cli_install(char* executable_name, char* name) {
    signal(SIGINT, cleanup);
    srand(time(0));
    CURL* curl = curl_easy_init();
    char* url = get_url(name);

    if (!url) {
        fprintf(stderr, "%s: \"%s\" is not available.\n", executable_name, name);
        return;
    }

    printf("\e[?25l");
    char* path = malloc(strlen(FONTS_DIRECTORY) + strlen(name) + 6);
    snprintf(path, strlen(FONTS_DIRECTORY) + strlen(name) + 6, "%s/%s.ttf", FONTS_DIRECTORY, name);
    Ongoing = malloc(strlen(path));
    memcpy(Ongoing, path, strlen(path));

    FILE* file = fopen(path, "w");

    printf("Downloading %s...\n", name);

    char* splash_text[] = {
        "this will not take long, will it?",
        "oh shoot",
        "let us get monofied!",
        "meow",
        "hai meqa :P"
    };

    char* random_splash_text = splash_text[random_range(0, 4)];

    printf("\033[3m%s\033[0m\n\n", random_splash_text);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, download_progress);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    printf("\n%s has been successfuly installed.\n\e[?25h", name);
}

void cli_set(char* executable_name, char* name) {
    char** installed_fonts = list_installed_fonts();

    if (!installed_fonts) {
        printf("You have no installed fonts yet.\n");
        return;
    }

    if (!font_is_installed(name)) {
        printf("%s: %s is not installed.\n", executable_name, name);
        return;
    }

    remove(TERMUX_FONT_PATH);
    copy(path_by_font_name(name), TERMUX_FONT_PATH);
    system("termux-reload-settings");
}
