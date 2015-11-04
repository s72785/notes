#ifdef WINDOWS
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

#define VBUFSIZE 128
#define BERUFSIZE 20
#define MITRSIZE 10
#define NAMESIZE 20

int getBerufe( SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf );
int getMitarbeiterByBeruf( SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf, char *mitid );
int getMitarbeiterByMitIDAndBeruf( SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf, char *mitid );

int main(int argc, char *argv[]) {
	// sql vars
	SQLHENV henv = SQL_NULL_HENV; // environment
	SQLHDBC hdbc = SQL_NULL_HDBC; // connection
	SQLHSTMT hstmt = SQL_NULL_HSTMT; // statement

	// input vars
	char beruf[BERUFSIZE + 1];
	char mitid[MITRSIZE + 1];

	// sql connect
	sqlConnect(&henv, &hdbc, &hstmt);

	// program logic
	while ( getBerufe( &henv, &hdbc, &hstmt, beruf ) ) {
		while ( getMitarbeiterByBeruf( &henv, &hdbc, &hstmt, beruf, mitid ) ) {
			getMitarbeiterByMitIDAndBeruf( &henv, &hdbc, &hstmt, beruf, mitid );
		}
	}

	puts("");

	// sql disconnect
	sqlDisconnect(&henv, &hdbc, &hstmt);

	return 0;
}

int getBerufe(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf) {
	// sql vars
	SQLCHAR kBeruf[BERUFSIZE + 1];
	SQLLEN bindLen;
	SQLRETURN rc;

	// input buffer
	char vBuf[VBUFSIZE];

	// SQL statement
	char *sqlStatement = "SELECT DISTINCT(Beruf) FROM Mitarbeiter";
	if (DEBUGINFO) printf("sqlStatement: \"%s\"\n", sqlStatement);

	// perform the SQL statement
	rc = SQLExecDirect(*hstmt, (SQLCHAR *)sqlStatement, SQL_NTS);
	if (!checkReturnCode("SQLExecDirect [hstmt, sqlStatement]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	// bind columns
	rc = SQLBindCol(*hstmt, 1, SQL_C_CHAR, kBeruf, BERUFSIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 1, kBeruf]", rc, *hstmt, SQL_HANDLE_STMT);

	puts("");

	// fetch and print each row of data
	int i = 0;
	while ((rc = SQLFetch(*hstmt)) != SQL_NO_DATA) {
		// check error and warning
		if (rc == SQL_ERROR) {
			printf("SQLFetch [hstmt]: SQL_ERROR\n");
			break;
		}
		if (rc == SQL_SUCCESS_WITH_INFO) {
			printf("SQLFetch [hstmt]: SQL_SUCCESS_WITH_INFO\n");
		}

		// process data
		printf("  %-*s\n", BERUFSIZE, kBeruf);

		i++;
	}

	// cancel statement handle
	rc = SQLCancel(*hstmt);
	if (!checkReturnCode("SQLCancel [hstmt]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	if (i == 0) {
		printf("  Keine Berufe vorhanden.\n");
	}

	// get input
	printf("\n Beruf ? ");
	fgets(vBuf, VBUFSIZE, stdin);
	vBuf[strlen(vBuf) - 1] = 0;
	#ifdef WINDOWS
	strncpy_s(beruf, BERUFSIZE, vBuf, VBUFSIZE); // windows
	#else
	strncpy(beruf, vBuf, BERUFSIZE); // linux
	#endif

	return strlen( beruf );
}

int getMitarbeiterByBeruf( SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf, char *mitid ) {
	// sql vars
	SQLINTEGER kMitID;
	SQLCHAR kNName[NAMESIZE + 1];
	SQLCHAR kVName[NAMESIZE + 1];
	SQLLEN bindLen;
	SQLRETURN rc = 0;

	// input buffer
	char vBuf[VBUFSIZE];

	// SQL statement
	char *part1 = "SELECT MitID, Nachname, Vorname FROM Mitarbeiter WHERE Beruf = '";
	char *part2 = "'";
	int size = strlen(part1) + strlen(beruf) + strlen(part2) + 1;
	char *sqlStatement = malloc(sizeof(char) * size);
	#ifdef WINDOWS
	sprintf_s(sqlStatement, sizeof(char) * size, "%s%s%s", part1, beruf, part2); // windows
	#else
	sprintf(sqlStatement, "%s%s%s", part1, beruf, part2); // linux
	#endif
	if (DEBUGINFO) printf("sqlStatement: \"%s\"\n", sqlStatement);

	// perform the SQL statement
	rc = SQLExecDirect(*hstmt, (SQLCHAR *)sqlStatement, SQL_NTS);
	if (!checkReturnCode("SQLExecDirect [hstmt, sqlStatement]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	// bind columns
	rc = SQLBindCol(*hstmt, 1, SQL_C_LONG, &kMitID, 0, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 1, kMitID]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 2, SQL_C_CHAR, kNName, NAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 2, kNName]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 3, SQL_C_CHAR, kVName, NAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 2, kVName]", rc, *hstmt, SQL_HANDLE_STMT);

	puts("");

	// fetch and print each row of data
	int i = 0;
	while ((rc = SQLFetch(*hstmt)) != SQL_NO_DATA) {
		// check error and warning
		if (rc == SQL_ERROR) {
			printf("SQLFetch [hstmt]: SQL_ERROR\n");
			break;
		}
		if (rc == SQL_SUCCESS_WITH_INFO) {
			printf("SQLFetch [hstmt]: SQL_SUCCESS_WITH_INFO\n");
		}

		// process data
		printf("  %ld %-*s %-*s\n", kMitID, NAMESIZE, kNName, NAMESIZE, kVName);

		i++;
	}

	// cancel statement handle
	rc = SQLCancel(*hstmt);
	if (!checkReturnCode("SQLCancel [hstmt]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	if (i == 0) {
		printf("  Beruf '%s' ist nicht vorhanden.\n", beruf);
		return 0;
	}

	// wait
//  printf("\n wainting for you to press a key ");
//  fgets(vBuf, sizeof(vBuf), stdin);

//  return 0;
	// get input
	printf( "\n MitID ? " );
	fgets( vBuf, VBUFSIZE, stdin );
	vBuf[ strlen( vBuf ) - 1 ] = 0;
	#ifdef WINDOWS
	strncpy_s( mitid, MITRSIZE, vBuf, VBUFSIZE ); // windows
	#else
	strncpy( mitid, vBuf, MITRSIZE ); // linux
	#endif
	return strlen( mitid );
}

int getMitarbeiterByMitIDAndBeruf(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf, char *mitid ) {
	// sql vars
	SQLINTEGER kMitID;
	SQLCHAR kNName[NAMESIZE + 1];
	SQLCHAR kVName[NAMESIZE + 1];
	SQLCHAR kBeruf[NAMESIZE + 1];
	SQLCHAR kOrt[NAMESIZE + 1];
	SQLCHAR kGebdat[NAMESIZE + 1];
	SQLCHAR kTelnr[NAMESIZE + 1];
	SQLINTEGER kProNR;
	SQLCHAR kProName[NAMESIZE + 1];
	SQLCHAR kIstanteil[NAMESIZE + 1];
	SQLCHAR kPlananteil[NAMESIZE + 1];
	SQLLEN bindLen;
	SQLRETURN rc = 0;

	// input buffer
	char vBuf[VBUFSIZE];

	// SQL statement
	//next Statement: "SELECT ProNR, ProName, Istanteil, Plananteil FROM Projekt WHERE MitID = ''"
	char *part1 = "SELECT MitID, Nachname, Vorname, Beruf, Ort, Gebdat, Telnr FROM Mitarbeiter WHERE MitID = '";
	char *part2 = "' AND Beruf='";
	char *part3 = "'";
	int size =	strlen(part1) +
				strlen(mitid) +
				strlen(part2) +
				strlen(beruf) +
				strlen(part3) + 1;
	char *sqlStatement = malloc(sizeof(char) * size);
	#ifdef WINDOWS
	sprintf_s(sqlStatement, sizeof(char) * size, "%s%s%s%s%s", part1, mitid, part2, beruf, part3); // windows
	#else
	sprintf(sqlStatement, "%s%s%s%s%s", part1, mitid, part2, beruf, part3); // linux
	#endif
	if (DEBUGINFO) printf("sqlStatement: \"%s\"\n", sqlStatement);

	// perform the SQL statement
	rc = SQLExecDirect(*hstmt, (SQLCHAR *)sqlStatement, SQL_NTS);
	if (!checkReturnCode("SQLExecDirect [hstmt, sqlStatement]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	// bind columns
	rc = SQLBindCol(*hstmt, 1, SQL_C_LONG, &kMitID, 0, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 1, kMitID]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 2, SQL_C_CHAR, kNName, NAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 2, kNName]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 3, SQL_C_CHAR, kVName, NAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 3, kVName]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 4, SQL_C_CHAR, kBeruf, NAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 4, kBeruf]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 5, SQL_C_CHAR, kOrt, NAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 5, kOrt]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 6, SQL_C_CHAR, kGebdat, NAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 6, kGebdat]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 7, SQL_C_CHAR, kTelnr, NAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 7, kTelnr]", rc, *hstmt, SQL_HANDLE_STMT);

	puts("");

	//Kopf für Ausgabe
	printf("  %s %-*s %-*s %-*s %-*s %-*s %-*s\n", "MitID", NAMESIZE, "Nachname", NAMESIZE, "Vorname", NAMESIZE, "Beruf", NAMESIZE, "Ort", NAMESIZE, "Gebdat", NAMESIZE, "Telnr");
	// fetch and print each row of data
	int i = 0;
	while ((rc = SQLFetch(*hstmt)) != SQL_NO_DATA) {
		// check error and warning
		if (rc == SQL_ERROR) {
			printf("SQLFetch [hstmt]: SQL_ERROR\n");
			break;
		}
		if (rc == SQL_SUCCESS_WITH_INFO) {
			printf("SQLFetch [hstmt]: SQL_SUCCESS_WITH_INFO\n");
		}

		// process data
		printf("  %ld %-*s %-*s %-*s %-*s %-*s %-*s\n", kMitID, NAMESIZE, kNName, NAMESIZE, kVName, NAMESIZE, kBeruf, NAMESIZE, kOrt, NAMESIZE, kGebdat, NAMESIZE, kTelnr);

		i++;
	}

	// cancel statement handle
	rc = SQLCancel(*hstmt);
	if (!checkReturnCode("SQLCancel [hstmt]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	if (i == 0) {
		printf("  MitID '%s' mit Beruf '%s' ist nicht vorhanden.\n", mitid, beruf);
		return 0;
	} else {

		printf("  MitID '%s' ist vorhanden.\n", mitid);
		// SQL statement
		char *s2part1 = "SELECT p.ProNr, p.ProName, z.Istanteil, z.Plananteil FROM Projekt p JOIN Zuordnung z ON p.ProNr = z.ProNr WHERE MitID = '";
		char *s2part2 = "'";
		int size =	strlen(s2part1) +
					strlen(mitid) +
					strlen(s2part2) + 1;
		char *sqlStatement = malloc(sizeof(char) * size);
		#ifdef WINDOWS
		sprintf_s(sqlStatement, sizeof(char) * size, "%s%s%s", s2part1, mitid, s2part2); // windows
		#else
		sprintf(sqlStatement, "%s%s%s", s2part1, mitid, s2part2); // linux
		#endif
		if (DEBUGINFO) printf("sqlStatement: \"%s\"\n", sqlStatement);

		// perform the SQL statement
		rc = SQLExecDirect(*hstmt, (SQLCHAR *)sqlStatement, SQL_NTS);
		if (!checkReturnCode("SQLExecDirect [hstmt, sqlStatement]", rc, *hstmt, SQL_HANDLE_STMT)) {
			freeSQLHandles(henv, hdbc, hstmt); exit(0);
		}

		// bind columns
		rc = SQLBindCol(*hstmt, 1, SQL_C_LONG, &kProNR, 0, &bindLen);
		checkReturnCode("SQLBindCol [hstmt, 1, kProNR]", rc, *hstmt, SQL_HANDLE_STMT);
		rc = SQLBindCol(*hstmt, 2, SQL_C_CHAR, kProName, NAMESIZE + 1, &bindLen);
		checkReturnCode("SQLBindCol [hstmt, 2, kProName]", rc, *hstmt, SQL_HANDLE_STMT);
		rc = SQLBindCol(*hstmt, 3, SQL_C_CHAR, kIstanteil, NAMESIZE + 1, &bindLen);
		checkReturnCode("SQLBindCol [hstmt, 3, kIstanteil]", rc, *hstmt, SQL_HANDLE_STMT);
		rc = SQLBindCol(*hstmt, 4, SQL_C_CHAR, kPlananteil, NAMESIZE + 1, &bindLen);
		checkReturnCode("SQLBindCol [hstmt, 4, kPlananteil]", rc, *hstmt, SQL_HANDLE_STMT);

		puts("");

		//Kopf für Ausgabe
		printf("  %s %-*s %-*s %-*s\n", "ProNr", NAMESIZE, "ProName", NAMESIZE, "Istanteil", NAMESIZE, "Plananteil");
		// fetch and print each row of data
		int i = 0;
		while ((rc = SQLFetch(*hstmt)) != SQL_NO_DATA) {
			// check error and warning
			if (rc == SQL_ERROR) {
				printf("SQLFetch [hstmt]: SQL_ERROR\n");
				break;
			}
			if (rc == SQL_SUCCESS_WITH_INFO) {
				printf("SQLFetch [hstmt]: SQL_SUCCESS_WITH_INFO\n");
			}

			// process data
			printf("  %ld %-*s %-*s %-*s\n", kProNR, NAMESIZE, kProName, NAMESIZE, kIstanteil, NAMESIZE, kPlananteil);

			i++;
		}

		// cancel statement handle
		rc = SQLCancel(*hstmt);
		if (!checkReturnCode("SQLCancel [hstmt]", rc, *hstmt, SQL_HANDLE_STMT)) {
			freeSQLHandles(henv, hdbc, hstmt); exit(0);
		}

		if (i == 0) {
			printf("  Kein Projekt für MitID '%s' vorhanden.\n", mitid);
			return 0;
		} else {
			printf("  %d Projekte für MitID '%s' vorhanden.\n", i, mitid);
		}

	}

	// wait
	printf("\n wainting for you to press a key ");
	fgets(vBuf, sizeof(vBuf), stdin);

	return 0;
}
