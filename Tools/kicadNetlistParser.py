#!/usr/bin/python3

'''
Script to parse kicad netlists
'''

# pylint:disable = C0103

from BOMparts import BOMpart
from pyparsing import *
import re


def extractKiCADComponents(filename):
    '''
    Load a KiCAD netlist file and extract the part information
    '''
    components = []
    # Make single string out of file 
    with open(filename, "r") as net_f:
        netfile = net_f.read()
        netfile = re.sub('\s+', ' ', netfile)
        netfile = re.sub('\"', '', netfile)

    # helpers with suppression
    lparen = Literal("(").suppress()
    rparen = Literal(")").suppress()
    # Define a grmr representation of what we are looking for
    refgrmr = lparen + Word("ref").suppress() + Word(alphanums).setResultsName('ref') + rparen
    valuegrmr = lparen + Word("value").suppress() + Word(alphanums+". ,_").setResultsName('value') + rparen
    fpgrmr = lparen + Word("footprint").suppress() + Word(alphanums+"-_:.").setResultsName('fp') + rparen
    fieldgrmr = lparen + Word("field") + lparen  + Word("name") + \
                Word(alphas+"\" #") + rparen + Word(alphanums+"/\".-_ ~,#") + rparen
    libgrmr = lparen + Word("libsource").suppress() + lparen + \
              Word("lib").suppress() + Word(alphanums).setResultsName('lib') + rparen + \
              lparen + Word("part").suppress() + Word(alphanums+'-_').setResultsName('libp') + \
              rparen + rparen
    componentgrmr = lparen + Word("comp").suppress() + \
                    refgrmr + \
                    valuegrmr + \
                    fpgrmr + \
                    lparen + Word("fields").suppress() + ZeroOrMore(Group(fieldgrmr)) + rparen + \
                    libgrmr
    complistgrmr = OneOrMore(componentgrmr)
    # Create list of matching grammars
    components_parsed = [data for data,dataS,dataE in 
                         complistgrmr.scanString(netfile)]
    # Iterate over list of matching grammars and create a list of component objects
    for comp in components_parsed:
        # Check for attributes and collect
        attrs = {}
        for prprty in comp:
            if prprty[0] == 'field':
                attrs[prprty[2]] = prprty[3]
        # Build BOMpart and append to list
        components.append(BOMpart(ref=comp['ref'],
                                  evalue=comp['value'],
                                  library=comp['lib']+':'+comp['libp'],
                                  footprint=comp['fp'],
                                  attributes=attrs))
    return components

if __name__ == '__main__':
    # Test local functionality
    print('Testing Kicad Netlist Parser')
    # infile = '../SampleFiles/Mainboard.net'
    infile = '/home/jesse/millwooj@mail.gvsu.edu/RFCx/Design/PCB/Kicad Project 2/Main/Mainboard.net'
    Kcomps = extractKiCADComponents(infile)
    for c in Kcomps:
        print('-'*40)
        print(c.ref)
        print(c.evalue)
        print(c.library)
        print(c.footprint)
        print(c.attributes)
