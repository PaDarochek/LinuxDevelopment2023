#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct range
{
    int start;
    int stop;
    int step;
    int cur_value;
} range;

void argparse(int argc, char *argv[], int *start, int *stop, int *step)
{
    if (argc < 1 || argc > 4)
    {
        printf("Incorrect args number\n");
        _Exit(1);
    }
    if (argc == 1)
    {
        printf("Usage:\t%s [ARGS]\n", argv[0]);
        printf("  ARGS: [start[ stop[ step]]]\n");
        return;
    }

    *step = 1;
    if (argc == 2)
    {
        *start = 0;
        *stop = atoi(argv[1]);
        return;
    }

    *start = atoi(argv[1]);
    *stop = atoi(argv[2]);
    if (argc > 3)
    {
        *step = atoi(argv[3]);
    }
}

void range_init(range *I)
{
    I->cur_value = I->start;
}

bool range_run(range *I)
{
    return (I->step > 0 && I->cur_value < I->stop) || (I->step < 0 && I->cur_value > I->stop);
}

void range_next(range *I)
{
    I->cur_value += I->step;
}

int range_get(range *I)
{
    return I->cur_value;
}

int main(int argc, char *argv[])
{
    range I;
    argparse(argc, argv, &I.start, &I.stop, &I.step);
    for (range_init(&I); range_run(&I); range_next(&I))
        printf("%d\n", range_get(&I));
    return 0;
}