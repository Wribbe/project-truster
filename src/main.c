#include <stdlib.h>
#include <stdio.h>

#include "sqlite3.h"

#define PATH_DB "db.sqlite3"

int
db_init(void)
{
  FILE * schema = fopen("schema.sql", "r");
  fseek(schema, 0, SEEK_END);
  size_t size_schema = ftell(schema);
  rewind(schema);
  char * data_sql = malloc(size_schema+1);
  if (data_sql == NULL) {
    fprintf(stderr, "Could not allocate memory for reading schema.\n");
    exit(EXIT_FAILURE);
  }
  size_t size_read = 0;
  for (;;) {
    if (size_read == size_schema) {
      break;
    }
    size_read += fread(data_sql, 1, size_schema-size_read, schema);
  }
  data_sql[size_schema] = '\0';
  fclose(schema);

  sqlite3 * conn = NULL;
  sqlite3_open(PATH_DB, &conn);

  char * str_err = NULL;
  int err = sqlite3_exec(conn, data_sql, NULL, NULL, &str_err);
  if (err) {
    fprintf(stderr, "Schema creation failed with %d -- %s\n", err, str_err);
    printf("Schema:\n%s", data_sql);
    sqlite3_free(str_err);
  }

  free(data_sql);

  sqlite3_close(conn);

  if (err) {
    remove(PATH_DB);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int
main(void)
{
  if (fopen(PATH_DB, "r") == NULL) {
    db_init();
  }
  sqlite3 * conn = NULL;
  sqlite3_open(PATH_DB, &conn);
//  for (int i=0; i<1000; i++) {
//    sqlite3_exec(conn, "INSERT INTO post (?)"
//  }
  sqlite3_close(conn);
}
