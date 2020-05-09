//
// Created by root on 12/10/19.
//
/**
 * yum install mysql-devel
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#define MAX_BUF_SIZE 1024

const char *host = "10.1.102.161";    //or set the remote ip address.
const unsigned int port = 3306;
const char *user = "root";
const char *passwd = "1q2w3e4r";
const char *dbName = "game_server";      //database name of my typecho blog.

/* print the last error message. */
void finish_with_error(MYSQL *conn, const char *msg) {
    if (msg)
        printf("Error message[%s]: [%s].\n", msg, mysql_error(conn));
    else
        printf("Error message[%s].\n", mysql_error(conn));
    mysql_close(conn);
    /**
     * When errors such as MySQL server has gone away hapended, the program should be end immeidately.
     * Otherwise, we should encounter the error below.
     * *** Error in `./linux_c_mysql': double free or corruption (!prev): 0x0000000001223560 ***
     */
    exit(-1);
}

/**
 * mysql_query() cannot be used for statements that contain binary data; you must use mysql_real_query() instead.
 * Binary data may contain the “\0” character, which mysql_query() interprets as the end of the statement string.
 * In addition, mysql_real_query() is faster than mysql_query() because it does not call strlen() on the statement string.
 */
int executesql(MYSQL *conn, const char *sql) {
    if (mysql_real_query(conn, sql, strlen(sql)))
        return -1;
    return 0;
}

/* init the mysql connection. */
MYSQL *init_mysql() {
    //MySQL connection.
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL)
        return NULL;
    if (!mysql_real_connect(conn, host, user, passwd, dbName, port, NULL, 0))
        return NULL;
    //set the language for the results excuted.
    if (executesql(conn, "set names utf8"))
        return NULL;
    return conn;
}

void test_insert() {
    char *sql = "SELECT * FROM map_level limit 10";
}

void test_select(MYSQL *conn) {
//    char cSqlData[MAX_BUF_SIZE] = {0x00};
    char *sql = "SELECT * FROM map_level limit 10";
//    memcpy(cSqlData, sql, strlen(sql));
    if (executesql(conn, sql)) {
        finish_with_error(conn, NULL);
    }
    //result set.
    //MYSQL_RES *pMysqlRes = mysql_use_result(pMysqlConn);
    MYSQL_RES *res = mysql_store_result(conn);

    int rows = mysql_num_rows(res);
    int fields = mysql_num_fields(res);

    printf("Table have [%d] records containing [%d] fields in each one.\n", rows, fields);
    printf("+------------------------------------------------+\n");

    //an instance of a row from the result.
    MYSQL_ROW row;
    int x = 0, i = 0;
    while ((row = mysql_fetch_row(res))) {
        i = 0;
        while (i < fields) {
            printf("|%s", row[i] ? row[i] : "NULL");
            x = strlen(row[i++]);
        }
        printf("|\n");
    }

    printf("+------------------------------------------------+\n");
    mysql_free_result(res);
}


int main(int argc, char **argv) {
    int x = 0, i = 0;
    printf("A example for connecting mysql using c program in linux.\n");
    MYSQL *conn = init_mysql();
    if (conn == NULL) {
        finish_with_error(conn, NULL);
    }
    test_select(conn);

    mysql_close(conn);
    return 0;
}