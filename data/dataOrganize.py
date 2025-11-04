import json
import os
import math
import re
from collections import Counter
from pathlib import Path

genNum= 1
indexRank = 0
ranks = [0, 1500, 1630, 1760]
indexUse = 0
uses = ['ou']

#meta game analysis
topMoves = 10
topItems = 5
topSpreads = 5
topTera = 5
level = 100 #4 EV points = 1 stat

#helpers for meta components
stats = ["hp", "atk", "def", "spa", "spd", "spe"]
spreadRegex = re.compile(r"(?P<nature>[A-Za-z]+):(?P<evs>(\d+/){5}\d+)$") #expression to extract nature
#and EV values from the spread string by converting to raw string and separating values
natures = {
    "Lonely" : ("atk", "def"), "Adamant" : ("atk", "spa"), "Naughty" : ("atk", "spd"),
    "Brave" : ("atk","spe"), "Bold" : ("def", "atk"), "Impish" : ("def", "spa"), "Lax" : ("def", "spd"),
    "Relaxed" : ("def", "spe"), "Modest" : ("spa","atk"), "Mild" : ("spa","def"), "Rash" : ("spa", "spd"),
    "Quiet" : ("spa", "spe"), "Calm" : ("spd", "atk"), "Gentle": ("spd", "def"), "Careful": ("spd", "spa"),
    "Sassy" : ("spd", "spe"), "Timid" : ("spe", "atk"), "Hasty" : ("spe", "def"), "Jolly": ("spe", "spa"),
    "Naive" : ("spe", "spd")
}

def parseSpreadKey(key): #takes input string key and matches nature with ev split
    matches = spreadRegex.match(key.strip())
    if not matches:
        return "Bashful", [0,0,0,0,0,0]
    nature = matches.group("nature")
    evs = list(map(int, matches.group("evs").split("/")))
    return nature, evs

def statsForEV(ev): #every 4 EVs is one stat point
    return ev // 4

def natureChanges(nature): #implements a 10 percent buff and nerf to stats based on nature
    if nature not in natures:
        return {"buff": None, "nerf": None}
    up, down = natures[nature]
    return {"buff": up, "nerf": down}

def topKeys(data, n): #ranks the n highest data points
    return sorted(data.items(), key=lambda x: x[1], reverse=True)[:n]

fileName = f"gen{genNum}{uses[indexUse]}-{ranks[indexRank]}"
path = f"raw_files/{fileName}.json"
dataPoints = 0

while indexRank < len(ranks):
    genNum = 1
    fileName = f"gen{genNum}{uses[indexUse]}-{ranks[indexRank]}"
    path = f"raw_files/{fileName}.json"
    while os.path.exists(path):
        with open(path, "r") as file:
            data = json.load(file)
            with open(f"cppOrganized/AllPokemon-organized.txt", "a") as writeFile:
                for pokemon in data['data']:
                    dataPoints += 1
                    writeFile.write(f"{pokemon}, Generation: {genNum}, lowestRank: {ranks[indexRank]} \n")
                    moves = ""
                    for move in data['data'][pokemon]['Moves']:
                        number = data['data'][pokemon]['Moves'][move]
                        stat = number/data['data'][pokemon]["Raw count"]
                        writeFile.write(move + ': ' + str(round(stat * 100,2)) + "% ")

                    writeFile.write("\n")
                    for teammate in data['data'][pokemon]['Teammates']:
                        number = data['data'][pokemon]['Teammates'][teammate]
                        stat = number/data['data'][pokemon]["Raw count"]
                        writeFile.write(teammate + ': ' + str(round(stat * 100,2)) + "%, ")
                    writeFile.write("\n")

                    abilities = data['data'][pokemon].get('Abilities', {})
                    if abilities:
                        writeFile.write("Abilities: ")
                        for ability, pct in sorted(abilities.items(), key=lambda kv: kv[1], reverse=True):
                            number = data['data'][pokemon]['Abilities'][ability]
                            stat = number/data['data'][pokemon]["Raw count"]
                            writeFile.write(ability + ': ' + str(round(stat * 100,2)) + "% ")
                        writeFile.write("\n")

                    items = data['data'][pokemon].get('Items', {})
                    if items:
                        writeFile.write("Top Items: ")
                        for item, pct in topKeys(items, topItems):
                            number = data['data'][pokemon]['Items'][item]
                            stat = number/data['data'][pokemon]["Raw count"]
                            writeFile.write(item + ': ' + str(round(stat * 100,2)) + "% ")
                        writeFile.write("\n")

                    spreads = data['data'][pokemon].get('Spreads', {})
                    if spreads:
                        writeFile.write("Top Spreads: \n")
                        for spread in sorted(spreads, key=spreads.get, reverse=True)[:topSpreads]:
                            number = spreads[spread]
                            stat = number/data['data'][pokemon]["Raw count"]

                            nature, evs = parseSpreadKey(spread)
                            EVMap = dict(zip(stats, evs))
                            points = {s: statsForEV(EVMap[s]) for s in stats}
                            natureStats = natureChanges(nature)

                            writeFile.write(f" {nature} (+{natureStats['buff'] or '-'} /"
                                        f" -{natureStats['nerf'] or '-'})"
                                        + str(round(stat * 100, 2)) + "% "
                                        f"EVs {EVMap['hp']}/{EVMap['atk']}/{EVMap['def']}"
                                        f"/{EVMap['spa']}/{EVMap['spd']}/{EVMap['spe']}\n"
                                        f"+pts {points['hp']}/{points['atk']}/{points['def']}/"
                                        f"{points['spa']}/{points['spd']}/{points['spe']}\n")

                    if genNum > 8:
                        teras = data['data'][pokemon].get('Tera Types', {})
                        if teras:
                            writeFile.write("Top Tera: ")
                            for tera, pct in topKeys(teras, topTera):
                                number = data['data'][pokemon]['Tera Types'][tera]
                                stat = number/data['data'][pokemon]["Raw count"]
                                writeFile.write(tera + ': ' + str(round(stat * 100,2)) + "% ")
                            writeFile.write("\n")
        genNum += 1 #go next gen
        fileName = f"gen{genNum}{uses[indexUse]}-{ranks[indexRank]}"
        path = f"raw_files/{fileName}.json"
    #when no more gens in mmr go next cutoff
    indexRank += 1
print(dataPoints)