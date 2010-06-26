#!/bin/env python

import re

try:
  import json
except:
  try:
    import simplejson as json
  except:
    raise RuntimeError, "You need to either run Python 2.6 or greater or install simplejson in Python 2.5"
                            
import sys
import optparse

parser = optparse.OptionParser('''Usage: %prog in.json''')

(options, args) = parser.parse_args()

if len (args) != 1:
  print "You must provide a JSON file\n"
  parser.print_help()
  sys.exit()

inputFile = args[0]

json_file = file (inputFile, 'r')
json_dict = json.load (json_file)
json_file.close()

baseFilename = re.search('(?:.*/)?([\w-]*).txt', inputFile).group(1).replace("-","_")

outLines = []
outLines.append("class %s" % (baseFilename))
outLines.append("{")
outLines.append("public:")
outLines.append("\tstatic std::vector<KappaTools::RunLumiEvtBXRange> getRange()")
outLines.append("\t{")
outLines.append("\t\tstd::vector<KappaTools::RunLumiEvtBXRange> ret;")
for run, lumiRangeList in json_dict.items():
  for lumis in lumiRangeList:
    if not isinstance (lumis, list) or not len(lumis) == 2:
      continue
    #print run, lumis[0], lumis[1]
    outLines.append("\t\tret.push_back(KappaTools::RunLumiEvtBXRange(%s,%s,%s));" % (run, lumis[0], lumis[1]))
    #for lumiSection in range(lumis[0], lumis[1] + 1):
    #  runLumiKey = "%d_%d" % (int(run), int(lumiSection))
    #  print "Item: %s" % runLumiKey

outLines.append("\t\treturn ret;")
outLines.append("\t}")
outLines.append("};")


FILE = open(baseFilename+".cc","w")
FILE.writelines(map(lambda x: x+"\n",outLines))
FILE.close()                

print "file created:"
print baseFilename+".cc"

