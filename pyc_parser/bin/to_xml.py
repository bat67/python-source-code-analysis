import imp
import sys
import os

def generate_pyc(name):
	fp, pathname, description = imp.find_module(name)
	try:
		imp.load_module(name, fp, pathname, description)
	finally:
		if fp:
			fp.close()

if __name__ == '__main__':
	py_name = sys.argv[1]
	module_name = py_name[:py_name.index(".")]
	generate_pyc(module_name)
	if os.path.exists('./pyc_parser.exe'):
		#for Win32
		exe = '.\\pyc_parser.exe'
	else:
		#for Linux
		exe = './pyc_parser'
	cmd = "%s %s" % (exe, module_name + ".pyc",)
	os.system(cmd)
