#include "mylib.h"
#include "utils.h"
#include "functions.h"
#include "student.h"
#include "ownVector.h"
//sutvarkyt kad visom sistemom veiktu simboliai
#ifdef _WIN32
#include <windows.h>
#endif

//void matuotiSparta(unsigned int dydis);

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(65001); 
    #endif


    /*std::vector<unsigned int> dydziai = {10000, 100000, 1000000, 10000000};
    for (unsigned int d : dydziai) {
        matuotiSparta(d);
    }*/

    //skaiciuotiPerskirstymus(100000000);

    vector<Student> students;

    int choice = getMenuChoice();

    if (choice == 1) {
        handleProgramMenu(students);
    } else if (choice == 2) {
        handleTestMenu();
    } else {
        cout << "Kaip sau nori.\n";
    }

    return 0;
}

