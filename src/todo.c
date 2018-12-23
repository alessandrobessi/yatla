#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "style.h"
#include "list.h"
#include "clear.h"
#include "rm.h"
#include "add.h"
#include "set.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "See usage\n");
        exit(EXIT_FAILURE);
    }

    sqlite3 *db;
    int rc;

    rc = sqlite3_open("/tmp/todo.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    if (strcmp("clear", argv[1]) == 0)
    {
        clear(db);
    }

    if (strcmp("list", argv[1]) == 0)
    {
        list(db, argv);
    }

    if (strcmp("rm", argv[1]) == 0)
    {
        rm(db, argv);
    }

    if (strcmp("set", argv[1]) == 0)
    {
        set(db, argc, argv);
    }

    if (strcmp("add", argv[1]) == 0)
    {
        add(db, argc, argv);
    }
    sqlite3_close(db);
    return 0;
}