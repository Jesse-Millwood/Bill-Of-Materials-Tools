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
    # Define a BNF representation of what we are looking for
    fieldBNF = lparen + Word("field") + lparen  + Word("name") + \
               Word(alphas+"\" #") + rparen + Word(alphanums+"\".-_ ~") + rparen
    componentBNF = lparen + Word("comp").suppress() + \
                   lparen + Word("ref").suppress() + Word(alphanums) + rparen + \
                   lparen + Word("value").suppress() + Word(alphanums) + rparen + \
                   lparen + Word("footprint").suppress() + Word(alphanums+"_:") + rparen + \
                   lparen + Word("fields").suppress() + ZeroOrMore(Group(fieldBNF)) + rparen + \
                   lparen + Word("libsource").suppress() + lparen + Word("lib").suppress() + Word(alphanums) + rparen + lparen + Word("part").suppress() + Word(alphanums+'-_') + rparen + rparen
    complistBNF = OneOrMore(componentBNF)
    # Create list of matching grammars
    components_parsed = [data for data,dataS,dataE in 
                         complistBNF.scanString(netfile)]
    # Iterate over list of matching grammars and create a list of component objects
    for comp in components_parsed:
        # Check for attributes and collect
        attrs = {}
        for prprty in comp:
            if prprty[0] == 'field':
                attrs[prprty[2]] = prprty[3]
        # Build BOMpart and append to list
        components.append(BOMpart(ref=comp[0],
                                  evalue=comp[1],
                                  library=comp[-2]+':'+comp[-1],
                                  footprint=comp[2],
                                  attributes=attrs))
    return components

if __name__ == '__main__':
    # Test local functionality
    print('Testing Kicad Netlist Parser')
    infile = '../SampleFiles/Top.net'
    comps = extractKiCADComponents(infile)
