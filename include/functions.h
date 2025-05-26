#pragma once
#include "mylib.h"
#include "student.h"
#include "ownVector.h"
#include <cassert>

void handleProgramMenu(vector<Student>& students);
void handleTestMenu();
void generateFile(int size);
void groupStudents(vector<Student>& students, vector<Student>& kietiakai, vector<Student>& vargsiukai, int groupType);
void printToConsole(vector<Student>& kietiakai, vector<Student>& vargsiukai);
void printToFile(vector<Student>& students, const string& fileName);
void fileGenTest(int size);
void programTest(int size);
void testRuleOfFive();
//void testZmogausClass(); // norit testuoti Zmogaus klase, atkomentuokite sia funkcija
void testOwnVector();
template <typename Vec>
void benchmarkPushBack(size_t sz, const std::string& name);