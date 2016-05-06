#!/usr/bin/python
#-*- coding: UTF-8 -*-
"""
功能描述：删除kernel文件夹中
不在modem_kernel.idl接口描述文件中的c/h/cpp 文件
"""
import os
import sys

def main():
    filedir = os.path.dirname(os.path.abspath(__file__))
    curdir = filedir + "/../.."
    curdir = os.path.abspath(curdir)
    top_dir = curdir + '/'
    code_dir = top_dir + "kernel"
    idl_file_path = top_dir + "vendor/hisi/interface/desc/modem/kernel/modem_kernel.idl"
    if os.path.exists(idl_file_path):
        fidl = file(idl_file_path,'r')
        idllines = fidl.read()
        fidl.close()
    else:
        print("idl_file not exist!")
        return
    idl_line_list = idllines.split("\n")
    for root, dirs, files in os.walk(code_dir):
        for fn in files:
            kfile = root + "/" + fn
            kfile = kfile.replace(top_dir,"")
            kfile = kfile.strip()
            find_kfile_in_idl_flag = False
            if kfile.endswith(".c") or kfile.endswith(".h") or kfile.endswith(".cpp"):
                for idl_line in idl_line_list:
                    idl_line = idl_line.strip()
                    if kfile == idl_line:
                        find_kfile_in_idl_flag = True
                        break
                if (find_kfile_in_idl_flag == False):
                    os.remove(top_dir + kfile)          

if __name__ == '__main__':
    main()


