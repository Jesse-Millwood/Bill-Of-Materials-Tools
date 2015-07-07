Bill Of Materials Tools
=======================

Command Line tool for converting a Kicad Netlist or an Eagle schematic file to a CSV file in a BOM format.

Sample Usage: 
```
python3 BOMtools.py -i '/Project Files/project.net' \
		    -o '/Path/to/output/' \
		    -t 'kicad' \
		    -w -v
```

This will output a csv file that can be opened by just about any spreadsheet program. The parts are grouped by the type of part and identical parts. For the output argument, `-o`, do not put the file name. The output file will be `Rootnameofinputfile_BOM.csv`. 
Preparation and Usage (Kicad)
=======================
You must add fields to every part in order to take advantage of having part numbers in your schematic file and exposed in the output of this tool. This can be accomplished this way:
* In Eeschema click `Preferences` and the `Schematic Editor Options`
* Then there is a tab at the top of that dialog window called `Template Field Names`
* Here there can be fields shuould be "Distributor#" and "Distributor"
* All of the schematic symbols will have these attributes now and you can edit them by pressing `E` on the symbols
* I am not sure if there is a way to include fields when creating a symbol in the Library Editor

Preparation and Usage (Eagle)
=======================
You must add attributes to every part in order to take advantage of having part numbers in your schematic file and exposed in the output of this tool. This can be accomplished a few ways:
* In the schematic use the 'attribute' tool built in to Eagle
* In the schematic use Bob Starr's `attrib-add` ulp in his `ulp_user` [Github repo](https://github.com/robertstarr/ulp_user)
* In the part editor add the attributes to the parts there
The attributes to add must be `DISTRUBUTOR` and `DISTRIBUTOR-NUM`



Disclaimer: This is still a work in progress. If you use this please compare the CSV output to the expected list.

Some TODO's:
* Detect file automatically
* Make CSV file creation more robust 