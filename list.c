#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "style.h"

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    NotUsed = 0;

    if (strcmp(argv[4], "1") == 0)
    {
        exclamation();
        marker();
    }
    else
    {
        placeholder();
    }
    for (int i = 0; i < argc - 2; i++)
    {
        printf("%s\t", argv[i] ? argv[i] : "NULL");
    }
    if (strcmp(argv[3], "1") == 0)
    {
        tick();
    } else {
        placeholder();
    }
    reset();
    printf("\n");
    return 0;
}

void print_header()
{
    bold();
    printf("Flag\tId\tTask\tCategory\n");
    reset();
}

void list(sqlite3 *db, char **argv)
{
    int rc;
    char *err_msg = 0;
    char *sql = "SELECT * FROM Todo ORDER BY Urgent DESC";
    print_header();
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if (rc)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
}