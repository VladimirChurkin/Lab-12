#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string>
#include <iostream>

int callback(void* data, int argc, char** argv, char** azColName) {
	printf("%d \n", (int)data);
	for (int i = 0; i < argc; i++) {
		printf("%s = %s \n", azColName[i], argv[i]);
	}
	printf("\n");
	return 0;
}

void SELECT(sqlite3* db, int res) {
	char* zErrMsg = 0;
	std::cout << "What do you want to select? (surname/name/year_of_birth/home_town)" << std::endl;
	std::string parametr;
	std::getline(std::cin, parametr);
	std::cout << "Its value: " << std::endl;
	std::string value;
	std::getline(std::cin, value);
	std::string SQL = "SELECT * FROM students WHERE " + parametr + " = '" + value + "'";
	res = sqlite3_exec(db, SQL.c_str(), callback, (void*)10, &zErrMsg);
	if (res != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s \n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Records created successfully\n");
	}
}

void INSERT(sqlite3* db, int res) {
	char* zErrMsg = 0;
	std::string surname, name, year, town;
	std::cout << "Enter the student's surname: " << std::endl;
	std::getline(std::cin, surname);
	std::cout << "Enter the student's name: " << std::endl;
	std::getline(std::cin, name);
	std::cout << "Enter the student's home town: " << std::endl;
	std::cout << "Enter the student's year of birth: " << std::endl;
	std::getline(std::cin, year);
	std::cout << "Enter the student's home town: " << std::endl;
	std::getline(std::cin, town);
	std::string SQL = "INSERT INTO students (surname, name, year_of_birth, home_town) VALUES ('" + surname + "','" + name + "', '" + year + "', '" + town + "')";
	res = sqlite3_exec(db, SQL.c_str(), 0, 0, &zErrMsg);
	if (res != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s \n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Records created successfully\n");
	}
}

void UPDATE(sqlite3* db, int res) {
	char* zErrMsg = 0;
	std::cout << "What do you want to change? (surname, name, year_of_birth, home_town)" << std::endl;
	std::string parametr;
	std::getline(std::cin, parametr);
	std::cout << "Apply this change to id: " << std::endl;
	std::string some_id;
	std::getline(std::cin, some_id);
	std::cout << "Change " << parametr << " to: " << std::endl;
	std::string some_data;
	std::getline(std::cin, some_data);
	std::string SQL = "UPDATE students SET " + parametr + " = '" + some_data + "' WHERE id = '" + some_id + "'";
	res = sqlite3_exec(db, SQL.c_str(), callback, (void*)10, &zErrMsg);
	if (res != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s \n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Records created successfully\n");
	}
}

void DELETE(sqlite3* db, int res) {
	char* zErrMsg = 0;
	std::cout << "Delete everyone with surname/name/year_of_birth/home_town: " << std::endl;
	std::string parametr;
	std::getline(std::cin, parametr);
	std::cout << "equal to: " << std::endl;
	std::string value;
	std::getline(std::cin, value);
	std::string SQL = "DELETE FROM students WHERE " + parametr + " = '" + value + "'";
	res = sqlite3_exec(db, SQL.c_str(), callback, (void*)10, &zErrMsg);
	if (res != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s \n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Records created successfully\n");
	}
}

int main() {
	sqlite3* db;
	int res = sqlite3_open("students_one.db", &db);
	if (res) {
		fprintf(stderr, "Can't open database: %s \n", sqlite3_errmsg(db));
		return 0;
	}
	else {
		fprintf(stderr, "Database opened successfully \n");
	}

	while (true) {
		std::cout << "What do you want to do?" << std::endl;
		std::cout << "1 — SELECT, 2 — INSERT, 3 — UPDATE, 4 — DELETE" << std::endl;
		int x;
		std::string tmp;
		std::getline(std::cin, tmp);
		x = std::stoi(tmp);
		if (x == 1) {
			SELECT(db, res);
		}
		else if (x == 2) {
			INSERT(db, res);
		}
		else if (x == 3) {
			UPDATE(db, res);
		}
		else if (x == 4) {
			DELETE(db, res);
		}
		else {
			std::cout << "An error occured." << std::endl;
			break;
		}
	}
	sqlite3_close(db);
	return 0;
}