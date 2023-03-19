#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

//using namespace std;


class Map {



    class Gear {

        int x_coord;
        int y_coord;
        int radius;
        std::string mDir;
        std::vector<int> touching;

    public:

        Gear(int x_coord, int y_coord, int radius) {
            this->x_coord = x_coord;
            this->y_coord = y_coord;
            this->radius = radius;
            mDir = "NOT MOVING";
        }

        int getGearX() {
            return this->x_coord;
        }
        int getGearY() {
            return this->y_coord;
        }
        int getGearR() {
            return this->radius;
        }
        std::string getDir() {
            return this->mDir;
        }
        void setDir(std::string dir) {
            this->mDir = dir;
        }

    };

    std::vector<Gear*> allGears;

    bool isTouching(int a, int b) {

        double x_diff = (double)abs(allGears[a]->getGearX() - allGears[b]->getGearX());
        double y_diff = (double)abs(allGears[a]->getGearY() - allGears[b]->getGearY());

        double diag = sqrt(pow(x_diff, 2) + pow(y_diff, 2));
        double radiusSum = (double)allGears[a]->getGearR() + (double)allGears[b]->getGearR();

        return diag == radiusSum;
    }

public:

    bool isJammed = false;

    void addGear(int x, int y, int r) {
        Gear* input = new Gear(x, y, r);

        if (empty(allGears))
            input->setDir("CW");

        allGears.push_back(input);
    }

    void printAllGears() {
        for (Gear* gear : allGears) {
            std::cout << std::to_string(gear->getGearX()) + " "
                + std::to_string(gear->getGearY()) + " "
                + std::to_string(gear->getGearR()) << std::endl;
        }

        std::cout << this->isTouching(0, 1);
    }

    std::string getLastGearDir() {
        return allGears.back()->getDir();
    }


    void inspectGears(int current) {
        for (int i = 0; i < allGears.size(); i++) {

            if (i != current) {

                if (isTouching(i, current)) {

                    if (allGears[i]->getDir() == allGears[current]->getDir()) {

                        isJammed = true;

                    }
                    else if (allGears[i]->getDir() == "NOT MOVING") {

                        if (allGears[current]->getDir() == "CW") {
                            allGears[i]->setDir("CCW");
                        }
                        else {
                            allGears[i]->setDir("CW");
                        }
                        inspectGears(i);
                    }
                }
            }
        }
    }
};

int main()
{
    Map* map = new Map();

    int n;
    std::cin >> n; std::cin.ignore();
    for (int i = 0; i < n; i++) {
        int x;
        int y;
        int r;
        std::cin >> x >> y >> r; std::cin.ignore();

        map->addGear(x, y, r);
    }

    map->inspectGears(0);

    if (map->isJammed) {
        std::cout << "NOT MOVING";
    }
    else {
        std::cout << map->getLastGearDir();
    }
    return 0;
}