#pragma once
#include <map>
using namespace std;

//This class
class Pokemon {
private:
    string name;
    map<string, float> teamStats;

    int genNum;
    int minRank;
    map<string, float> topMoves;
    map<string, float> topItems;
    map<string, float> topSpreads;
    map<string, float> topTera;
    map<string, float> abilities;
public:
    Pokemon() {
        name = "";
        genNum = 0;
        minRank = 0;
        clearAll();
    }

    Pokemon(string name, int gen, int rank) {
        this->name = name;
        this->genNum = gen;
        this->minRank = rank;
        clearAll();
    }

    Pokemon(string name, map<string, float> teamStats, int gen, int rank) {
        this->name = name;
        this->teamStats = teamStats;
        this->genNum = gen;
        this->minRank = rank;
        topMoves.clear();
        topItems.clear();
        topSpreads.clear();
        topTera.clear();
        abilities.clear();

    }

    bool operator==(const Pokemon &pokemon) {
        if (this->name == pokemon.name && this->teamStats == pokemon.teamStats
            && this->genNum == pokemon.genNum && this->minRank == pokemon.minRank) {
            return true;
        } return false;

    }

    Pokemon& operator=(const Pokemon &pokemon) {
        this->name = pokemon.name;
        this->genNum = pokemon.genNum;
        this->minRank = pokemon.minRank;
        this->teamStats = pokemon.teamStats;
        this->topMoves = pokemon.topMoves;
        this->topItems = pokemon.topItems;
        this->topSpreads = pokemon.topSpreads;
        this->topTera = pokemon.topTera;
        this->abilities = pokemon.abilities;

        return *this;
    }

    string getName() {
        return name;
    }

    int getGenNum() {
        return genNum;
    }

    int getMinRank() {
        return minRank;
    }

   map<string, float> getTeamStats() {
        return teamStats;
    }
    map<string, float> getTopMoves() {
        return topMoves;
    }
    map<string, float> getTopItems() {
        return topItems;
    }
    map<string, float> getTopSpreads() {
        return topSpreads;
    }
    map<string, float> getTopTera() {
        return topTera;
    }

    map<string, float> getAbilities() {
        return abilities;
    }

    void clearAll() {
        teamStats.clear();
        topMoves.clear();
        topItems.clear();
        topSpreads.clear();
        topTera.clear();
        abilities.clear();
    }

    void setGenNum(int gen) {genNum = gen;}
    void setMinRank(int rank) {minRank = rank;}
    void setTeamStats(map<string, float> &map) {teamStats = map;}
    void setTopMoves(map<string, float> &map) {topMoves = map;}
    void setTopItems(map<string, float> &map) {topItems = map;}
    void setTopSpreads(map<string, float> &map) {topSpreads = map;}
    void setTopTera(map<string, float> &map) {topTera = map;}
    void setAbilities(map<string, float> &map) {abilities = map;}


    ~Pokemon() {
        clearAll();
        name.clear();
    }
};

