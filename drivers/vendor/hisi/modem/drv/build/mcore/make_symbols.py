#!/usr/bin/python
import os
import string
import sys
import datetime
import time
import stat
				
def main():
	errcode = 0

	# nm
	nm_tool = "/opt/gcc-arm-none-eabi-4_6-2012q1/bin/arm-none-eabi-nm"
	my_argv = sys.argv[1:]
	
	# scan parameters to dict
	params_dict = {}
	params_string = ""
	for p in my_argv:
		params_string += " " + p
		if string.find(p, '=') != -1 :
			subs = string.split(p,'=')
			if params_dict.has_key(subs[0]) :
				params_dict[subs[0]]=params_dict[subs[0]] + ',' + subs[1]
			else :
				params_dict[subs[0]]=subs[1]
		else:
			params_dict[p]=""
			
	print ">> PARAMS:" + params_string
	
	# 'product' is required.
	if not params_dict.has_key('nm') or not params_dict.has_key('of') or not params_dict.has_key('if'):
		print "args is required."
		usage()
		sys.exit(-1)
		
	nm_tool = params_dict['nm']
	
	out_file = params_dict['of']	
	out_file_i = out_file + '.i'
	
	in_files = string.split(params_dict['if'], ',')
	
	# init out file
	out_file_fd = open(out_file, 'w')
	out_file_i_fd = open(out_file_i, 'w')
	temp_file = out_file + '.tmp'
	
	out_file_fd.write('/* Created by Jeffery.Zhai */\n')
	out_file_fd.write('#include <symbol.h>\n')
	out_file_fd.write('#include "' + out_file_i + '"\n\n')
	out_file_fd.write('struct symbol kallsyms[] = {\n')
	
	sym_count = 0
	for f in in_files:
		nm_cmd = nm_tool + " -s -f bsd " + f + " > " + temp_file
		errcode = os.system(nm_cmd)
		fd = open(temp_file, 'r')
		for v in fd.readlines() :
			syms = string.split(string.rstrip(v,'\n'), ' ')
			#if len(syms) == 3 and syms[2].find('.') == -1 and (syms[1] == 'B' or syms[1] == 'D' or syms[1] == 'T'):
			if len(syms) == 3 and syms[2].find('.') == -1 and (syms[1] == 'T'):
				if syms[1] == 'T' :
					out_file_i_fd.write('extern int ' + syms[2] + '();\n')
				else:
					out_file_i_fd.write('extern int ' + syms[2] + ';\n')
				out_file_fd.write('\t{"' + syms[2] + '", (unsigned long)&' + syms[2] + '},\n')
				sym_count = sym_count + 1
		fd.close()
	out_file_fd.write('};\n\n')
	out_file_fd.write('unsigned kallsyms_count = ' + str(sym_count) + ';\n')
	
	out_file_fd.close()
	out_file_i_fd.close()
	os.system('rm -f ' + temp_file)

	if errcode != 0 :
		sys.exit(-1)
	
def usage():
	print "\n\nUsage:\n"
	print "	make_symbols nm=<nm tools> ifs=<file1>,<file2>,... of=<target file> "
	print "\n"
	

if __name__ == "__main__" :
	main()
