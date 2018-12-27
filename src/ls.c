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
    for (int i = 0; i < argc - 4; i++)
    {
        printf("%s\t", argv[i] ? argv[i] : "NULL");
    }

    if (strcmp(argv[2], "Uncategorized") != 0)
    {
        printf("\t[%s]\t", argv[2]);
    }
    else
    {
        placeholder();
    }

    if (strcmp(argv[3], "1") == 0)
    {
        tick();
    }
    if (strcmp(argv[5], "1") == 0)
    {
        star();
    }
    reset();
    printf("\n");
    return 0;
}

void ls(sqlite3 *db, int argc, char **argv)
{
    int rc;
    char *err_msg = 0;

    if (argc > 2)
    {
        char cmd[255];
        strcpy(cmd, "SELECT * FROM Todo WHERE Category='");
        strcat(cmd, argv[2]);
        strcat(cmd, "' ORDER BY Urgent DESC");
        rc = sqlite3_exec(db, cmd, callback, 0, &err_msg);
        if (rc)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        char *cmd = "SELECT * FROM Todo ORDER BY Urgent DESC";
        rc = sqlite3_exec(db, cmd, callback, 0, &err_msg);
        if (rc)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(EXIT_FAILURE);
        }
    }
}