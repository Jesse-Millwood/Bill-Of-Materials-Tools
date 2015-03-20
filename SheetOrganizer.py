#!/usr/bin/python3.4

'''
Module SheetOrgainizer:
A collection of functions to organize
an electrical bill of materials
'''

# Written By: Jesse Millwood
# Tested on: Python 3.4 Ubuntu 14.04
    # Need Python 3.4 for openpyxl
    # Colors get messed up in spreadsheets processed by openpyxl


# Installed the follwing packages via pip:
#	* openpyxl


# Disable Some Pylint Warning Messages

# pyline: python3
# pylint: disable= C0103
# pylint: disable= W0312
# pylint: disable= W0311
# pylint: disable= R0902
# pylint: disable= R0913
# pylint: disable= W0102
# pylint: disable= C0326
# pylint: disable= C0303

from openpyxl import load_workbook
from BOMtools import reorderParts


        


if __name__ == '__main__':
	# Example Usage
	# prjpath = '/home/jesse/Digi-Parser/SampleFiles/'
	# prjname = 'Water Use Monitor'
	# components = importEagleCSV(prjpath, prjname)
        # writeBOM(components,prjname)

