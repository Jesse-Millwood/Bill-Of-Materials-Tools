#!/usr/bin/python3

'''
Script to parse kicad netlists
'''

# pylint:disable = C0103

from BOMparts import BOMpart
import pyparsing

        

def extractKiCADComponents(filename):
    '''
    Load a KiCAD netlist file and extract the part information
    '''
    data = []
    netlistComponents = []
    components = []
    
    # Read file as one long string
    with open(filename, 'r') as f:
        data = f.read().replace('\n', '')
    # Parse the nested lists
    parseddata = pyparsing.OneOrMore(pyparsing.nestedExpr()).parseString(data)
    for section in parseddata[0]:
        if 'components' in section[0]:
            netlistComponents = section
    for i, comp in enumerate(netlistComponents[1:]):
        # Create new part
        components.append(BOMpart())
        for attribute in comp:
            if 'ref' in attribute[0]:
                components[i].ref = attribute[1]
            elif 'value' in attribute[0]:
                components[i].evalue = attribute[1]
            elif 'footprint' in attribute[0]:
                components[i].footprint = attribute[1]
            elif 'fields' in attribute[0]:
                for field in attribute[1:]:
                    components[i].attributes[field[1][1]] = field[2]
            elif 'libsource' in attribute[0]:
                try:
                    components[i].library = attribute[1][1]
                except NameError:
                    print("libsource: {}".format(comp))
                #components[i]. = attribute[2][1]
    return components
