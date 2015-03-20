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

import xml.sax
from BOMparts import BOMpart

class EaglePart(object):
    '''
    Class for grouping part attributes in an eagle
    schematic
    
    *DEPRECIATED*
    '''
    def __init__(self):
        self.name = ''
        self.library = ''
        self.deviceSet = ''
        self.device = ''
        self.value = ''
        self.attributes = {}

class PartsHandler(xml.sax.ContentHandler):
    '''
    Class for handling the part tags in an 
    Eagle CAD schematic
    '''
    def __init__(self):
        # Keep track of current elements
        self.currentName = ''
        self.currentLibrary = ''
        self.currentDeviceSet = ''
        self.currentDevice = ''
        self.currentValue = ''
        self.currentAttributes = {}
        # There are "attribute" tags outside of the "parts" tags
        # so this flag helps make sure that the only "attribute"
        # tags taken into consideration are the ones contained
        # in the "parts" tag
        self.inParts = False
        # List to keep track of parts in the schematic
        self.partsList = []
        # Counter to keep track of parts
        self.partCounter = 0

    def startElement(self, tag, attributes):
        '''
        Called when an element starts
        '''
        if tag == 'parts':
            self.inParts = True

        elif tag == 'part':
            # Create new Eagle Part Object
            self.partsList.append(BOMpart())
            # Update the new current variables
            self.currentName = attributes['name']
            self.currentLibrary = attributes['library']
            self.currentDeviceSet = attributes['deviceset']
            self.currentDevice = attributes['device']
            # Some elements have values and some don't
            try:
                self.currentValue = attributes['value']   
            except KeyError:
                self.currentValue = 'No Value' 
            
        elif tag == 'attribute' and self.inParts == True:
            # Update the dictionary for storing the attributes
            self.currentAttributes[attributes['name']] = attributes['value']
            

    def characters(self, content):
        '''
        Called when a character is read
        '''


    def endElement(self, tag):
        '''
        Called when an element ends
        '''
        if tag == 'part':
            # Updating the last made Eagle Part object with the data read from
            # the xml file
            self.partsList[self.partCounter].ref = self.currentName
            self.partsList[self.partCounter].library = self.currentLibrary
            self.partsList[self.partCounter].footprint = self.currentDeviceSet + self.currentDevice
            self.partsList[self.partCounter].value = self.currentValue 
            self.partsList[self.partCounter].attributes = self.currentAttributes
            # Reset the object variables that are keeping
            # track of current attributes for the next element
            self.currentName = ''
            self.currentLibrary = ''
            self.currentDeviceSet = ''
            self.currentDevice = ''
            self.currentValue = ''
            self.currentAttributes = {}
            # Increment part counter
            self.partCounter += 1
            
        elif tag == 'parts':
            self.inParts = False
            
        
        
# If imported, start with this function
def extractEagleComponents(schematicFile):
    '''
    It will return a list of objects representing
    all of the parts in the eagle schematic file and 
    their associted attributes
    
    from EagleSchematicParser import extractEagleComponents
    
    schemfilename = '~/Eagleproj/project.sch'
    eagleComponents = extractEagleComponents(schemfilename)
    
    '''
    SAXparser = xml.sax.make_parser()
    SAXparser.setFeature(xml.sax.handler.feature_namespaces, 0)
    SAXHandler = PartsHandler()
    SAXparser.setContentHandler(SAXHandler)
    SAXparser.parse(schematicFile)

    return SAXHandler.partsList
            

        
            
        
if __name__ == '__main__':
    schematicfilename = '/home/jesse/Magnum/Washer/Electrical/Washer/Washer Controller/Washer Control Board.sch'
    #schematicfilename = '/home/jesse/Public/schematic.sch'

    parser = xml.sax.make_parser()
    parser.setFeature(xml.sax.handler.feature_namespaces, 0)
    Handler = PartsHandler()
    parser.setContentHandler(Handler)
    parser.parse(schematicfilename)
    # Part information can then be extracted with
    # Handler.partsList[N].objectattr
