#!/usr/bin/python3

'''
This is a file that defines the object to store
parts in electronic projects
'''

# pylint: disable=C0303
# pylint: disable=C0103
# pylint: disable=C0301
# pylint: disable=R0902
# pylint: disable=R0903

import re

class BOMpart(object):
    '''
    This is an object to group electronic project
    parts and their attributes
    It provides a common way of expressing parts from
    projects created with different EDA tools

    |-----------------------------------|
    | BOMparts	| Eagle	    | Kicad	|
    |-----------|-----------|-----------|
    | ref	| name	    | name	|
    | evalue	| value     | value 	|
    | library	| library   | libsource |
    | footprint | footprint | device    |
    | attributes| attributes| fields	|
    |-----------|-----------|-----------|
    
    Other object attributes:
    	- fvalue: The floating point representation of the string representing
	          the value of the component
	          It will be -1 if this attribute is not applicable
	- group: For sorting purposes 
	- qty: For sorting purposes, the overall qty of the exact part in the project
	- sqty: 
	

    '''
    def __init__(self):
        self.ref = ''
        self.evalue = ''
        self.fvalue = -1.0
        self.library = ''
        self.footprint = ''
        self.attributes = {}
        self.group = ('Other', 1000)
        self.qty = 1
        self.sqty = 0
        # Convert the evalue to floating point
        # if applicable
        # self.convertEvalue()
        # self.setComponentGroup()

    def convertEvalue(self):
        '''
        Given a string representing an 
        electrical value (10mF, 100k Ohm)
        a float value is returned
        '''
        # Take out white spaces
        evalue = str(self.evalue).replace(' ', '')
        if len(evalue) == 0:
            self.fvalue = -1.0
            #return -1.0
        elif self.evalue[0].isdigit():
            multipliers = {'M':10**6,
                           'K':10**3,
                           'k':10**3,
                           'm':10**-3,
                           'u':10**-6,
                           'n':10**-9,
                           'p':10**-12}
            baseval = re.findall(r'\d*\.?\d+', self.evalue)[0]
            if len(baseval) == len(evalue): # no multiplier
                self.fvalue = float(baseval)
                #return float(baseval)
            elif evalue[len(baseval)] in multipliers.keys(): # multiplier exists
                self.fvalue = float(baseval)*multipliers[self.evalue[len(baseval)]]
                #return float(baseval)*multipliers[evalue[len(baseval)]]
            else:
                self.fvalue = float(baseval)
                #return float(baseval)
        else:
            self.fvalue = -1.0
            #return -1.0

    def setComponentGroup(self):
        '''
        the grouping of the component will
        be decided
        
        The purpose of grouping components is to aid in the readability
        and organization of a Bill of Materials grouping merely by a part
        reference does not do the best job. Hopefully this will be better
        
        Each group is characterized by a 
        	label: C, R, D, L, ect
        	ptype: part type 
        	presedence: used for determining which group is higher up in 
        		    the BOM listing
        	gtype: group type, to group passives with passives and so on
        If any of the characteristics of a particular group are found in the 
        attributes of the BOM part that group is assigned to the BOM part
        '''
        current_confidence = 0
        highest_confidence = 0
        ThreshHoldMatch = []
        MostLikelyMatches = []
        confidence_threshold = 2

        print ('-'*40)
        
        for index, definition in enumerate(partgroups):
            # Reset per definiton comparison variables
            current_confidence = 0
            # Build Confidence in a match
            if definition.ref in self.ref:
                current_confidence += 1
                print ('{0} matched in {1} at {2}'.format(definition.ref, self.ref, index))
            if definition.partType in self.library or \
               definition.partType in self.footprint:
                current_confidence += 1
                print ('{0} matched in {1} or {2} at {3}'.format(definition.partType,
                                                                self.library,
                                                                self.footprint,
                                                                index))
            if definition.groupType in self.library or \
               definition.groupType in self.footprint:
                current_confidence += 1
                print ('{0} matched in {1} or {2} at {3}'.format(definition.groupType,
                                                         self.library,
                                                         self.footprint,
                                                         index))
            if current_confidence > highest_confidence:
                highest_confidence = current_confidence
            if current_confidence >= confidence_threshold:
                MostLikelyMatches.append([definition, index])
                print ('Threshold Met')

        print ('Part:')
        print ('\tRef:{0}'.format(self.ref))
        print ('\tValue:{0}'.format(self.evalue))
        print ('\tFootprint:{0}'.format(self.footprint))
        print ('\tHighest Confidence: {0}'.format(highest_confidence))
        print ('Most Likely Groups:')
        if len(MostLikelyMatches) == 0:
            print ('No Match')
        else:
            for match in MostLikelyMatches:
                print (match[0].ref, match[0].partType, match[0].groupType)
        


class groupDefinition(object):
    '''
    Object that aids in group defintions
    '''
    def __init__(self, ref, partType, groupType, precedence):
        self.ref = ref
        self.partType = partType
        self.groupType = groupType
        self.precedence = precedence

def AddGroup(groupdeflist, reference, pt, gt):
    '''
    Function to aid in building up a list of group 
    defintion objects 

    Precedence is set later with the SetPrecedence
    '''
    groupdeflist.append(groupDefinition(ref=reference, partType=pt,
                                      groupType=gt, precedence=0))

def SetPrecedence(groupdeflist):
    '''
    Set the precedence of a group definitions in 
    a list of them

    This is where you can put the rules for sorting 
    the group defintion precedence 
    '''
    for index, groupdef in enumerate(groupdeflist):
        if groupdef.partType == 'Capacitor':
            groupdef.precedence = 0
        elif groupdef.partType == 'Resistor':
            groupdef.precedence = 1
        elif groupdef.partType == 'Inductor':
            groupdef.precedence = 2
        elif groupdef.partType == 'Diode':
            groupdef.precedence = 3
        elif groupdef.partType == 'LED':
            groupdef.precedence = 4
        elif groupdef.partType == 'Other':
            groupdef.precedence = 1000
        else:
            groupdef.precedence = 1000
        
def createGroupsList():
    '''
    This function is meant to create the groups that may be used
    to group the BOM parts. It is intended to take the creation of
    this list outside of the scope of the BOMpart class

    This is where you may add more group definitions
    The precedence will be set after the groups are defined
    '''

    # Passive Parts
    AddGroup(partgroups, 'C', 'Capacitor', 'Passive')
    AddGroup(partgroups, 'R', 'Resistor', 'Passive')
    AddGroup(partgroups, 'R', 'Potentiometer', 'Passive')
    AddGroup(partgroups, 'L', 'Inductor', 'Passive')
    AddGroup(partgroups, 'D', 'Diode', 'Passive')
    AddGroup(partgroups, 'LED', 'LED', 'Passive')
    # Transistors
    AddGroup(partgroups, 'U', 'FET', 'Transistor')
    AddGroup(partgroups, 'U', 'Transistor', 'General')
    AddGroup(partgroups, 'U', 'NPN', 'Transistor')
    AddGroup(partgroups, 'U', 'PNP', 'Transistor')
    # MCUs
    AddGroup(partgroups, 'U', 'atmega', 'mcu')
    AddGroup(partgroups, 'U', 'pic', 'mcu')
    # ICs
    AddGroup(partgroups, 'U', 'Reg', 'IC')
    AddGroup(partgroups, 'U', 'Transceiver', 'IC')
    AddGroup(partgroups, 'U', 'Comparator', 'IC')
    AddGroup(partgroups, 'U', 'ESD', 'IC')
    # Mechanical
    AddGroup(partgroups, 'SW', 'Switch', 'Mech')
    # Crystals
    AddGroup(partgroups, 'Q', 'Crystal', 'Clock')
    AddGroup(partgroups, 'X', 'Crystal', 'Clock')
    # Set Precedence
    SetPrecedence(partgroups)

def combineBOMparts(bomparts):
    '''
    This function combines identical parts, updates the count
    and returns a list of combined parts
    '''
    combinedparts = []
    foundFlag = False

    # Check if part is in combined parts
    # if so append update the qty for the part in combined parts and update refs
    # if not append it to combined parts
    for ipart in bomparts:
        foundFlag = False
        for i,cpart in enumerate(combinedparts):
            if cpart.evalue == ipart.evalue and \
               cpart.attributes == ipart.attributes:
                # Match found, update combined parts list
                foundFlag = True
                combinedparts[i].ref = cpart.ref+',' + ipart.ref
                combinedparts[i].qty +=1
        if foundFlag == False:
            # part not already in combined parts list
            # add it
            combinedparts.append(ipart)
    return combinedparts
                
if __name__ == 'BOMparts':
    # Module has been imported
    # Blank initialization of a global in the scope of the BOMparts
    partgroups = []
    # create the groups
    createGroupsList()

elif __name__ == '__main__':
    import BOMtools
    from kicadNetlistParser import extractKiCADComponents
    # Module is being run directly
    # This should be done for testing purposes
    partgroups = []
    createGroupsList()
    
    # Define some test parts
    # Test Kicad Parts:
    kicadNetlistFile = 'Test Files/Mitten Heater.net'
    kicadparts = extractKiCADComponents(kicadNetlistFile)
    topnetlist = 'Test Files/Top.net'
    topparts = extractKiCADComponents(topnetlist)
    BOMtools.createCSV(topparts,'Solar')

    print('!-----===== Testing Grouping =====-----!')
    kicadparts[5].setComponentGroup()
    for kpart in kicadparts[6:]:
        kpart.setComponentGroup()
