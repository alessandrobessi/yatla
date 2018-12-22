#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

void red()
{
    printf("\033[1;32m");
}

void reset()
{
    printf("\033[0m");
}

void tick()
{
    printf("\xE2\x9C\x93 ");
}

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    NotUsed = 0;

    if (strcmp(argv[2], "1") == 0)
    {
        red();
        tick();
    }
    for (int i = 0; i < argc - 1; i++)
    {
        printf("%s\t", argv[i] ? argv[i] : "NULL");
    }

    reset();
    printf("\n");
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "See usage\n");
        exit(EXIT_FAILURE);
    }

    sqlite3 *db;
    int rc;

    rc = sqlite3_open("todo.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    if (strcmp("clear", argv[1]) == 0)
    {
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

    if (strcmp("list", argv[1]) == 0)
    {
        char *err_msg = 0;
        char *sql = "SELECT * FROM Todo ORDER BY Status DESC";
        rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
        if (rc)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(EXIT_FAILURE);
        }
    }

    if (strcmp("rm", argv[1]) == 0)
    {
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

    if (strcmp("done", argv[1]) == 0)
    {
        char *err_msg = 0;
        char done[100];
        strcpy(done, "UPDATE Todo SET Status=1 WHERE Id=");
        strcat(done, argv[2]);
        strcat(done, ";");

        printf("%s\n", done);
        rc = sqlite3_exec(db, done, 0, 0, &err_msg);
        if (rc)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(EXIT_FAILURE);
        }
    }

    if (strcmp("add", argv[1]) == 0)
    {
        char *err_msg = 0;
        char *sql = "CREATE TABLE IF NOT EXISTS Todo(Id INTEGER PRIMARY KEY, Task TEXT, Status INT);";
        char add[100];
        strcpy(add, "INSERT INTO Todo (Task, Status) VALUES ('");
        strcat(add, argv[2]);
        strcat(add, "', 0);");

        printf("%s\n", add);
        rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
        if (rc)
        {
            // fprintf(stderr, "SQL error: %s\n", err_msg);
            // sqlite3_free(err_msg);
            // sqlite3_close(db);
            // exit(EXIT_FAILURE);
        }
        rc = sqlite3_exec(db, add, 0, 0, &err_msg);
        if (rc)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(EXIT_FAILURE);
        }
    }
    sqlite3_close(db);
    return 0;
}