#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Room
{
    int i;
    int j;
} Room;

enum
{
    SIZE = 13,
    DIM_ROOMS = 6
};

void fill_unreachable(char **maze)
{
    for (size_t i = 0; i < SIZE; ++i)
    {
        for (size_t j = 0; j < SIZE; ++j)
        {
            if (i % 2 && j % 2)
            {
                maze[i][j] = '.';
            }
            else
            {
                maze[i][j] = '#';
            }
        }
    }
}

void push_room(Room room, Room *rooms, size_t *begin, size_t *end)
{
    if (*end == DIM_ROOMS * DIM_ROOMS - 1)
    {
        printf("Error while pushing room\n");
        exit(1);
    }
    rooms[(*end)++] = room;
}

Room pop_room(Room *rooms, size_t *begin, size_t *end)
{
    if (*begin >= *end)
    {
        printf("Error while popping room\n");
        exit(1);
    }
    ++*begin;
    return rooms[*begin - 1];
}

void remove_wall(char **maze, Room first, Room second)
{
    size_t i = first.i * 2 + 1;
    if (first.i != second.i)
    {
        i = (first.i + second.i) / 2 * 2 + 2;
    }
    size_t j = first.j * 2 + 1;
    if (first.j != second.j)
    {
        j = (first.j + second.j) / 2 * 2 + 2;
    }
    maze[i][j] = '.';
}

Room check_neighbors(Room cur_room, bool **visited)
{
    int i = cur_room.i;
    int j = cur_room.j;
    if (i < 0 || j < 0 || i >= DIM_ROOMS || j >= DIM_ROOMS)
    {
        printf("Incorrect room\n");
        exit(1);
    }

    bool neighbors[4] = {false, false, false, false};
    size_t num_neighbors = 0;
    if (i > 0 && !visited[i - 1][j])
    {
        neighbors[0] = true;
        num_neighbors++;
    }
    if (j > 0 && !visited[i][j - 1])
    {
        neighbors[1] = true;
        num_neighbors++;
    }
    if (i < DIM_ROOMS - 1 && !visited[i + 1][j])
    {
        neighbors[2] = true;
        num_neighbors++;
    }
    if (j < DIM_ROOMS - 1 && !visited[i][j + 1])
    {
        neighbors[3] = true;
        num_neighbors++;
    }

    Room room;
    if (!num_neighbors)
    {
        room.i = room.j = -1;
        return room;
    }
    size_t idx = rand() % 4;
    while (!neighbors[idx])
    {
        idx = rand() % 4;
    }
    int i_idx;
    int j_idx;
    switch (idx)
    {
        case 0:
            i_idx = i - 1;
            j_idx = j;
            break;
        case 1:
            i_idx = i;
            j_idx = j - 1;
            break;
        case 2:
            i_idx = i + 1;
            j_idx = j;
            break;
        case 3:
            i_idx = i;
            j_idx = j + 1;
            break;
    }
    room.i = i_idx;
    room.j = j_idx;
    return room;
}

Room choose_rand_room(bool **visited)
{
    size_t i = rand() % DIM_ROOMS;
    size_t j = rand() % DIM_ROOMS;
    while (visited[i][j])
    {
        i = rand() % DIM_ROOMS;
        j = rand() % DIM_ROOMS;
    }
    Room room = {i, j};
    return room;
}

void generate_maze(char **maze)
{
    bool **visited = malloc(DIM_ROOMS * sizeof(bool *));
    for (size_t i = 0; i < DIM_ROOMS; ++i)
    {
        visited[i] = calloc(DIM_ROOMS, sizeof(bool));
    }

    Room rooms[DIM_ROOMS * DIM_ROOMS];
    size_t rooms_begin = 0;
    size_t rooms_end = 0;
    size_t num_visited = 0;
    Room cur_room = {0, 0};
    visited[0][0] = true;
    num_visited++;

    while (num_visited != DIM_ROOMS * DIM_ROOMS)
    {
        Room neighbor = check_neighbors(cur_room, visited);
        if (neighbor.i != -1)
        {
            push_room(cur_room, rooms, &rooms_begin, &rooms_end);
            remove_wall(maze, cur_room, neighbor);
            cur_room = neighbor;
            visited[cur_room.i][cur_room.j] = true;
            num_visited++;
        }
        else if (rooms_begin != rooms_end)
        {
            cur_room = pop_room(rooms, &rooms_begin, &rooms_end);
        }
        else
        {
            cur_room = choose_rand_room(visited);
            visited[cur_room.i][cur_room.j] = true;
            num_visited++;
        }
    }
}

void print_maze(char **maze)
{
    for (size_t i = 0; i < SIZE; ++i)
    {
        printf("%.*s\n", (int)SIZE, maze[i]);
    }
}

void free_maze(char **maze)
{
    for (size_t i = 0; i < SIZE; ++i)
    {
        free(maze[i]);
    }
    free(maze);
}

int main()
{
    srand(time(NULL));

    char **maze = malloc(SIZE * sizeof(char *));
    for (size_t i = 0; i < SIZE; ++i)
    {
        maze[i] = malloc(SIZE * sizeof(char));
    }
    fill_unreachable(maze);

    generate_maze(maze);
    print_maze(maze);

    free_maze(maze);
    return 0;
}
