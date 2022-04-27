from random import randint

with open("data.txt", "w") as file:
    for i in range(1000):
        txt = ", " + str(randint(1, 400))
        file.write(txt)
