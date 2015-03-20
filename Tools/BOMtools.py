#!/usr/bin/python3

'''
BOM tools

Command Line tool for converting an Eagle schematic or Kicad Netlist file
to a BOM CSV file.

You can update pricing with the findchips.com api

Sample Usage: 

python BOMtools.py -i '/Project Files/project.net' \
		   -o 'projectBOM.csv' \
		   -t 'kicad' \
		   -w -v

'''
# pylint:disable=C0103
# pylint:disable=C0303

import argparse
import BOMparts
import csv
from eagleSchematicParser import extractEagleComponents
from kicadNetlistParser import extractKiCADComponents



def createCSV(parts, projectname):
    '''
    The creates the csv output file for the Bill of Materials
    '''
    outputFilename = projectname+'BOM.csv'
    print(outputFilename)
    with open(outputFilename, 'w', encoding='utf8') as csvfile:
        writer = csv.writer(csvfile, delimiter=',',
                            quoting=csv.QUOTE_ALL)
        writer.writerow(['Project:', '{0}'.format(projectname)])
        writer.writerow([' ', ' '])
        writer.writerow([' ', ' '])
        writer.writerow(['Reference', 'Value'])
        for bompart in parts:
            try:
                writer.writerow([bompart.ref, bompart.evalue, bompart.attributes['Distributor'], bompart.attributes['Distributor #']])
            except:
                writer.writerow([bompart.ref, bompart.evalue])


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    # Create Arguments
    parser.add_argument('--output', '-o', dest='output',
                        help='The path for the output csv BOM file')
    parser.add_argument('--input', '-i', dest='input',
                        help='The path to the input schematic or netlist file')
    parser.add_argument('--eda-tool', '-t', dest='edaTool',
                        help='Define what EDA tool created the input file')
    parser.add_argument('--update', '-u', dest='update',
                        help='Update the pricing')
    parser.add_argument('--verbose', '-v', action='store_true',
                        help='Show the verbose output to the terminal')
    parser.add_argument('--writeCSV', '-w', action='store_true',
                        help='Write BOM to CSV file')
    args = parser.parse_args()

    prjname = args.input[0:args.input.index('.')]
    print (args.input)
    
    if args.edaTool.lower() == 'eagle':
        print ('Eagle EDA-Tool Chosen')
        BOMparts = extractEagleComponents(args.input)
    elif args.edaTool.lower() == 'kicad':
        print ('KiCAD EDA-Tool Chosen')
        BOMparts = extractKiCADComponents(args.input)
    if args.writeCSV:
        createCSV(BOMparts, prjname)
        
    if args.verbose:
        print ('Project Components')
        print ('-'*40)
        for i, part in enumerate(BOMparts):
            print ('{0}: \tReference: {1}'.format(i, part.ref))
            print ('\tValue: {0}'.format(part.value))
            print ('-'*40)

