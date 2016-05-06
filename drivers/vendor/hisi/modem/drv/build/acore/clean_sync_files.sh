#!/bin/bash 
cat $1 | while read NAME; do rm -rf $NAME; done 
