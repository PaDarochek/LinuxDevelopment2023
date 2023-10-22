#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAXGR 10

void append_str(char **buf, size_t *capacity_buf, size_t *len_buf, char *add_buf, size_t add_len)
{
    if (*len_buf + add_len + 1 >= *capacity_buf)
    {
        *buf = realloc((void *)*buf, *capacity_buf + add_len + 64);
        *capacity_buf += add_len + 64;
    }
    for (int i = 0; i < add_len; ++i)
    {
        (*buf)[(*len_buf)++] = add_buf[i];
    }
    (*buf)[*len_buf] = 0;
}

int main(int argc, char *argv[])
{
    size_t len = 0;
    int chars;
    regex_t regex;
    regmatch_t bags[MAXGR];

    int error = regcomp(&regex, argv[1], REG_EXTENDED);
    if (error != 0)
    {
        char err_buf[1024];
        regerror(error, &regex, err_buf, 1024);
        printf("%.*s\n", 1024, err_buf);
        return -1;
    }
    char *buf;
    if (regexec(&regex, argv[3], MAXGR, bags, 0) == 0)
    {
        int s = bags[0].rm_so, e = bags[0].rm_eo;
        size_t capacity_buf = e - s;
        size_t len_buf = 0;
        buf = malloc((capacity_buf + 1) * sizeof(char));
        buf[len_buf] = 0;
        size_t len_subst = strlen(argv[2]);

        int i = 0;
        while (i < len_subst)
        {
            if (argv[2][i] == '\\')
            {
                if (i < len_subst - 1)
                {
                    switch (argv[2][i + 1])
                    {
                    case '\\':
                    {
                        append_str(&buf, &capacity_buf, &len_buf, "\\", 1);
                        i += 2;
                        break;
                    }
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    {
                        int idx_bag = argv[2][i + 1] - '0';
                        if (bags[idx_bag].rm_so == -1)
                        {
                            printf("Try to get non-existing capture group: \\%d\n", idx_bag);
                            return -1;
                        }
                        int ss = bags[idx_bag].rm_so, ee = bags[idx_bag].rm_eo;
                        append_str(&buf, &capacity_buf, &len_buf, &argv[3][ss], ee - ss);
                        i += 2;
                        break;
                    }
                    default:
                    {
                        append_str(&buf, &capacity_buf, &len_buf, "\\", 1);
                        i++;
                        break;
                    }
                    }
                }
            }
            else
            {
                append_str(&buf, &capacity_buf, &len_buf, &argv[2][i], 1);
                i++;
            }
        }
        printf("%.*s%.*s%.*s\n", s, argv[3], (int)len_buf, buf, (int)(strlen(argv[3]) - e), &argv[3][e]);
        free(buf);
    }
    else
    {
        printf("%s\n", argv[3]);
    }
    regfree(&regex);
    return 0;
}