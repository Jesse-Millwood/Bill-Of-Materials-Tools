#!/usr/bin/python

'''
Module SheetOrgainizer:
A collection of functions to organize
an electrical bill of materials
'''

# Written By: Jesse Millwood
# Tested on: Python 3.4 Ubuntu 14.04


# Installed the follwing packages via pip:
#	* openpyxl
# 	* ezodf


# Disable Some Pylint Warning Messages

# pylint: disable= C0103
# pylint: disable= W0312
# pylint: disable= W0311
# pylint: disable= R0902
# pylint: disable= R0913
# pylint: disable= W0102
# pylint: disable= C0326
# pylint: disable= C0303

from openpyxl import load_workbook
from operator import attrgetter
import csv
import re



class bomComponent(object):
    def __init__(self,
                 designator,
                 evalue,
                 package,
                 dkpn,
                 mfpn,
                 group,
                 qty):
        self.designator = designator
        self.evalue = evalue
        self.fvalue = convertEvalue(self.evalue)
        self.package = package
        self.dkpn = dkpn
        self.mfpn = mfpn
        self.group = group
        self.stock = stockStatus(self)
        self.qty = qty

def stockStatus(component):
    '''
    Checks if the part is a stock part or not.
    Returns true or false
    '''
    if component:
        return False
        


def convertEvalue(evalue):
    '''
    Given a string representing an 
    electrical value (10mF, 100k Ohm)
    a float value is returned
    '''
    # Take out white spaces
    evalue = evalue.replace(' ','')
    if len(evalue) == 0:
        return 0.0
    elif evalue[0].isdigit():
        multipliers = {'M':10**6,
                       'K':10**3,
                       'k':10**3,
                       'm':10**-3,
                       'u':10**-6,
                       'n':10**-9,
                       'p':10**-12}

        baseval = re.findall(r'\d*\.?\d+',evalue)[0]
        if len(baseval)==len(evalue): # no multiplier
            return float(baseval)
        elif evalue[len(baseval)] in multipliers.keys(): # multiplier exists
            return float(baseval)*multipliers[evalue[len(baseval)]]
        else:
            return float(baseval)
    else:
        return 0.0

def setComponentGroup(component):
    '''
    Given a row of the csv file 
    the grouping of the component will
    be extracted and returned
    '''
    # TODO: use regex to parse component info and figure out what the group is
    # TODO make easier to add a group and not have to manually shift the precedence numbers for all of the components
    # TODO crystal and zeners still not showing up correctly

    passive_groups = [('C', 'Capacitor', 0, 'Passive '),
                      ('R', 'Resistor', 1, 'Passive '),
                      ('R', 'Potentiometer', 2, 'Passive '),
                      ('D', 'Diode', 3, 'Passive '),
                      ('L', 'Inductor', 4, 'Passive '),
                      ('LED', 'LED', 5, 'Passive ')]
    transistors = [('U', 'fet', 6, 'Transistor '),
                   ('U', 'npn', 7, 'Transistor '),
                   ('U', 'pnp', 8, 'Transistor ')]
    mcu = [('U', 'atmega', 9, 'IC ')]
    crystal = [('Q', 'crystal ', 100, '')]
    
    device = component[2].lower()
    indicator = re.findall("[a-zA-Z]+", component[0].upper())[0]

    # Sample Component Value:
    # ['C1', '4.7uF', 'CAPACITOR0805', 'C0805']
    # Sample Group Value:
    # ('Passive Resistor', 1)

    for label, ptype, precedence, gtype in passive_groups + \
        transistors + mcu + crystal:
        if ptype.lower() in device:
            return (gtype + ptype, precedence)

    # Component did not fit any of the defined groups
    # Set precedence to 1000 to keep at the end
    return ('Other', 1000)
    
def reorderParts(parts):
    '''
    Function: reorderParts
    Description: Groups and orders the
    components of the bill of materials
    according to value
	Order of Priority:
	* Group (Resistor, Capacitor, IC ..)
	* Stock Part (YES, NO)
	* Value (If applicable)
        * Group the same values together and record qty
    '''
    # Make list of objects containing information about
    # the components in the bom
    bomComponents = []
    for component in parts:
        #print (component)
        # Create a list of objects with the proper attributes
        bomComponents.append(bomComponent(designator = component[0],
                                          evalue = component[1],
                                          package = component[3],
                                          group = setComponentGroup(component),
                                          dkpn = '',
                                          mfpn = '',
                                          qty = 1))
    # Order By Group Precedence and value
    bomComponents.sort(key = lambda x: (x.group[1], x.fvalue))
#    for thing in bomComponents:
#        print(thing.designator, thing.evalue)
    # Group Same Components
    bomComponents = combineSameComponents(bomComponents)    
    return bomComponents

def combineSameComponents(body):
        '''
        Combines components with the same 
        fvalue and group attributes
        increments respective qty attribute
        for component object
        '''
        combined = []
        copy = body
        counted = []
        
        for i,member1 in enumerate(body):
            if i not in counted:
                designators = member1.designator
                for i, member2 in enumerate(copy):
                    if member1.fvalue == member2.fvalue and \
                       member1.evalue == member2.evalue and \
                       member1.group[0] == member2.group[0] and \
                       member1.designator != member2.designator and \
                       'Other' not in member1.group[0]:
                        counted.append(i)
                        member1.qty += 1
                        designators += ' '+ member2.designator
                member1.designator = designators
                combined.append(member1)

        for thing in combined:
            print(thing.qty, thing.designator, thing.evalue)
        return combined

def writeBOM(parts, projectname):
    '''
    Take the ordered and grouped part info and
    write it to a standard BOM and save it
    '''
    StandardBOMFILE = '/home/jesse/Digi-Parser/SampleFiles/StandardBOM.xlsx'
    
    wb = load_workbook(filename=StandardBOMFILE)
    sheet = wb.get_sheet_by_name('BOM')
    STARTROW = 8
    r = STARTROW
    # Fill BOM
    for i, part in enumerate(parts):
       sheet.cell(row = r+i,column = 1).value = part.designator
       sheet.cell(row = r+i,column = 2).value = part.evalue + ' ' + part.package
       sheet.cell(row = r+i, column = 3).value = part.qty
    projectBOMname = projectname + 'BOM' + '.xlsx'

    
    wb.save(projectBOMname)
        
        

def csvToBOM(projectpath, projectname):
    '''
    Take information from Eagle CSV BOM
    and enter it into the BOM Excel File	
    * How to Create The CSV File from Eagle
        * Open Schematic
	* Run bom.ulp
	* Choose The Following Options:
	    * List Type: Parts
	    * List Attributes: Check
	    * Output format: CSV
    '''
    # Collect Components
    body = []
    infile = projectpath + projectname + '.csv'
    with open(infile , 'rt') as f:
        reader = csv.reader(f)
        for rownum,row in enumerate(reader):
            if rownum == 0:
                header = row
            else:
                body.append(row[0].replace('"','').split(';'))
    # order and group components
    orderedBody = reorderParts(body)

    writeBOM(orderedBody, projectname)

        
    return orderedBody

if __name__ == '__main__':
	# Example Usage
	prjpath = '/home/jesse/Digi-Parser/SampleFiles/'
	prjname = 'Water Use Monitor'
	things = csvToBOM(prjpath, prjname)
