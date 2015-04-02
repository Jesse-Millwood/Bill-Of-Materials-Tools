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
# API KEY: luqgEu6Q3kf8MSpbAohv
# pylint:disable=C0103
# pylint:disable=C0303

import argparse
import BOMparts
import csv
from eagleSchematicParser import extractEagleComponents
from kicadNetlistParser import extractKiCADComponents



def createCSV(parts, projectname, outputpath, tool, noParts):
    '''
    The creates the csv output file for the Bill of Materials
    '''
    outputFilename = outputpath+projectname+'_BOM.csv'
    bomRow = [0,0,0,0,0]
    # set component groups and sort
    for p in parts:
        p.setComponentGroup()
    parts.sort(key=lambda x: (x.group[1], x.fvalue), reverse=False)
    # Create csv file
    print('CSV Output File: ' + outputFilename)
    with open(outputFilename, 'w', encoding='utf8') as csvfile:
        writer = csv.writer(csvfile, delimiter=',',
                            quoting=csv.QUOTE_ALL)
        # Create Header for BOM
        writer.writerow(['Project:', '{0}'.format(projectname)])
        writer.writerow(['Tool:', '{0}'.format(tool)])
        writer.writerow(['Number of Parts ', '{0}'.format(noParts)])
        writer.writerow([' ', ' '])
        # Create Header for BOM Columns
        writer.writerow(['Reference',
                        'Quantity',
                         'Value',
                         'Distributor',
                         'Distributor #'])
        # Fill in BOM
        for bompart in parts:
            # Build row
            try:
                bomRow[0] = bompart.ref
            except:
                bomRow[0] = 'NA'
            try:
                bomRow[1] = bompart.qty
            except:
                bomRow[1] = 'NA'
            try:
                bomRow[2] = bompart.evalue
            except:
                bomRow[2] = 'NA'
            try:
                bomRow[3] = bompart.attributes['Distributor']
            except:
                bomRow[3] = 'NA'
            try:
                bomRow[4] = bompart.attributes['Distributor #']
            except:
                bomRow[4] = 'NA'
            # Write the row that had been built
            writer.writerow(bomRow)



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

    prjname = args.input.split('/')[-1].split('.')[0]
    print ('Input argument: {0}'.format(args.input))
    
    if args.edaTool.lower() == 'eagle':
        print ('Eagle EDA-Tool Chosen')
        bomParts = extractEagleComponents(args.input)
    elif args.edaTool.lower() == 'kicad':
        print ('KiCAD EDA-Tool Chosen')
        bomParts = extractKiCADComponents(args.input)
    if args.writeCSV:
        print('Project Name: {0}'.format(prjname))
        combinedBOMparts = BOMparts.combineBOMparts(bomParts)
        numberofparts = len(bomParts)
        #createCSV(bomParts, prjname, args.output, args.edaTool)
        createCSV(combinedBOMparts,
                  prjname,
                  args.output,
                  args.edaTool,
                  numberofparts)
        
    if args.verbose:
        print ('Project Components')
        print ('-'*40)
        for i, part in enumerate(bomParts):
            print ('{0}: \tReference: {1}'.format(i, part.ref))
            print ('\tValue: {0}'.format(part.evalue))
            print ('-'*40)

