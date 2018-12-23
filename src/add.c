#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <stdbool.h>

void add(sqlite3 *db, int argc, char **argv)
{
    int rc;
    char *err_msg = 0;
    char *sql = "CREATE TABLE IF NOT EXISTS Todo(Id INTEGER PRIMARY KEY, Task TEXT, Category TEXT, Status INT, Urgent INT);";
    char add[256];

    bool is_urgent = false;
    bool has_category;
    char *category;
    if (argc > 3)
    {
        for (int i = 0; i < argc; i++)
        {
            if (strcmp(argv[i], "-u") == 0)
                is_urgent = true;
            if (strcmp(argv[i], "-t") == 0)
            {
                has_category = true;
                category = argv[i + 1];
            }
        }
    }

    strcpy(add, "INSERT INTO Todo (Task, Category, Status, Urgent) VALUES ('");
    strcat(add, argv[2]);
    strcat(add, "', '");
    strcat(add, has_category ? category : "Uncategorized");
    strcat(add, "', 0, ");
    strcat(add, is_urgent ? "1" : "0");
    strcat(add, ");");

    printf("%s\n", add);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    rc = sqlite3_exec(db, add, 0, 0, &err_msg);
    if (rc)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
}