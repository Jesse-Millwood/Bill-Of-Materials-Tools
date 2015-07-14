#! /usr/bin/python

'''
Script for extracting part info from an Eagle CAD XML Schematic file

Make sure that the 'eagle.dtd' file is in the same directory as the schematic,
otherwise this will not work. It is usually found in 'eagle/doc/eagle.dtd'
'''

# pylint:disable=C0303
# pylint:disable=C0103
# pylint:disable=C0301
# pylint:disable=R0902
# pylint:disable=R0903

from pyparsing import *
import re
from BOMparts import BOMpart


# If imported, start with this function
def extractEagleComponents(filename):
    '''
    It will return a list of objects representing
    all of the parts in the eagle schematic file and 
    their associted attributes
    
    from EagleSchematicParser import extractEagleComponents
    
    schemfilename = '~/Eagleproj/project.sch'
    eagleComponents = extractEagleComponents(schemfilename)
    
    '''
    with open(filename, "r") as sch_f:
        schemfile = sch_f.read()
        schemfile = re.sub('\s+', ' ', schemfile)
    # helpers with suppression
    lbracket = Literal("<").suppress()
    rbracket = Literal(">").suppress()
    quote = Literal("\"").suppress()
    # Grammars for xml fields
    # Redefine printables 
    newprintables = re.sub(r'[<>\\]', '', printables)+' '
    print("new: {}\n\n\n".format(newprintables))

    namegrmr = Word("name=").suppress() + quote + \
               Word(alphanums+"$_-").setResultsName('pref') + quote
    librarygrmr = Word("library=").suppress() + quote + \
                  Word(alphanums+" ").setResultsName('plib') + quote
    devicesetgrmr = Word("deviceset=").suppress() + quote + \
                    Word(alphanums+"_-*/").setResultsName('pdevset') + quote
    devicegrmr = Word("device=").suppress() + quote + \
                 Optional(Word(alphanums+"_-").setResultsName('pdev')) + quote
    valuegrmr = Word("value=").suppress() + quote + \
                Word(alphanums+"_-,/").setResultsName('pval') + quote
    attributegrmr = lbracket + Word("attribute name=").suppress() + \
                    quote + Word(alphanums+"_-/.") + quote + \
                    Word("value=").suppress() + quote + \
                    Word(alphanums+" _-/.") + quote + \
                    Literal("/").suppress() + rbracket
    techgrmr = Word("technology=") + quote + Word(alphanums) + quote
    # TODO: make grammar more robust
    # namegrmr = Word("name=").suppress() + quote + \
    #            Word(newprintables).setResultsName('pref') + quote
    # librarygrmr = Word("library=").suppress() + quote + \
    #               Word(newprintables).setResultsName('plib') + quote
    # devicesetgrmr = Word("deviceset=").suppress() + quote + \
    #                 Word(newprintables).setResultsName('pdevset') + quote
    # devicegrmr = Word("device=").suppress() + quote + \
    #              Optional(Word(newprintables).setResultsName('pdev')) + quote
    # valuegrmr = Word("value=").suppress() + quote + \
    #             Word(newprintables).setResultsName('pval') + quote
    # attributegrmr = lbracket + Word("attribute name=").suppress() + \
    #                 quote + Word(newprintables) + quote + \
    #                 Word("value=").suppress() + quote + \
    #                 Word(newprintables) + quote + \
    #                 Literal("/").suppress() + rbracket
    # techgrmr = Word("technology=") + quote + Word(newprintables) + quote


    # Main part grammar put together
    partgrmr = lbracket + Word("part").suppress() + \
               namegrmr +\
               librarygrmr +\
               devicesetgrmr +\
               Optional(devicegrmr) + \
               Optional(techgrmr) + \
               Optional(valuegrmr) + \
               Optional(Literal("/")) + rbracket +\
               ZeroOrMore(Group(attributegrmr)).setResultsName('attrs')
    # NOTE: Don't know if this is an issue but does not allow
    # parts through that have '+' or '-' in the reference (for power symbols)
    partlistgrmr = OneOrMore(partgrmr)
    parts_parsed = [data for data,dataS,dataE in
                    partlistgrmr.scanString(schemfile)]
    noparts = ['GND', 'FRAME']
    # Build list of BOMparts instances
    parts = []
    for part in parts_parsed:
        # Check to make sure the current part is one that is
        # of interest
        if not any(word in part['pref'].upper() for word in noparts) and \
           not any(word in part['plib'].upper() for word in noparts):
            print(part)
            try:
                tmpref = part['pref']
            except KeyError:
                tmpref = 'Unknown'
            try:
                tmpval = part['pval']
            except KeyError:
                tmpval = 'Unknown'
            try:
                tmplib = part['plib']+':'+part['pdevset']
            except KeyError:
                print('ref:{} could not find plib or devset')
                tmplib = 'Unknown'
            try:
                tmpfp = part['pdev']
            except KeyError:
                tmpfp = 'Unknown'
            try:
                print('Part Attributes: {}'.format(part['attrs']))
                tmpattrs = {}
                for a in part['attrs']:
                    tmpattrs[a[0]] = a[1]
            except KeyError:
                print('no attrs')
                tmpattrs = {}
            parts.append(BOMpart(ref=tmpref,
                                 evalue=tmpval,
                                 library=tmplib,
                                 footprint=tmpfp,
                                 attributes=tmpattrs))
    return parts

if __name__ == '__main__':
    print('Testing Eagle Schematic Parser')
    infile = '../SampleFiles/demo3.sch'
    Ecomps = extractEagleComponents(infile)

    for c in Ecomps:
        print('-'*40)
        print(c.ref)
        print(c.evalue)
        print(c.library)
        print(c.footprint)
        print(c.attributes)

    print('\n\nNum of Comps: {}'.format(len(Ecomps)))
