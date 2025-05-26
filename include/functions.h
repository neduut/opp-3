#pragma once
#include "mylib.h"
#include "student.h"
#include "ownVector.h"
#include <cassert>

void handleProgramMenu(Vector<Student>& students);
void handleTestMenu();
void generateFile(int size);
void groupStudents(Vector<Student>& students, Vector<Student>& kietiakai, Vector<Student>& vargsiukai, int groupType);
void printToConsole(Vector<Student>& kietiakai, Vector<Student>& vargsiukai);
void printToFile(Vector<Student>& students, const string& fileName);
void fileGenTest(int size);
void programTest(int size);
void testRuleOfFive();
//void testZmogausClass(); // norit testuoti Zmogaus klase, atkomentuokite sia funkcija
void testOwnVector();
template <typename Vec>
void benchmarkPushBack(size_t sz, const std::string& name);