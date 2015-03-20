#!/usr/bin/python

'''
Find A part using Digi-Key part number and store its'
information in an object
'''
# Jesse Millwood

# Installed BeautifulSoup4 Through pip
# Made Sure requests was installed
# Python 2.7

# Disable Some Pylint Warning Messages

# pylint: disable= C0103
# pylint: disable= W0312
# pylint: disable= W0311
# pylint: disable= R0902
# pylint: disable= R0913
# pylint: disable= W0102
# pylint: disable= C0326


from bs4 import BeautifulSoup
import requests

def find(lst, substring):
	'''
	Find the index of the substring in the given
	list
	'''
    	for i,s in enumerate(lst):
            if substring in s:
                return i
        return -1

        
class Component(object):
	'''
	Object that describes an electrical component.
	Intended use is for automating Bill Of Materials
	fields
	'''
	def __init__(self, dkPartno=None):
            self.dkPartno 	= dkPartno
            self.mfPartno 	= ''
            self.priceInfo 	= []
            self.manufacturer 	= ''
            self.description 	= ''
            self.infoRetrieved 	= False
            self.attributes 	= {}
        def getDigiInfo(self):
    		'''
		Given the Digi-Key Part number as a string,
		The price break, manufacturer, manufacturer
		part number and description are set for the
		object
		'''
                # Create url to read

		DKurl = 'http://digikey.com/scripts/DkSearch/dksus.dll?Detail&name='
		url = DKurl+self.dkPartno
		# Get html page for part with requests  and parse it with beautiful soup
		r = requests.get(url)
		soup = BeautifulSoup(r.text)
		# Define names of html tables containing needed info
		basic_tablename = 'product-details-table'
		info_tablename = 'product-additional-info'
		# Find html tables in html page
		basic_table = soup.find("table", {"class": basic_tablename})
		info_table = soup.find("table", {"class": info_tablename})
		# Intitialize empty lists to store info in
		self.basic_tablecontents = []
		self.info_tablecontents = []
		# Store html table contents in respective
                # lists and get rid of irrelevant entries
		for row in basic_table.findAll("tr"):
			for cell in row.findAll("td"):
	            		self.basic_tablecontents.append(cell.findAll(text=True))
                self.basic_tablecontents = [x.encode('ascii','ignore')
                                            for x in self.basic_tablecontents[0]
                                            if x != '\n']
		for row in info_table.findAll("tr"):
			for cell in row.findAll("td"):
	            		self.info_tablecontents.append(cell.findAll(text=True))
                self.info_tablecontents = [x.encode('ascii', 'ignore')
                                           for x in self.info_tablecontents[0]]
                self.info_tablecontents = [x for x in self.info_tablecontents
                                           if x not in ['','\n']]
                begin = self.info_tablecontents.index('Standard Package')
                end = self.info_tablecontents.index('Dynamic Catalog')
                self.info_tablecontents = self.info_tablecontents[begin:end]
                # Set flag indicating that the info has been retrieved
                self.infoRetrieved = True

	def getPriceInfo(self):
		'''
		After the info of the part has been
		retrieved by the getDigiInfo method,
		the price info can be extracted and
		stored in the objects' priceInfo list
		'''
		# find starting and ending index of the
            	# table contents that contain the price
            	# info
                start = self.basic_tablecontents.index('Extended Price\r\n')+1
                end = self.basic_tablecontents.index('Quantity Available')
		#prices = self.basic_tablecontents[start:end]
                # Convert strings to numbers
                prices = [float(x.replace(',','')) for x in self.basic_tablecontents[start:end]]
                priceBreak = prices[0::3]
                unitPrice = prices[1::3]
                ExtendedPrice = prices[2::3]
                # Store info in a list of dictionaries
                for i,price in enumerate(priceBreak):
                    self.priceInfo.append({'Price Break':priceBreak[i],
                                           'Unit Price':unitPrice[i],
                                           'Extended Price':ExtendedPrice[i]})

    	def getAttributes(self):
    		'''
		After the info of the part has been
		retrieved by the getDigiInfo method,
		the attributes can be retrieved from 
		the tables and associations can be made
		and stored in the attributes list
		'''
		# Extract Useful data from Basic Table and store in attributes table
                basic_fieldnames = ['Digi-Key Stock', 'Manufacturer',
                                    'Manufacturer Part Number', 'Description']
                for fieldname in basic_fieldnames:
                    if fieldname == 'Digi-Key Stock':
                        # The only one that needs a little extra thought
                        tbl_index = find(self.basic_tablecontents, fieldname)
                        s_index = self.basic_tablecontents[tbl_index].index(':')+1
                        fieldvalue = self.basic_tablecontents[tbl_index][s_index:]
                        self.attributes[fieldname] = fieldvalue
                    else:
                        fieldvalue_i = self.basic_tablecontents.index(fieldname)+1
                        fieldvalue = self.basic_tablecontents[fieldvalue_i]
                        self.attributes[fieldname] = fieldvalue
                # Extract Useful data from Info Table
                info_field = self.info_tablecontents[0::2]
                info_value = self.info_tablecontents[1::2]
                for field,value in zip(info_field,info_value):
                    self.attributes[field]=value
                # set object attributes based on contents of attributes dictionary
                self.mfPartno 		= self.attributes['Manufacturer Part Number']
        	self.manufacturer 	= self.attributes['Manufacturer']
            	self.description 	= self.attributes['Description']
if __name__ == '__main__':
	# Sample Usage
	dkpn = '458-1003-ND'
        buzzer = Component(dkPartno=dkpn)
        buzzer.getDigiInfo()
        buzzer.getPriceInfo()
        buzzer.getAttributes()

        res = Component(dkPartno='311-1.0KGRCT-ND')
        res.getDigiInfo()
        res.getPriceInfo()
        res.getAttributes()

        # Illustrating accessing the list of Dictionaries for the price info
        print '{0:^48}'.format('Buzzer Price Info')
        print '|{0:^16}|{1:^16}|{2:^16}|'.format('Price Break', 'Unit Price', 'Extended Price')
        for price in buzzer.priceInfo:
            print '|{0:^16}|{1:^16}|{2:^16}|'.format(price['Price Break'],price['Unit Price'], price['Extended Price'])

        # Illustrating accessing the component attributes
        print '{0:^49}'.format('Resistor Attributes')
        for key,value in res.attributes.iteritems():
            print '{0:>24}|{1:<24}'.format(key,value)

        # Illustrating accessing the component attributes
        print '\n{0:^49}'.format('Buzzer Attributes')
        for key,value in buzzer.attributes.iteritems():
            print '{0:>24}|{1:<24}'.format(key,value)
