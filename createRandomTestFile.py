import random as rd

lines = ""
date = "10-10-2010"

nbfilms = 100
nbUsers = 1000
nbMaxMarkPerFilm = nbUsers
nbMinMarkPerFilm = 2*nbUsers/3

for i in range(nbfilms):
    lines += str(i+1)+":"
    lines += "\n"
    users = []
    for j in range(rd.randint(nbMinMarkPerFilm, nbMaxMarkPerFilm)):
        user = rd.randint(1, nbUsers)
        while (user in users):
            user = rd.randint(1, nbUsers)
        users.append(user)
        lines += str(user)
        lines += ","
        lines += str(rd.randint(1, 5))
        lines += ","
        lines += date
        lines += "\n"
    
file = open("testFile.txt", "w+")
file.write(lines)
file.close()