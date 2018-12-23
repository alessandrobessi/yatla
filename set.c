#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

void set(sqlite3 *db, int argc, char **argv)
{
    if (strcmp("done", argv[3]) == 0)
    {
        int rc;
        char *err_msg = 0;
        char cmd[100];
        strcpy(cmd, "UPDATE Todo SET Status=1 WHERE Id=");
        strcat(cmd, argv[2]);
        strcat(cmd, ";");

        printf("%s\n", cmd);
        rc = sqlite3_exec(db, cmd, 0, 0, &err_msg);
        if (rc)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(EXIT_FAILURE);
        }
    }

    if (strcmp("todo", argv[3]) == 0)
    {
        int rc;
        char *err_msg = 0;
        char cmd[100];
        strcpy(cmd, "UPDATE Todo SET Status=0 WHERE Id=");
        strcat(cmd, argv[2]);
        strcat(cmd, ";");

        printf("%s\n", cmd);
        rc = sqlite3_exec(db, cmd, 0, 0, &err_msg);
        if (rc)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(EXIT_FAILURE);
        }
    }

    if (strcmp("category", argv[3]) == 0)
    {
        int rc;
        char *err_msg = 0;
        char cmd[100];
        strcpy(cmd, "UPDATE Todo SET Category='");
        strcat(cmd, argv[4]);
        strcat(cmd, "' WHERE Id=");
        strcat(cmd, argv[2]);
        strcat(cmd, ";");

        printf("%s\n", cmd);
        rc = sqlite3_exec(db, cmd, 0, 0, &err_msg);
        if (rc)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(EXIT_FAILURE);
        }
    }

    if (strcmp("priority", argv[3]) == 0)
    {
        int rc;
        char *err_msg = 0;
        char cmd[100];
        strcpy(cmd, "UPDATE Todo SET Urgent=");
        strcat(cmd, strcmp(argv[4], "high") == 0 ? "1" : "0");
        strcat(cmd, " WHERE Id=");
        strcat(cmd, argv[2]);
        strcat(cmd, ";");

        printf("%s\n", cmd);
        rc = sqlite3_exec(db, cmd, 0, 0, &err_msg);
        if (rc)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(EXIT_FAILURE);
        }
    }
}