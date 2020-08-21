def process_vector(instruction, list):
    vector1 = list[0]
    if len(list) >=2:
        vector2 = list[1]
    if instruction == "SM":
        return (vector1[0]*vector2[0] +vector1[1]*vector2[1] + vector1[2]*vector2[2])
    if instruction == "M":
        return ((vector1[0] ** 2 + vector1[1] ** 2 + vector1[2] **2) ** 0.5)
    if instruction == "N":
        hipot = ((vector1[0] ** 2 + vector1[1] ** 2 + vector1[2] **2) ** 0.5)
        return (vector1[0]/hipot, vector1[1]/hipot, vector1[2]/hipot)

print process_vector("SM", [(3.0, 4.0, 5.0), (2.0, 4.0, 6.0)])
print process_vector("M", [(2.0, 7.0, 8.0)])

# Not, if'lerin icinde calisacak scalarMult, magnitude ve normalize fonksiyonlarini tanimlayabilirsin.
# vector 1 degil, v1 diye tanimla.
