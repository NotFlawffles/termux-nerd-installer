#include "../include/fontinstaller.h"


NerdFont* new_nerd_font(char* name, char* url) {
    NerdFont* nerd_font = malloc(sizeof(NerdFont));
    nerd_font->name = name;
    nerd_font->url = url;
    return nerd_font;
}

bool is_termux_enviroment(void) {
    struct stat stat_buffer;
    return stat(TERMUX_DIRECTORY, &stat_buffer) == 0;
}

bool check_fonts_directory(void) {
    struct stat stat_buffer;
    return stat(FONTS_DIRECTORY, &stat_buffer) == 0;
}

char** list_installed_fonts(void) {
    char** fonts = malloc(sizeof(char*));
    size_t fonts_size = 0;

    DIR* fonts_directory = opendir(FONTS_DIRECTORY);
    struct dirent* reader;

    while ((reader = readdir(fonts_directory))) {
        if (*reader->d_name == '.')
            continue;

        fonts = realloc(fonts, sizeof(fonts) * (1 + fonts_size));
        fonts[fonts_size] = malloc(sizeof(strlen(reader->d_name)));
        memcpy(fonts[fonts_size++], reader->d_name, strlen(reader->d_name));
    }

    return fonts_size ? fonts : NULL;
}

bool font_is_installed(char* name) {
    char* full_name = malloc(strlen(FONTS_DIRECTORY) + strlen(name) + 6);
    snprintf(full_name, strlen(FONTS_DIRECTORY) + strlen(name) + 6, "%s/%s.ttf", FONTS_DIRECTORY, name);
    struct stat stat_buffer;
    return stat(full_name, &stat_buffer) == 0;
}

unsigned short get_terminal_width(void) {
    struct winsize window_size;
    ioctl(1, TIOCGWINSZ, &window_size);
    return window_size.ws_col;
}

char* get_url(char* name) {
    NerdFont* available_fonts[55] = {
        _3270,
        AGAVE,
        ANONYMICE_PRO,
        ARIMO,
        AURULENT_SANS_MONO,
        BIG_BLUE_TERM,
        BITSTROM_WERA_SANS_MONO,
        CASCAYDIA_COVE,
        BLEX_MONO,
        CODE_NEW_ROMAN,
        COMIC_SHANNS_MONO,
        COUSINE,
        DADDY_TIME_MONO,
        DEJAVU_SANS_MONO,
        DROID_SANS_MONO,
        FANTASQUE_SANS_MONO,
        FIRA_CODE,
        FIRA_MONO,
        GOHU,
        GO_MONO,
        HACK,
        HASKLUG,
        HEAVY_DATA,
        HURMIT,
        IM_WRITING,
        INCONSOLATA,
        INCONSOLATA_GO,
        INCONSOLATA_LGC,
        IOSEVKA,
        IOSEVKA_TERM,
        JETBRAINS_MONO_LIGATURES,
        JETBRAINS_MONO_NO_LIGATURES,
        LEKTON,
        LIBERATION_MONO,
        LILEX,
        MESLO,
        MONOFUR,
        MONOID,
        MONONOKI,
        M_PLUS_CODE,
        NOTO_MONO,
        OPEN_DYSLEXIC_MONO,
        OVERPASS_MONO,
        PRO_FONT,
        PROGGY_CLEAN,
        ROBOTO_MONO,
        SHURE_TECH_MONO,
        SAUCE_CODE_MONO,
        SPACE_MONO,
        SYMBOLS_ONLY,
        TERMINESS,
        TINOS,
        UBUNTU,
        UBUNTU_MONO,
        VICTOR_MONO
    };

    for (int i = 0; i < 54; i++)
        if (memcmp(available_fonts[i]->name, name, strlen(available_fonts[i]->name)) == 0)
            return available_fonts[i]->url;

    return NULL;
}

char* font_path_as_name(char* font_path) {
    char* result = malloc(strlen(font_path - 4));
    memcpy(result, font_path, strlen(font_path) - 4);
    return result;
}

int getch(void) {
    struct termios old_attribute, new_attribute;
    tcgetattr(STDIN_FILENO, &old_attribute);
    new_attribute = old_attribute;
    new_attribute.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attribute);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old_attribute);
    return ch;
}
