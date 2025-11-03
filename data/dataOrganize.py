import json
import os

genNum= 1
indexRank = 0
ranks = [0, 1500, 1630, 1760]
indexUse = 0
uses = ['ou', 'uu']
fileName = f"gen{genNum}{uses[indexUse]}-{ranks[indexRank]}"
path = f"raw_files/{fileName}.json"
dataPoints = 0
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
    genNum += 1
    fileName = f"gen{genNum}{uses[indexUse]}-{ranks[indexRank]}"
    path = f"raw_files/{fileName}.json"

print(dataPoints)