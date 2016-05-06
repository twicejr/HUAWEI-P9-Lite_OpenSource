#!/usr/bin/perl -w

use strict;
use Spreadsheet::ParseExcel;
use Cwd;

#==========================================================================
#
#GEN_GPIO_CFG
#
#brief description
#	auto gen config.c and .h by perl script
#EXAMPLE
#	if example.xls is given,then example.c and example.h will be
#	generated automaticlly by excuting gen_gpio_cfg.pl.
#Copyright (c) 2013 by Huawei Incorporated.  All Rights Reserved.
#==========================================================================

sub my_main()
{
	#get current directory
	my $current_dir = getcwd();
	opendir(CUR_DIR, $current_dir) || die "[PERL_ERROR] current directory not exist";
	my @file_s = readdir(CUR_DIR);

	my $count;
	my $subdir;
	my $subdir_t;
	my $pin_config_xls;

	for($count = 0; $count<@file_s; $count++)
	{
		#skip file that is not a directory
		if($file_s[$count] =~ m/\./)
		{
			if($file_s[$count] =~ m/^\.\.?$/)
			{
				next;
			}
		}
		else
		{
			if($file_s[$count] =~ m/hi3630_dtsi/)
			{
				next;
			}
			$subdir_t = $file_s[$count];
			$subdir = "$current_dir/$subdir_t";

			$pin_config_xls = get_user_choice_of_product($subdir);
			if($pin_config_xls eq "")
			{
				die("!!!Error to get xls in folder $file_s[$count]\n");
			}

			gen_modem_pin_config($subdir, $pin_config_xls, $file_s[$count]);
		}
	}

	closedir(CUR_DIR);
}

sub get_user_choice_of_product()
{
	my ($cur_dir) = @_;
	my $i = 0;
	my @products;

	opendir(PIN_DIR, $cur_dir) || return "";
	foreach $_ (sort readdir(PIN_DIR))
	{
		if(/.xls/)
		{
			$products[$i] = $_;
			#print $i,". ",$_,"\n";
			$i++;
			return $_;
		}
	}
	closedir(PIN_DIR);

	return "";
}

sub gen_modem_pin_config()
{
	my ($root_dir, $pin_filename, $file_name) = @_;
	my $pin_config_excel = "$root_dir/$pin_filename";
	
	my $product_name;
	my $pin_n = 0;
    my $pin_init_num = 0;
    my $pin_lp_num = 0;
	my $pin_normal_num = 0;	

	my $hw_pin_handle ;
	my $pin_config_file = "hisi_3630_modem_$file_name\.dtsi";

	#print "---> $pin_filename\n";
	my @temp_name = split /\./, $pin_filename;
	$product_name = pop(@temp_name);
	$product_name = pop(@temp_name);
	my $oExcel = new Spreadsheet::ParseExcel;
	my $oBook = $oExcel->Parse($pin_config_excel);
	# my $oSheet = $oBook->{Worksheet}[2];

	print "[PERL] generating $pin_config_file, please wait a while ... \n";

	open($hw_pin_handle, ">../../../../kernel/arch/arm/boot/dts/auto-generate/$pin_config_file") ||
		die("[PERL_ERROR] Failed to open file $pin_config_file for write!");
	
    printf $hw_pin_handle "/*\n";
	printf $hw_pin_handle " * Hisilicon Ltd. Hi3630 SoC\n";
	printf $hw_pin_handle " *\n";
	printf $hw_pin_handle " * Copyright (C) 2012-2013 Hisilicon Ltd.\n";
	printf $hw_pin_handle " * Author: nobody\n";
	printf $hw_pin_handle " *\n";
	printf $hw_pin_handle " * This program is free software; you can redistribute it and/or modify\n";
	printf $hw_pin_handle " * it under the terms of the GNU General Public License version 2 as\n";
	printf $hw_pin_handle " * publishhed by the Free Software Foundation.\n";
	printf $hw_pin_handle " */\n";
	printf $hw_pin_handle "\n";
	printf $hw_pin_handle "/{\n";
	printf $hw_pin_handle "	modem_pintrl {\n";
	printf $hw_pin_handle "		compatible = \"arm,modem_pintrl\";\n";
	printf $hw_pin_handle "			pinctrl-names = \"init\",\"default\",\"idle\";\n";
	printf $hw_pin_handle "			/*table: gpio_group gpio_pin mux_addr mux_value cfg_addr cfg_value gpio_dir gpio_value*/\n";
		
	$pin_init_num = gen_pin_config($oBook, $hw_pin_handle, $pin_n, "InitMode", "InitPullType", "InitGpioDirection", "InitOutputValue");
	
	$pin_n += 1;
	$pin_normal_num = gen_pin_config($oBook, $hw_pin_handle, $pin_n, "NormalMode", "NormalPullType", "MNormalGpioDirection", "MNormalOutputValue");
	
	$pin_n += 1;
	$pin_lp_num = gen_pin_config($oBook, $hw_pin_handle, $pin_n, "LPMode", "LPPullType", "MLPGpioDirection", "MLPOutputValue");

    printf $hw_pin_handle "			pinctrl-num   = <$pin_init_num $pin_normal_num $pin_lp_num>;\n";

	printf $hw_pin_handle "			status = \"disable\";\n";
	printf $hw_pin_handle "	};\n";
	printf $hw_pin_handle "};\n";
	
	close($hw_pin_handle);
	print "[PERL] $pin_config_file have done, everything is OK!\n"
	#exit 0;

}


sub gen_pin_config()
{
	my ($io_book, $hw_iomux_handle, $pin_n, $pin_mode, $pin_pull, $pin_gpio_dir, $pin_output) = @_;
	my $pin_sheet = $io_book->{Worksheet}[2];
	my $count;
	my @title_name_array;
	my %title_name_map;
	my $gpio_num;
	my $pin_mode_debug;
	my $pin_pull_debug;
	my $pin_driver_debug;
	my $pin_slew_debug;
	my $pin_gpio_dir_debug;
	my $pin_output_debug;
	my $iomg;
	my $iocg;
	my $is_modem;
	my $line_index = 2;
	my $previous_mode;
	my $pin_total = 0;

	my $max_col = $pin_sheet->{MaxCol};
	#print "$max_col\n";
	for($count = 0; $count <= $max_col; $count++)
	{
		#create title_name array automatically according to the excel's 0th line.
		if($count > 39)
		{
			$title_name_array[$count] = $pin_sheet->{Cells}[1][$count]->Value;
		}
		else
		{
			$title_name_array[$count] = $pin_sheet->{Cells}[0][$count]->Value;
		}
		#create title_name HASH array automatically.
		$title_name_map{$title_name_array[$count]} = $count;
	}

	my %pin_mode_map =
	(
		"Function_0" => "0",
		"Function_1" => "1",
		"Function_2" => "2",
		"Function_3" => "3",
		"Function_4" => "4",
		"Function_5" => "5",
		"Function_6" => "6",
		"Function_7" => "7"
	);
	
	my %pin_dir_map =
	(
		"IN" => "0",
		"OUT" => "1",
	);

	my %pin_pull_map =
	(
		"NP" => "0",
		"PU" => "1",
		"PD" => "2",
	);

	my %pin_out_vlaue =
	(
		"H" => "1",
		"L" => "0",
	);

	my $gpio_number;
	my @gpio_name;
	my $group;
	my $number_in_group;
	
	printf $hw_iomux_handle "			pinctrl-$pin_n = <\n";

	#parsing for iomg
	while(1)
	{
		$gpio_num = $pin_sheet->{Cells}[$line_index][$title_name_map{"GpioNum"}]->Value;
		$pin_mode_debug = $pin_sheet->{Cells}[$line_index][$title_name_map{$pin_mode}]->Value;
		$pin_pull_debug = $pin_sheet->{Cells}[$line_index][$title_name_map{$pin_pull}]->Value;
		$pin_driver_debug = $pin_sheet->{Cells}[$line_index][$title_name_map{"LPDriverDebug"}]->Value;
		$pin_slew_debug = $pin_sheet->{Cells}[$line_index][$title_name_map{"LPSlewRateDebug"}]->Value;
		$pin_gpio_dir_debug = $pin_sheet->{Cells}[$line_index][$title_name_map{$pin_gpio_dir}]->Value;
		$pin_output_debug = $pin_sheet->{Cells}[$line_index][$title_name_map{$pin_output}]->Value;
		$iomg = $pin_sheet->{Cells}[$line_index][$title_name_map{"MUX_S_Group_Address"}]->Value;
		$iocg = $pin_sheet->{Cells}[$line_index][$title_name_map{"Pad_Ctrl_Group_Address"}]->Value;
		$is_modem = $pin_sheet->{Cells}[$line_index][$title_name_map{"IsEffective"}]->Value;
		#print "$gpio_num $pin_mode_debug $pin_pull_debug $pin_driver_debug $iomg $iocg\n";
		
		if($is_modem ne "MODEM")
		{
			#print "$is_modem is error\n";
			$line_index += 1;
			if($line_index > $pin_sheet->{MaxRow})
			{
				last;
			}
			next;
		}
		
		if ($pin_mode_debug eq "")
		{
			$pin_mode_debug = $previous_mode;
		}
		else
		{
			$previous_mode = $pin_mode_debug;
		}
		
		@gpio_name = split /_/, $gpio_num;
		$gpio_number = pop(@gpio_name);
		$group = $gpio_number / 8;
		$number_in_group = $gpio_number % 8;
		printf  $hw_iomux_handle "						%2d         %d      ", $group, $number_in_group;
		
		if ($iomg eq "N")
		{
			print  $hw_iomux_handle "0xfff      ";
		}
		else
		{
		    print  $hw_iomux_handle "$iomg      ";
		}

		print  $hw_iomux_handle "$pin_mode_map{$pin_mode_debug}       ";
		print  $hw_iomux_handle "$iocg      ";
		print  $hw_iomux_handle "$pin_pull_map{$pin_pull_debug}           ";

		print  $hw_iomux_handle "$pin_dir_map{$pin_gpio_dir_debug}           ";
		print  $hw_iomux_handle "$pin_out_vlaue{$pin_output_debug}";
		print  $hw_iomux_handle "\n";
		
		$pin_total += 1;

		$line_index += 1;
		if($line_index > $pin_sheet->{MaxRow})
		{
			last;
		}
	}
	
	printf $hw_iomux_handle "						>;\n";
	
	return $pin_total;
}

&my_main();
