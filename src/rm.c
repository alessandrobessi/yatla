#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

void rm(sqlite3 *db, char **argv)
{
    int rc;
    char *err_msg = 0;
    char rm[100];
    strcpy(rm, "DELETE FROM Todo WHERE Id=");
    strcat(rm, argv[2]);
    strcat(rm, ";");

    printf("%s\n", rm);
    rc = sqlite3_exec(db, rm, 0, 0, &err_msg);
    if (rc)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
}