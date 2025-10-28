#pragma once
#include <map>
using namespace std;

//This class
class Pokemon {
private:
    string name;
    map<string, float> teamStats;
public:
    Pokemon() {
        name = "";
        teamStats.clear();
    }

    Pokemon(string name) {
        this->name = name;
        teamStats.clear();
    }

    Pokemon(string name, map<string, float> teamStats) {
        this->name = name;
        this->teamStats = teamStats;
    }

    bool operator==(const Pokemon &pokemon) {
        if (this->name == pokemon.name && this->teamStats == pokemon.teamStats) {
            return true;
        }else {
            return false;
        }
    }

    Pokemon& operator=(const Pokemon &pokemon) {
        this->name = pokemon.name;
        this->teamStats = pokemon.teamStats;
        return *this;
    }

    string getName() {
        return name;
    }


    map<string, float> getTeamStats() {
        return teamStats;
    }

    ~Pokemon() {
        name = "";
        teamStats.clear();
    }
};

