#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <sqlite3.h>

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

int main()
{
	sqlite3 *db;
	char *errMsg = 0;
	int rc;
	srand(time(NULL));

	rc = sqlite3_open("beehive.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stderr, "Opened database succesfully\n");
	}
	

	sqlite3_close(db);
    return 0;
}