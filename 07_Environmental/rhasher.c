#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "rhash.h"

#include "config.h"

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

int main()
{
    char *buf = NULL;
    size_t n = 0;
    unsigned char digest[64];
    char output[130];

    int is_term = isatty(fileno(stdin));
    char *prompt = "";
    if (is_term)
    {
        prompt = "> ";
    }
    rhash_library_init();
#ifdef USE_READLINE
    while ((buf = readline(prompt)))
    {
        if (buf && *buf)
        {
            add_history(buf);
        }
#else
    printf("%s", prompt);
    while (getline(&buf, &n, stdin) != EOF)
    {
#endif
        char *alg_name = strtok(buf, " ");
        if (!alg_name)
        {
            fprintf(stderr, "Please provide 2 words: hashing algorithm name and filename/string\n");
#ifndef USE_READLINE
            printf("%s", prompt);
#endif
            free(buf);
            continue;
        }
        char *str = strtok(NULL, " ");
        if (strlen(str) > 0 && str[strlen(str) - 1] == '\n')
        {
            str[strlen(str) - 1] = 0;
        }
        if (!str || !strlen(str))
        {
            fprintf(stderr, "Please provide second word: filename/string\n");
#ifndef USE_READLINE
            printf("%s", prompt);
#endif
            free(buf);
            continue;
        }

        enum rhash_ids alg;
        int islower = alg_name[0] >= 'a' && alg_name[0] <= 'z';
        for (int i = 0; i < strlen(alg_name); ++i)
        {
            alg_name[i] = toupper(alg_name[i]);
        }
        if (!strcmp(alg_name, "MD5"))
        {
            alg = RHASH_MD5;
        }
        else if (!strcmp(alg_name, "SHA1"))
        {
            alg = RHASH_SHA1;
        }
        else if (!strcmp(alg_name, "TTH"))
        {
            alg = RHASH_TTH;
        }
        else
        {
            fprintf(stderr, "Unknown algorithm: %s\n", alg_name);
#ifndef USE_READLINE
            printf("%s", prompt);
#endif
            free(buf);
            continue;
        }

        if (str[0] == '\"')
        {
            if (rhash_msg(alg, &str[1], strlen(str) - 1, digest) < 0)
            {
                fprintf(stderr, "Error while computing digest: %s: %s\n", str, strerror(errno));
#ifndef USE_READLINE
                printf("%s", prompt);
#endif
                free(buf);
                continue;
            }
        }
        else if (rhash_file(alg, str, digest) < 0)
        {
            fprintf(stderr, "Error while computing digest: %s: %s\n", str, strerror(errno));
#ifndef USE_READLINE
            printf("%s", prompt);
#endif
            free(buf);
            continue;
        }

        if (islower)
        {
            rhash_print_bytes(output, digest, rhash_get_digest_size(alg), RHPR_BASE64);
        }
        else
        {
            rhash_print_bytes(output, digest, rhash_get_digest_size(alg), RHPR_HEX);
        }
        printf("%s\n", output);
#ifndef USE_READLINE
        printf("%s", prompt);
#endif
        free(buf);
    }

    return 0;
}
