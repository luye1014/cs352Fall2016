#!/bin/bash
tests=$(ls -d test_*)
for x in $tests ; do
	cd $x;
	../phoneCalls $(cat CMDLINE) >myOut 2>errOut
	echo $? >>myOut
	cd ..;
done
