#!/usr/bin/perl
use warnings;
use strict;

my $in = $ARGV[0];	#executable filename passed as argument
open IN, "$in" or die "Couldn't open $in, $!\n";	#Open the file

$/ = undef;			#stop interpretting carriage returns
my $file = <IN>;	#Slurp the data up into variable
$/ = "\n";			#Reinterpretation of carriage returns is ok
close IN;			#close the file

$file =~ s/(\x01\x00\x00\x00.{24})\x05/$1\x07/;	#Patch the rwx byte

open FILE, ">$in" or die "Couldn't open $in, $!\n";	#Open file back up for writing
print FILE $file;										#Write patched data
close FILE;												#close file
