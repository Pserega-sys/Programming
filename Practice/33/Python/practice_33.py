def create(a, b=0, c=0):
    array = [b] * a
    for i, item in enumerate(range(b, b + c * a, c)):
            array[i] = item
        
    return array;

def sort(array):
    for i in range(1, len(array)):
        key = array[i]
        j = i-1
        while j >=0 and key < array[j] :
            array[j+1] = array[j]
            j -= 1
        array[j+1] = key
    return array
       

print ("Введите длину массива, начальный член и шаг арифметической прогрессии;")
print(sort(create(int(input()), int(input()), int(input()))))
