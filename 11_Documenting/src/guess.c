/** @mainpage Guessing game program
 * @copydetails program
 */
/** @page program Guessing game program
 * This is free and unencumbered software released into the public domain.
 *
 * The program suggests you to play in a guessing game. You pick a number
 * between 1 and 100 and the program will guess it.
 * 
 * The program will ask you questions that you should answer. Possible variants
 * for the answers that the program can recognize are shown in the brackets
 * after the question.
 * 
 * Be careful that the case of the letters in answers make sence.
 * 
 * Option '-r' allows you to represent all the numbers in the Roman numeral
 * system.
 */

#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

/** @file guess.c
 * Implementation
 * 
 * Guessing is made by binary search. Each time the program asks
 * the user whether his number is greater than the middle of the
 * possible interval. Each answer halves the interval.
 * 
 * The representation for all numbers between 1 and 100 in the
 * Roman numeral system is stored in an array. The translation
 * is made before printing messages.
 * 
 * Guessing is made while the interval contains more than one number.
 * In the end the only left value is showed to the user.
 */

/// Wrapper for gettext function
#define _(STRING) gettext(STRING)
/// Path to locale file
#define LOCALE_PATH "po"

/// String representations for Roman numbers between 1 and 100
static char *roman_nums[] = {
    "I", "II", "III", "IV", "V", "VI", "VII",
    "VIII", "IX", "X", "XI", "XII", "XIII", "XIV",
    "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI",
    "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII",
    "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV",
    "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII",
    "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX",
    "L", "LI", "LII", "LIII", "LIV", "LV", "LVI",
    "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII",
    "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX",
    "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII",
    "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV",
    "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI",
    "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII",
    "XCIX", "C"};

/** Translate the Roman number @p num to the Arabic number.
 *
 * @param num The Roman number
 * @return The corresponding Arabic number
 * 
 * Translation is made by searching the matching string in
 * roman_nums array.
 */
int roman2arab(char *num)
{
    size_t i = 0;
    for (; i < 100; ++i)
    {
        if (!strcmp(num, roman_nums[i]))
        {
            break;
        }
    }
    if (i < 100)
    {
        return i + 1;
    }
    return -1;
}

/** Translate the Arabic number @p num to the Roman number.
 *
 * @param num The Arabic number
 * @return The corresponding Roman number
 * 
 * Translation is made by taking the corresponding entry from
 * roman_nums array.
 */
char *arab2roman(size_t num)
{
    if (num <= 100)
    {
        return roman_nums[num - 1];
    }
    return "";
}

/// Print help message.
void print_help()
{
    printf(_("Usage: ./guess [OPTIONS]\n"));
    printf(_("    OPTIONS:\n"));
    printf(_("        --help  print help message\n"));
    printf(_("        -r      use Roman numbers\n"));
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALE_PATH);
    textdomain("guess");

    int roman = 0;
    if (argc > 1)
    {
        if (!strcmp(argv[1], "-r"))
        {
            roman = 1;
        }
        else if (!strcmp(argv[1], "--help"))
        {
            print_help();
            return 0;
        }
    }

    if (roman)
    {
        printf(_("Choose number between %s and %s\n"), arab2roman(1), arab2roman(100));
    }
    else
    {
        printf(_("Choose number between 1 and 100\n"));
    }

    size_t left = 1;
    size_t right = 100;
    char answer[30];
    while (left != right)
    {
        if (roman)
        {
            printf(_("Is your number greater that %s? (yes/no)\n"),
                   arab2roman((left + right) / 2));
        }
        else
        {
            printf(_("Is your number greater that %lu? (yes/no)\n"),
                   (left + right) / 2);
        }

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
    if (roman)
    {
        printf(_("Your number is %s\n"), arab2roman(right));
    }
    else
    {
        printf(_("Your number is %lu\n"), right);
    }
    return 0;
}
