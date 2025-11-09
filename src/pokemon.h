#pragma once
#include <map>
using namespace std;

//This class just holds every pokemon's attributes
class Pokemon {
private:
    string name;
    int rank;
    int gen;
    map<string, float> moveStats;
    map<string, float> teamStats;
public:

    Pokemon() {
        name = "";
        teamStats.clear();
    }

    //All types of constructors used in the project
    Pokemon(string name, int rank, int gen) {
        this->name = name;
        this->rank = rank;
        this->gen = gen;
        teamStats.clear();
        moveStats.clear();
    }

    Pokemon(string name) {
        this->name = name;
        //-1 means the rank and generation are not established
        rank = -1;
        gen = -1;
        moveStats.clear();
        teamStats.clear();
    }

    Pokemon(string name, map<string, float> teamStats) {
        this->name = name;
        this->teamStats = teamStats;
        rank = -1;
        gen = -1;
        moveStats.clear();
    }

    Pokemon(string name, map<string, float> teamStats, map<string, float> moveStats) {
        this->name = name;
        this->teamStats = teamStats;
        rank = -1;
        gen = -1;
        this->moveStats = moveStats;
    }

    //This is for comparing pokemon for the data structures
    bool operator==(const Pokemon &pokemon) {
        if (this->name == pokemon.name && this->teamStats == pokemon.teamStats && this->moveStats == pokemon.moveStats && this->gen == pokemon.gen && this->rank == pokemon.rank) {
            return true;
        }else {
            return false;
        }
    }

    //This allows us to set pokemon equal to another one
    Pokemon& operator=(const Pokemon &pokemon) {
        this->name = pokemon.name;
        this->teamStats = pokemon.teamStats;
        this->moveStats = pokemon.moveStats;
        this->gen = pokemon.gen;
        this->rank = pokemon.rank;
        return *this;
    }

    //All setters
    void setName(string name) {
        this->name = name;
    }

    void setRank(int rank) {
        this->rank = rank;
    }
    void setGen(int gen) {
        this->gen = gen;
    }

    void setTeamStats(map<string, float> teamStats) {
        this->teamStats = teamStats;
    }

    void setMoveStats(map<string, float> moveStats) {
        this->moveStats = moveStats;
    }

    //Remove all attributes from a pokemon if needed
    void empty() {
        this->name.clear();
        this->gen = -1;
        this->rank = -1;
        this->teamStats.clear();
        this->moveStats.clear();
    }

    //Getters
    string getName() {
        return name;
    }

    int getRank() {
        return rank;
    }

    int getGen() {
        return gen;
    }

    map<string, float> getTeamStats() {
        return teamStats;
    }

    map<string, float> getMoveStats() {
        return moveStats;
    }

    ~Pokemon() {
        name = "";
        teamStats.clear();
    }
};

