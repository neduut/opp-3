#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <windows.h>
#include "student.h"
#include "functions.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdio>
#include "ownVector.h"  // Įsijunkite savo Vector klasės headerį

TEST_CASE("Konstruktoriai ir pagrindinės operacijos") {
    SECTION("Default konstruktorius") {
        Vector<int> v;
        REQUIRE(v.size() == 0);
        REQUIRE(v.capacity() == 0);
        REQUIRE(v.empty());
    }

    SECTION("Dydžio konstruktorius") {
        Vector<int> v(5);
        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() == 5);
    }

    SECTION("Dydžio ir reikšmės konstruktorius") {
        Vector<int> v(3, 42);
        REQUIRE(v.size() == 3);
        REQUIRE(v[2] == 42);
    }
}

TEST_CASE("Kopijavimas ir perkėlimas") {
    Vector<int> original{1, 2, 3};
    
    SECTION("Kopijavimo konstruktorius") {
        Vector<int> copy(original);
        REQUIRE(copy == original);
    }

    SECTION("Perkėlimo konstruktorius") {
        Vector<int> moved(std::move(original));
        REQUIRE(moved.size() == 3);
        REQUIRE(original.empty());
    }
}

TEST_CASE("Elementų prieiga") {
    Vector<int> v{10, 20, 30};
    
    SECTION("Operatorius []") {
        REQUIRE(v[1] == 20);
        v[0] = 100;
        REQUIRE(v[0] == 100);
    }

    SECTION("Metodas at()") {
        REQUIRE(v.at(2) == 30);
        REQUIRE_THROWS_AS(v.at(3), std::out_of_range);
    }
}

TEST_CASE("Modifikavimo metodai") {
    Vector<int> v;
    
    SECTION("Push back") {
        v.push_back(1);
        v.push_back(2);
        REQUIRE(v.size() == 2);
        REQUIRE(v.back() == 2);
    }

    SECTION("Insert ir erase") {
        v.insert(0, 10);
        v.insert(1, 20);
        REQUIRE(v == Vector<int>{10, 20});
        
        v.erase(0);
        REQUIRE(v.size() == 1);
        REQUIRE(v[0] == 20);
    }
}

TEST_CASE("Utility metodai") {
    Vector<int> v{3, 1, 2, 2, 4};
    
    SECTION("Rūšiavimas") {
        v.sort();
        REQUIRE(v == Vector<int>{1, 2, 2, 3, 4});
    }

    SECTION("Unikalumas") {
        v.sort();
        v.unique();
        REQUIRE(v == Vector<int>{1, 2, 3, 4});
    }

    SECTION("Map operacija") {
        auto squared = v.map([](int x) { return x*x; });
        REQUIRE(squared == Vector<int>{9, 1, 4, 4, 16});
    }
}

TEST_CASE("Kiti testai") {
    SECTION("Talpos valdymas") {
        Vector<int> v;
        v.reserve(10);
        REQUIRE(v.capacity() >= 10);
        
        v.shrink_to_fit();
        REQUIRE(v.capacity() == 0);
    }

    SECTION("Lyginimo operatoriai") {
        Vector<int> a{1, 2};
        Vector<int> b{1, 2, 3};
        REQUIRE(a < b);
        REQUIRE_FALSE(a == b);
    }
}

/*TEST_CASE("Student klasės metodų testai") {
    SetConsoleOutputCP(65001);

    // 1st test
    SECTION("1 TESTAS: Default konstruktorius") {
        Student s;
        s.setFirstName("testas");
        s.setLastName("testukas");
        s.setMarks({1, 2, 3, 4, 5});
        s.setExamMark(10);
        s.calculateFinalMarks();

        REQUIRE(s.getFirstName() == "testas");
    }

    // 2nd test
    SECTION("2 TESTAS: kopijavimo konstruktorius") {
        Student s_original;
        s_original.setFirstName("testas");
        Student s_copy(s_original);
        REQUIRE(s_copy.getFirstName() == "testas");
    }

    // 3rd test
    SECTION("3 TESTAS: kopijavimo operatorius") {
        Student s_original;
        s_original.setFirstName("testas");
        Student s_copy;
        s_copy = s_original;
        REQUIRE(s_copy.getFirstName() == "testas");
    }

    // 4th test
    SECTION("4 TESTAS: perkėlimo konstruktorius") {
        Student s_source;
        s_source.setFirstName("testas");
        Student s_move(std::move(s_source));

        REQUIRE(s_move.getFirstName() == "testas");
        REQUIRE(s_source.getFirstName().empty());
    }

    // 5th test
    SECTION("5 TESTAS: perkėlimo operatorius") {
        Student s_source;
        s_source.setFirstName("testas");
        Student s_move;
        s_move = std::move(s_source);

        REQUIRE(s_move.getFirstName() == "testas");
        REQUIRE(s_source.getFirstName().empty());
    }

    // 6th test
    SECTION("6 TESTAS: įvesties operatorius (istringstream)") {
        std::istringstream iss("testas testukas 1 2 3 4 5 10\n");
        Student s;
        iss >> s;
        s.calculateFinalMarks();

        REQUIRE(s.getFirstName() == "testas");
        REQUIRE(s.getExamMark() == 10);
    }

    // 7th test
    SECTION("6.1 TESTAS: įvesties operatorius (input iš konsoles)"){
    std::istringstream iss("Labas Labukas 10 10 9 10 8 7");
    Student s;
    iss >> s;
    s.calculateFinalMarks();
    REQUIRE(s.getFirstName() == "Labas");
    }   

    // 8th test
    SECTION("6.2 TESTAS: įvestis iš failo") {
        std::ofstream testFile("../files/testas1.txt");
        testFile << "Antanas Antanaitis 9 8 7 6 5 9\n";
        testFile.close();
    
        Student s;
        std::ifstream fr("../files/testas1.txt");
        fr >> s;
        fr.close();
        s.calculateFinalMarks();

        REQUIRE(s.getFirstName() == "Antanas");
        REQUIRE(s.getLastName() == "Antanaitis");
        REQUIRE((s.getHomeworkMarks() == std::vector<int>{9, 8, 7, 6, 5}));
        REQUIRE(s.getExamMark() == 9);
    }

    // 9th test
    SECTION("7 TESTAS: išvesties operatorius") {
        Student s;
        s.setFirstName("Antanas");
        s.setLastName("Antanaitis");
        std::ostringstream oss;
        oss << s;
        REQUIRE(s.getFirstName() == "Antanas");
        REQUIRE(s.getLastName() == "Antanaitis");
    }

    //10th test
    SECTION("8 TESTAS: studentų nuskaitymas iš failo") {
        std::ofstream testFile("../files/studentai3.txt");
        testFile << "antrašte\n";
        testFile << "Jonas Jonaitis 10 9 8 7 9 6\n";
        testFile << "Vejas Vejukas 10 9 8 7 6 6\n";
        testFile << "Petras Petrauskas 8 9 7 10 9 5\n";
        testFile.close();

        std::vector<Student> s;
        Student::readFromFile(s, 3);
        REQUIRE(s.size() == 3);
        REQUIRE(s[0].getFirstName() == "Jonas");
        REQUIRE(s[1].getLastName() == "Vejukas");
    }

    // 11th test
    SECTION("9 TESTAS: išvedimas i failą") {
        Student s;
        s.setFirstName("testas");
        s.setLastName("testukas");
        s.setMarks({1, 2, 3, 4, 5});
        s.setExamMark(10);
        s.calculateFinalMarks();
        std::ofstream testFile("../files/testas2.txt");
        testFile << s << "\n";
        testFile.close();
    }

    // 12th test imituotas 
    SECTION("10 TESTAS: studentų išvedimas i konsolę") {
        std::ostringstream ss;
        Student s;
        s.setFirstName("testas");
        s.setLastName("testukas");
        s.setMarks({1, 2, 3, 4, 5});
        s.setExamMark(10);
        s.calculateFinalMarks();
        ss << s.getFirstName() << " " << s.getLastName() << "\n";
    
        std::string expected_output = "testas testukas\n";
        REQUIRE(ss.str() == expected_output);
    }

    // 13th test 
    SECTION("11 TESTAS: destruktorius") {
        const int before = dstCount;
        {
            Student temp;
        }
        REQUIRE(dstCount == before + 1);
    }
}

TEST_CASE("Papildomi testai") {
    SetConsoleOutputCP(65001);

    // 14th test 
    SECTION("12 TESTAS: galutinio pažymio skaičiavimas") {
        Student s;
        s.setMarks({9, 7, 10, 8, 10});
        s.setExamMark(10);
        s.calculateFinalMarks();
        REQUIRE(s.getAvgFinal() == 9.52f);
        REQUIRE(s.getMedianFinal() == 9);
    }

    // 15th test
    SECTION("13 TESTAS: studentų grupavimas") {
        std::vector<Student> students;
        Student s1, s2, s3;
        s1.setMarks({9, 8, 9, 10, 9});
        s1.setExamMark(10);
        s1.calculateFinalMarks();
        s2.setMarks({8, 6, 7, 8, 9});
        s2.setExamMark(9);
        s2.calculateFinalMarks();
        s3.setMarks({3, 2, 4, 4, 1});
        s3.setExamMark(5);
        s3.calculateFinalMarks();
        
        students.push_back(s1);
        students.push_back(s2);
        students.push_back(s3);

        std::vector<Student> kietiakai, vargsiukai;
        groupStudents(students, kietiakai, vargsiukai, 1); 

        REQUIRE(kietiakai.size() == 2);
        REQUIRE(vargsiukai.size() == 1);
    }  

    SECTION("14 TESTAS: random") {
        std::string kazkas = "Kazkas";
        std::string kazkas2 = "Kazkas2";
        kazkas2 = kazkas;
        REQUIRE(kazkas2 == "Kazkas");
    }

    SECTION("15 TESTAS: randommm")
    {
        int skaicius = 5;
        skaicius++;
        REQUIRE(skaicius == 6);
    }
}*/