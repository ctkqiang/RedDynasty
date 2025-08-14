#include<sqlite3.h>
#include<stdio.h>

int create_table(sqlite3 *db) {
    char *err_msg = NULL;
    const char *sql_query = "CREATE TABLE IF NOT EXISTS cve_data ("
                    "id TEXT PRIMARY KEY, "
                    "description TEXT, "
                    "publishedDate TEXT, "
                    "lastModifiedDate TEXT);";

    int record = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (record != SQLITE_OK) {
        fprintf(stderr, "SQL 错误: %s\n", err_msg);
        sqlite3_free(err_msg);
        return rc;
    }

    return SQLITE_OK;
}