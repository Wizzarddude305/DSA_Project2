#pragma once
#include <map>
using namespace std;

//This class
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

    bool operator==(const Pokemon &pokemon) {
        if (this->name == pokemon.name && this->teamStats == pokemon.teamStats && this->moveStats == pokemon.moveStats && this->gen == pokemon.gen && this->rank == pokemon.rank) {
            return true;
        }else {
            return false;
        }
    }

    Pokemon& operator=(const Pokemon &pokemon) {
        this->name = pokemon.name;
        this->teamStats = pokemon.teamStats;
        this->moveStats = pokemon.moveStats;
        this->gen = pokemon.gen;
        this->rank = pokemon.rank;
        return *this;
    }

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

    void empty() {
        this->name.clear();
        this->gen = -1;
        this->rank = -1;
        this->teamStats.clear();
        this->moveStats.clear();
    }
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

