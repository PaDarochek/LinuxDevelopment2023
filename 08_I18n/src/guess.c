#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "po"

int main()
{
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALE_PATH);
    textdomain("guess");

    printf(_("Choose number between 1 and 100\n"));
    size_t left = 1;
    size_t right = 100;
    char answer[10];
    while (left != right)
    {
        printf(_("Is your number greater that %lu? (yes/no)\n"), (left + right) / 2);
        if (scanf("%9s", answer) != 1)
        {
            continue;
        }
        if (!strcmp(answer, _("yes")))
        {
            left = (left + right) / 2 + 1;
        }
        else if (!strcmp(answer, _("no")))
        {
            right = (left + right) / 2;
        }
    }
    printf(_("Your number is %lu\n"), right);
    return 0;
}
