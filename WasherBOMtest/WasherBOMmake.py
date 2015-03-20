#!/usr/bin/python3.4

## Note:
## if using this for debugging purposes in the repl
## use imp.reload(BOMtools) inbetween running this script
## to import changes made in BOMtools
import BOMtools

if __name__ == '__main__':
    customername = 'Magnum'
#    prjname = 'RelayControlBoard'
    prjname  = 'Sensor Input Board'
    prjpath = '/home/jesse/BOMtools/WasherBOMtest/'
    stdbom  = '/home/jesse/BOMtools/WasherBOMtest/StandardBOM_style.xlsx'
    parts = BOMtools.importEagleCSV(prjpath, prjname)
    BOMtools.writeBOM(parts, prjname, stdbom, customername)

    # prjname = 'Sensor Input Board'
    # parts = BOMtools.importEagleCSV(prjpath,prjname)
    # BOMtools.writeBOM(parts,prjname,stdbom,customername)

    # prjname = 'Washer Control Board'
    # parts = BOMtools.importEagleCSV(prjpath,prjname)
    # BOMtools.writeBOM(parts,prjname,stdbom,customername)    
    
