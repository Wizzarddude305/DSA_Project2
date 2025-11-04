import json
import os

genNum= 1
indexRank = 0
ranks = [0, 1500, 1630, 1760]
indexUse = 0
uses = ['ou', 'uu']
fileName = f"gen{genNum}{uses[indexUse]}-{ranks[indexRank]}"
dir = "raw_files"
dataPoints = 0

#deleting all data in file before writing new
with open("cppOrganized/AllPokemon-organized.txt", "w"):
    pass

#This code organizes the data from the raw json files into readable txt for the main file
for filename in os.listdir(dir):
    print(filename)
    with open(dir + '/' + filename, "r") as file:
        data = json.load(file)
        with open("cppOrganized/AllPokemon-organized.txt", "a") as writeFile:
            for pokemon in data['data']:
                dataPoints += 1
                splitFile = filename.split("-")
                print(splitFile)
                writeFile.write(f"{pokemon}, Generation:{splitFile[0][3]}, lowestRank:{splitFile[1][0]} \n")
                moves = ""
                for move in data['data'][pokemon]['Moves']:
                    number = data['data'][pokemon]['Moves'][move]
                    stat = number/data['data'][pokemon]["Raw count"]
                    if move != list(data['data'][pokemon]['Moves'].keys())[-1]:
                        if round(stat * 100,2) > 0:
                            writeFile.write(move + ': ' + str(round(stat * 100,2)) + "%,")
                    else:
                        writeFile.write(move + ': ' + str(round(stat * 100,2)) + "%\n")

                for teammate in data['data'][pokemon]['Teammates']:
                    number = data['data'][pokemon]['Teammates'][teammate]
                    stat = number/data['data'][pokemon]["Raw count"]
                    if teammate != list(data['data'][pokemon]['Teammates'].keys())[-1]:
                        if round(stat * 100,2) > 0:
                            writeFile.write(teammate + ': ' + str(round(stat * 100,2)) + "%,")
                    else:
                        writeFile.write(teammate + ': ' + str(round(stat * 100,2)) + "%\n")

    genNum += 1
    fileName = f"gen{genNum}{uses[indexUse]}-{ranks[indexRank]}"
    path = f"raw_files/{fileName}.json"

print(dataPoints)