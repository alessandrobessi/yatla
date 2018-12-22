#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

void marker()
{
    printf("\033[1;31m");
}

void reset()
{
    printf("\033[0m");
}

void notick()
{
    printf("\xE2\x9D\x8C ");
}

void tick()
{
    printf("\xE2\x9C\x85 ");
}

void exclamation()
{
    printf("\xE2\x9D\x97 ");
}

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    NotUsed = 0;

    if (strcmp(argv[3], "1") == 0)
    {
        exclamation();
        marker();
    }
    for (int i = 0; i < argc - 2; i++)
    {
        printf("%s\t", argv[i] ? argv[i] : "NULL");
    }
    if (strcmp(argv[2], "1") == 0)
    {
        tick();
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

    rc = sqlite3_open("/tmp/todo.db", &db);
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
        char *sql = "SELECT * FROM Todo ORDER BY Urgent DESC";
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
        char *sql = "CREATE TABLE IF NOT EXISTS Todo(Id INTEGER PRIMARY KEY, Task TEXT, Status INT, Urgent INT);";
        char add[100];
        strcpy(add, "INSERT INTO Todo (Task, Status, Urgent) VALUES ('");
        strcat(add, argv[2]);
        strcat(add, "', 0, ");
        if (argc == 4)
        {
            strcat(add, strcmp(argv[3], "-u") == 0 ? "1" : "0");
        }
        else
        {
            strcat(add, "0");
        }
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
    sqlite3_close(db);
    return 0;
}