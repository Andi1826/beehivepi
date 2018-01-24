#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <sqlite3.h>
#include <unistd.h>


int maxId = 0;

double getInsideTemp() {
	double dummyTemp;
	dummyTemp = round(((double)rand() / RAND_MAX) * 21*10)/10;
	return dummyTemp;
}

double getHumidity() {
	double dummyHumidity;
	dummyHumidity = round(((double)rand() / RAND_MAX) * 100 * 10) / 10;
	return dummyHumidity;
}

double getDbLevel() {
	double dummyDbLevel;
	dummyDbLevel = round((double)rand()/RAND_MAX *140 *10) / 10;
	return dummyDbLevel;
}

double getWeight() {
	double dummyWeight;
	dummyWeight = round((double) rand()/ RAND_MAX* 20 * 10) / 10;
	return dummyWeight;
}

double getOutsideTemp() {
	double dummyTemp;
	dummyTemp = round(((double)rand() / RAND_MAX) * 21 * 10) / 10;
	return dummyTemp;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; ++i) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

static int callbackMaxId(void *NotUsed, int argc, char **argv, char **azColName) {
	long int i;
	if (argv[0]) {
		i = strtol(argv[0], NULL, 10);
	}
	else {
		i = 0;
	}
	maxId = (int)i;
	return 0;
}

int main()
{
	sqlite3 *db;
	char *errMsg = 0;
	int rc;
	char *sql, *sql2;
	char sqlInsert[150];
	double insideTemp, humidity, dbLevel, weight, outsideTemp;
	unsigned int microseconds = 1000000;
	int i = 0;

	srand(time(NULL));

	rc = sqlite3_open("beehive.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stderr, "Opened database succesfully\n");
	}
	
	sql = "CREATE TABLE IF NOT EXISTS MEASURE(" \
		  "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
		  "CURRENT_TIME DATETIME," \
		  "INSIDE_TEMP NUMERIC," \
		  "HUMIDITY NUMERIC," \
		  "DB_LEVEL NUMERIC," \
		  "WEIGHT NUMERIC," \
		  "OUTSIDE_TEMP NUMERIC);";

	rc = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", errMsg);
		sqlite3_free(errMsg);
	}
	else {
		fprintf(stdout, "Table created successfully\n");
	}

	sql = "INSERT INTO MEASURE (ID, CURRENT_TIME,INSIDE_TEMP,HUMIDITY,DB_LEVEL,WEIGHT,OUTSIDE_TEMP) " \
		  "VALUES (%d, DATETIME('now'), %.1f, %.1f, %.1f, %.1f, %.1f);";

	//printf("Press escape to end measurments\n");

	sql2 = "SELECT MAX(ID) FROM MEASURE;";

	rc = sqlite3_exec(db, sql2, callbackMaxId, 0, &errMsg);

	i = 0;
	while (i <= 10) {
		insideTemp = getInsideTemp();
		humidity = getHumidity();
		dbLevel = getDbLevel();
		weight = getWeight();
		outsideTemp = getOutsideTemp();

		sprintf(sqlInsert, sql, maxId+i+1, insideTemp, humidity, dbLevel, weight, outsideTemp);
		printf("%s\n", sqlInsert);
		rc = sqlite3_exec(db, sqlInsert, callback, 0, &errMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", errMsg);
			sqlite3_free(errMsg);
		}
		else {
			fprintf(stdout, "Records created successfully\n");
		}
		usleep(microseconds);
		i++;
	}

	sqlite3_close(db);
    return 0;
}