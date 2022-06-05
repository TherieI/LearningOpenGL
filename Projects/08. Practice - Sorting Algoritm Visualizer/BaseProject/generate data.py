from random import randint

with open("data.txt", "w") as file:
    elements = ""
    for i in range(1000):
        elements += str(randint(1, 1000)) + ", "
    elements = elements[:2]
    file.write(elements)
