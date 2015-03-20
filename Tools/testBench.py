#!/usr/bin/python

'''
This is for running tests with the BOM tools
'''

# pylint:disable=C0103
# pylint:disable=C0303

from eagleSchematicParser import extractEagleComponents
from kicadNetlistParser import extractKiCADComponents
import BOMtools


if __name__ == '__main__':
    # Define name of files
    kicadNetlistFile = 'Test Files/Mitten Heater.net'
    eagleSchematicFile = 'Test Files/Washer Control Board.sch'

    # Create list of parts
    eagleparts = extractEagleComponents(eagleSchematicFile)
    kicadparts = extractKiCADComponents(kicadNetlistFile)

    

    

    
