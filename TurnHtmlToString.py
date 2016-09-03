# TurnHtmlToString.py
import re

with open("Test.html", 'r') as HTMLFile:
	t = HTMLFile.read()

	v = t
	v = re.sub(r'"', r'\"', v)
	v = re.sub(r'^(\s*)(.*)$', r'\1"\2\\n"', v, flags=re.M)

	
with open("Testt.h", 'w') as Output:
	Output.write(v)