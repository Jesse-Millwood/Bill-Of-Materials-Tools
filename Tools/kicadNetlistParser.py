#!/usr/bin/python

'''
Script to parse kicad netlists
'''

# pylint:disable = C0103

from BOMparts import BOMpart

class kicadComponent(object):
    '''
    Class for keeping Kicad component attributes
    grouped together

    *DEPRECIATED*
    '''
    def __init__(self):
        self.ref = ''
        self.value = ''
        self.libsource = ''
        self.footprint = ''
        self.fields = {}

def extractFieldDict(string):
    '''
    Convert the attributes in the feild to a
    dictionary so it is searchable
    '''
    string = string.strip().replace('name ', '')
    string = string.replace('field ', '')
    string = string.replace('"', '')
#    print string
    fieldList = string.split(' ')
    if len(fieldList) > 2:
        fieldList[0] = ' '.join(fieldList[0:-1])
        fieldList[1] = fieldList[-1]
#    print fieldList
    fieldDict = {fieldList[0]:fieldList[1]}
#    print fieldDict
    return(fieldDict)
        
def extractKiCADComponents(filename):
    '''
    Parses Kicad netlist file and extracts componets
    '''
    openparenFLAG = False
    openParenCount = 0
    closeParenCount = 0
    compCount = 0
    components = []
    filelines = []
    with open(filename) as f:
        filelines = f.readlines()

    
    for line in filelines:
        if 'comp ' in line and openparenFLAG == False:
            openparenFLAG = True
            compCount +=1
            components.append(BOMpart())
        if openparenFLAG == True:
            openParenCount += line.count('(')
            closeParenCount += line.count(')')
            line = line.replace('(', '')
            line = line.replace(')', '')
            line = line.replace('\n', '')

            if 'ref' in line:
                components[compCount-1].ref = line[line.find('ref')+len('ref')+1:]
            if 'value' in line:
                components[compCount-1].evalue = line[line.find('value')+len('value')+1:]
            if 'footprint' in line:
                components[compCount-1].footprint = line[line.find('footprint')+len('footprint')+1:]
            if 'field ' in line:
                components[compCount-1].attributes.update(extractFieldDict(line))
            if 'libsource' in line:
                components[compCount-1].library = line[line.find('libsource')+len('libsource')+1:]
            if openParenCount == closeParenCount:
                openparenFLAG = False

        
    return components




