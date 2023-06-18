#ifndef FONT_INSTALLER_H
#define FONT_INSTALLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <malloc.h>
#include <dirent.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

#include "utils.h"

#define _3270 new_nerd_font("3270", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/3270/Regular/3270NerdFontMono-Regular.ttf")
#define AGAVE new_nerd_font("agave", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Agave/AgaveNerdFontMono-Regular.ttf")
#define ANONYMICE_PRO new_nerd_font("anonymice-pro", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/AnonymousPro/Regular/AnonymiceProNerdFontMono-Regular.ttf")
#define ARIMO new_nerd_font("arimo", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Arimo/Regular/ArimoNerdFont-Regular.ttf")
#define AURULENT_SANS_MONO new_nerd_font("aurulent-sans-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/AurulentSansMono/AurulentSansMNerdFontMono-Regular.otf")
#define BIG_BLUE_TERM new_nerd_font("big-blue-term", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/BigBlueTerminal/BigBlueTerm437NerdFontMono-Regular.ttf")
#define BITSTROM_WERA_SANS_MONO new_nerd_font("bitstrom-wera-sans-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/BitstreamVeraSansMono/Regular/BitstromWeraNerdFontMono-Regular.ttf")
#define CASCAYDIA_COVE new_nerd_font("caskaydia-cove", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/CascadiaCode/Regular/CaskaydiaCoveNerdFontMono-Regular.ttf")
#define BLEX_MONO new_nerd_font("blex-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/IBMPlexMono/Mono/BlexMonoNerdFontMono-Regular.ttf")
#define CODE_NEW_ROMAN new_nerd_font("code-new-roman", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/CodeNewRoman/Regular/CodeNewRomanNerdFontMono-Regular.otf")
#define COMIC_SHANNS_MONO new_nerd_font("comic-shanns-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/ComicShannsMono/ComicShannsMonoNerdFontMono-Regular.otf")
#define COUSINE new_nerd_font("cousine", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Cousine/Regular/CousineNerdFontMono-Regular.ttf")
#define DADDY_TIME_MONO new_nerd_font("daddy-time-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/DaddyTimeMono/DaddyTimeMonoNerdFontMono-Regular.ttf")
#define DEJAVU_SANS_MONO new_nerd_font("dejavu-sans-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/DejaVuSansMono/Regular/DejaVuSansMNerdFontMono-Regular.ttf")
#define DROID_SANS_MONO new_nerd_font("droid-sans-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/DroidSansMono/DroidSansMNerdFontMono-Regular.otf")
#define FANTASQUE_SANS_MONO new_nerd_font("fantasque-sans-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/FantasqueSansMono/Regular/FantasqueSansMNerdFontMono-Regular.ttf")
#define FIRA_CODE new_nerd_font("fira-code", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/FiraCode/Regular/FiraCodeNerdFontMono-Regular.ttf")
#define FIRA_MONO new_nerd_font("fira-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/FiraMono/Regular/FiraMonoNerdFontMono-Regular.otf")
#define GOHU new_nerd_font("gohu", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Gohu/uni-14/GohuFontuni14NerdFontMono-Regular.ttf")
#define GO_MONO new_nerd_font("go-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Go-Mono/Regular/GoMonoNerdFontMono-Regular.ttf")
#define HACK new_nerd_font("hack", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Hack/Regular/HackNerdFontMono-Regular.ttf")
#define HASKLUG new_nerd_font("hasklug", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Hasklig/Regular/HasklugNerdFontMono-Regular.otf")
#define HEAVY_DATA new_nerd_font("heavy-data", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/HeavyData/HeavyDataNerdFont-Regular.ttf")
#define HURMIT new_nerd_font("hurmit", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Hermit/Regular/HurmitNerdFontMono-Regular.otf")
#define IM_WRITING new_nerd_font("im-writing", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/iA-Writer/Mono/Regular/iMWritingMonoNerdFontMono-Regular.ttf")
#define INCONSOLATA new_nerd_font("inconsolata", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Inconsolata/InconsolataNerdFontMono-Regular.ttf")
#define INCONSOLATA_GO new_nerd_font("inconsolata-go", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/InconsolataGo/Regular/InconsolataGoNerdFontMono-Regular.ttf")
#define INCONSOLATA_LGC new_nerd_font("inconsolata-lgc", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/InconsolataLGC/Regular/InconsolataLGCNerdFontMono-Regular.ttf")
#define IOSEVKA new_nerd_font("iosevka", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Iosevka/Regular/IosevkaNerdFontMono-Regular.ttf")
#define IOSEVKA_TERM new_nerd_font("iosevka-term", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/IosevkaTerm/Regular/IosevkaTermNerdFontMono-Regular.ttf")
#define JETBRAINS_MONO_LIGATURES new_nerd_font("jetbrains-mono-ligatures", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/JetBrainsMono/Ligatures/Regular/JetBrainsMonoNerdFontMono-Regular.ttf")
#define JETBRAINS_MONO_NO_LIGATURES new_nerd_font("jetbrains-mono-no-ligatures", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/JetBrainsMono/NoLigatures/Regular/JetBrainsMonoNLNerdFontMono-Regular.ttf")
#define LEKTON new_nerd_font("lekton", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Lekton/Regular/LektonNerdFontMono-Regular.ttf")
#define LIBERATION_MONO new_nerd_font("liberation-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/LiberationMono/LiterationMonoNerdFontMono-Regular.ttf")
#define LILEX new_nerd_font("lilex", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Lilex/Regular/LilexNerdFontMono-Regular.ttf")
#define MESLO new_nerd_font("meslo", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Meslo/M/Regular/MesloLGMNerdFontMono-Regular.ttf")
#define MONOFUR new_nerd_font("monofur", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Monofur/Regular/MonofurNerdFontMono-Regular.ttf")
#define MONOID new_nerd_font("monoid", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Monoid/Regular/MonoidNerdFontMono-Regular.ttf")
#define MONONOKI new_nerd_font("mononoki", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Mononoki/Regular/MononokiNerdFontMono-Regular.ttf")
#define M_PLUS_CODE new_nerd_font("m-plus-code", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/MPlus/M_Plus_1_code/M%2B1CodeNerdFontMono-Regular.ttf")
#define NOTO_MONO new_nerd_font("noto-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Noto/Mono/NotoMonoNerdFontMono-Regular.ttf")
#define OPEN_DYSLEXIC_MONO new_nerd_font("open-dyslexic-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/OpenDyslexic/Mono-Regular/OpenDyslexicMNerdFontMono-Regular.otf")
#define OVERPASS_MONO new_nerd_font("overpass-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Overpass/Mono/Regular/OverpassMNerdFontMono-Regular.otf")
#define PRO_FONT new_nerd_font("pro-font", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/ProFont/profontiix/ProFontIIxNerdFontMono-Regular.ttf")
#define PROGGY_CLEAN new_nerd_font("proggy-clean", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/ProggyClean/SlashedZero/ProggyCleanSZNerdFontMono-Regular.ttf")
#define ROBOTO_MONO new_nerd_font("roboto-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/RobotoMono/Regular/RobotoMonoNerdFontMono-Regular.ttf")
#define SHURE_TECH_MONO new_nerd_font("shure-tech-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/ShareTechMono/ShureTechMonoNerdFontMono-Regular.ttf")
#define SAUCE_CODE_MONO new_nerd_font("sauce-code-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/SourceCodePro/Regular/SauceCodeProNerdFontMono-Regular.ttf")
#define SPACE_MONO new_nerd_font("space-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/SpaceMono/Regular/SpaceMonoNerdFontMono-Regular.ttf")
#define SYMBOLS_ONLY new_nerd_font("symbols-only", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/NerdFontsSymbolsOnly/SymbolsNerdFontMono-Regular.ttf")
#define TERMINESS new_nerd_font("terminess", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Terminus/Regular/TerminessNerdFontMono-Regular.ttf")
#define TINOS new_nerd_font("tinos", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Tinos/Regular/TinosNerdFont-Regular.ttf")
#define UBUNTU new_nerd_font("ubuntu", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/Ubuntu/Regular/UbuntuNerdFont-Regular.ttf")
#define UBUNTU_MONO new_nerd_font("ubuntu-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/UbuntuMono/Regular/UbuntuMonoNerdFontMono-Regular.ttf")
#define VICTOR_MONO new_nerd_font("victor-mono", "https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/VictorMono/Regular/VictorMonoNerdFontMono-Regular.ttf")

void cli_list_installed_fonts(void);
void cli_list_available_fonts(void);
void cli_remove(char* executable_name, char* name);
void cli_install(char* executable_name, char* name);
void cli_set(char* executable_name, char* name);
int random_range(int minimum, int maximum);

#ifdef __cplsuplus
}
#endif

#endif /* FONT_INSTALLER_H */
