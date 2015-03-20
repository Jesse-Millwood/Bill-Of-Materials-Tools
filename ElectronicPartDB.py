#!/usr/bin/python3.4

'''
Module ElectronicPartDB:
Create and Edit a serialized dictionary
that contains information about electronic
parts used. This is intended to lessen the
need to keep scraping websites and using api's
to get part info

command line interface and importable functions
'''


# Written By: Jesse Millwood
# Tested on: Python 3.4 Ubuntu 14.04

# pyline: python3
# pylint: disable= C0103
# pylint: disable= W0312
# pylint: disable= W0311
# pylint: disable= R0902
# pylint: disable= R0913
# pylint: disable= W0102
# pylint: disable= C0326
# pylint: disable= C0303


import pickle
import argparse
#from SheetOrgainizer import importPartsXSLX

    # '''
    # Load Local Part Database (serialized python objects)
    # Save parts for this project
    # Update part usage (for part usage stats)
    # Keep most used (1000 most used parts?)
    # Save using pickle
    # '''


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-a', '--action', help = 'Make new db, update existing')
    parser.add_argument('-i', '--inputf', help = 'Input file for updating')
    parser.add_argument('-o', '--outputf', help = 'Output file for db')
    parser.add_argument('-p', '--project', help = 'Project Name')
    parser.add_argument('--headerrow', help='The row of the header in the input file')
    args = parser.parse_args()

    if args.action == 'new':
        print("Making New Electronic Part Database")
        parts = importPartsXSLX(args.inputf, args.headerrow)

    elif args.action == 'update':
        print("Update Existing Electronic Part Database")
