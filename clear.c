#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

void clear(sqlite3 *db)
{
    int rc;
    char *err_msg = 0;
    char *sql = "DROP TABLE IF EXISTS Todo";
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
}