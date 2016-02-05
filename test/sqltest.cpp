#include <iostream>
#include <cstring>
#include <sqlite3.h>

int main(int argc, char** argv)
{
    //Open
    char* filename = new char [strlen(argv[1])];
    strcpy(filename,argv[1]);
    sqlite3* db;

    auto openErrCode = sqlite3_open_v2 (filename, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
    if (openErrCode != SQLITE_OK)
    {
        sqlite3_errstr(openErrCode);
        return -1;
    }

    delete [] filename;

    //Prepare stmt 
    char zSql[] = "CREATE TABLE MOVESET( PIECE INT  PRIMARY KEY NOT NULL, MOVES TEXT NOT NULL );";
    int zSqlLen = strlen(zSql);
    sqlite3_stmt *pStmt = nullptr;

    auto prepErrCode = sqlite3_prepare_v2 (db, zSql, zSqlLen, &pStmt, nullptr);
    if (prepErrCode != SQLITE_OK)
    {
        sqlite3_errstr(prepErrCode);
        return -1;
    }

    auto stepErrCode = sqlite3_step(pStmt);
    if (stepErrCode != SQLITE_DONE)
    {
        sqlite3_errstr(stepErrCode);
        return -1;
    }

    auto closeErrCode = sqlite3_close_v2 (db); 
    if (closeErrCode != SQLITE_OK)
    {
        sqlite3_errstr(openErrCode);
        return -1;
    }

    return 0;
}
