from random import randint

with open("data.txt", "w") as file:
    for i in range(400):
        txt = ", " + str(randint(1, 100))
        file.write(txt)
