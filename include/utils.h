#ifndef UTILS_H
#define UTILS_H

#define TERMUX_DIRECTORY "environment"
#define FONTS_DIRECTORY  "environment/fonts"

typedef struct {
    char* name;
    char* url;
} NerdFont;

NerdFont* new_nerd_font(char* name, char* url);

bool is_termux_enviroment(void);
bool check_fonts_directory(void);
bool font_is_installed(char* name);
char** list_installed_fonts(void);
NerdFont** list_available_fonts(void);
unsigned short get_terminal_width(void);
char* get_url(char* name);
char* font_path_as_name(char* font_path);
int getch(void);

#endif /* UTILS_H */
