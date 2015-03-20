#!/usr/bin/python

'''
Command Line program that is used to
Parse a spreadsheet and store the
contents in a serialized python object
'''

# Written By: Jesse Millwood
# Tested on: Python 2.7 Ubuntu 14.04


# Disable Some Pylint Warning Messages

# pylint: python3
# pylint: disable= C0103
# pylint: disable= W0312
# pylint: disable= W0311
# pylint: disable= R0902
# pylint: disable= R0913
# pylint: disable= W0102
# pylint: disable= C0326
# pylint: disable= C0303
# pylint: disable= C0301

import argparse
from BOMtools import bomComponent, \
                     checkpackage, \
                     setComponentGroup, \
                     importPartsXSLX, \
                     saveParts



if __name__ == '__main__':
    # parser = argparse.ArgumentParser()
    # parser.add_argument("--stockfile",
    #                     help="The Microsoft Excel *.xlsx file that contains the stock parts")
    # parser.add_argument("--mfncol",
    #                     help="Column containing Manufacurer")
    # args = parser.parse_args()
    # stockparts = args.stockfile + '.xlsx'

    infile = '/home/jesse/BOMtools/SampleFiles/Magnum_Stock_Parts.xlsx'
    headerrow = 4
    stockparts = importPartsXSLX(infile,headerrow)

    # Iterate through parts
    numberofparts = len(stockparts['Manufacturer'])
    components = []

    for i in range(0,numberofparts):
        components.append(bomComponent(
                          designator = '',
                          evalue = stockparts['Value'][i],
                          package= checkpackage([stockparts[k][i] for k in stockparts.keys()]),
                          dkpn = '',
                          mfpn = stockparts['Manufacturer PN'][i],
                          group = setComponentGroup([stockparts[k][i] for k in stockparts.keys()]),
                          qty = 0,
                          stock = True))
    saveParts(components)
