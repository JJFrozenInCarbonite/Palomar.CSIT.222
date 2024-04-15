class Vehicle():
    def __init__(self, location, speed, weight):
        self.location = location
        self.speed = speed
        self.weight = weight
    
    def stats(self):
        print(self.__dict__)

class Car(Vehicle):
    def __init__(self, location, speed, weight, color):
        super().__init__(location, speed, weight)
        self.color = color

v = Vehicle(1, 50 , 1000)
c = Car(2,100,100, 'Red')

v.stats()
c.stats()


