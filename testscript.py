
# pylint: disable= C0103
# pylint: disable= R0903
# pylint: disable= C0111

class thing(object):
    def __init__(self, qty, name):
        self.qty = qty
        self.name = name


dict1 = {}
dict2 = {}

dict1 = {'things':[thing(1, 'larry'),
                   thing(1, 'Oliver'),
                   thing(1, 'Fred'),
                   thing(1, 'Amy')]}

dict2 = {'things':[thing(1, 'Jesse'),
                   thing(2, 'Oliver')]}

for thing1 in dict1['things']:
    for thing2 in dict2['things']:
        if thing2.name in thing1.name:
            thing1.qty += thing2.qty



for thing in dict1['things']:
    print(thing.name, thing.qty)
