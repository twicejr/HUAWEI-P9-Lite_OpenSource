# Copyright (c) 2013, The Linux Foundation. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above
#       copyright notice, this list of conditions and the following
#       disclaimer in the documentation and/or other materials provided
#       with the distribution.
#     * Neither the name of The Linux Foundation nor the names of its
#       contributors may be used to endorse or promote products derived
#       from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
# ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
# BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
# BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
# IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# parser.pl
#
use FindBin qw($Bin);
use lib "$Bin/lib";
use lib "$Bin/share";
use XML::LibXML;
use IO::Handle;
use warnings;
use strict;

# initialize the parser
my $parser = new XML::LibXML;


# open a filehandle and parse
my $fh = new IO::Handle;

my @structDataMap = (
	[ "\"rgb_swap_rgb\"", 0 ],
	[ "\"rgb_swap_rbg\"", 1 ],
	[ "\"rgb_swap_bgr\"", 2 ],
	[ "\"rgb_swap_brg\"", 3 ],
	[ "\"rgb_swap_grb\"", 4 ],
	[ "\"rgb_swap_gbr\"", 5 ],
	[ "\"burst_mode\"", 2 ],
	[ "\"non_burst_sync_event\"", 1 ],
	[ "\"tight\"", 0 ],
	[ "\"loose\"", 1 ],
	[ "\"lane_map_0123\"", 0 ],
	[ "\"lane_map_3012\"", 1 ],
	[ "\"lane_map_2301\"", 2 ],
	[ "\"lane_map_1230\"", 3 ],
	[ "\"lane_map_0321\"", 4 ],
	[ "\"lane_map_1032\"", 5 ],
	[ "\"lane_map_2103\"", 6 ],
	[ "\"lane_map_3210\"", 7 ],
	[ "\"none\"", 0 ],
	[ "\"trigger_sw\"", 4 ],
);

my $name = "";
my $nameinH = "";
my $Version = "";
my $xmldoc = $parser->parse_file($ARGV[0]);
my $fastboot_include_folder = $ARGV[2];

if(scalar @ARGV < 2)
{
	print "2 command line arguments required.\n";
	print "1:XML Document to parse\n";
	print "2:[Panel|Platform]\n";
	print "Example: perl parse.pl Panel.xml Panel\n";
	exit 1;
}

if(uc($ARGV[1]) eq "PANEL")
{
	for my $property($xmldoc->findnodes('/GCDB/Version'))
	{
		$Version = $property->textContent();
	}

	for my $property($xmldoc->findnodes('/GCDB/PanelId'))
	{
		$name = $property->textContent();
	}

	for my $property($xmldoc->findnodes('/GCDB/PanelH'))
	{
		$nameinH = $property->textContent();
	}
	open (my $PANELH, '>'.$fastboot_include_folder.'/hw_panel_' . $nameinH . '.h') or die $!;
	printheader($PANELH);
	print $PANELH "\n#ifndef _PANEL_". uc($nameinH) . "_H_\n";
	print $PANELH "\n#define _PANEL_". uc($nameinH) . "_H_\n";

	printSectionHeader($PANELH, "HEADER files");

#	print $PANELH "#include \"hw_panel.h\"\n\n";
	print $PANELH "\n\n";

	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{
		my @panelConfigAttrs = ("PanelXres", "PanelYres",
		"PanelWidth", "PanelHeight", "PanelOrientation",
		"PanelBpp", "PanelBgrfmt", "PanelBlType",
		"PanelBlmin", "PanelBlmax", "PanelType", "PanelCompatible",
		"PanelIfbcType",
		"PanelFrcEnable", "PanelEsdEnable", "PanelCeSupport",
		"PanelPrefixSharpSupport", "PanelSblSupport", "PanelAcmSupport",
		"PanelAcmCeSupport", "PanelGammaSupport", "PanelPxlClk",
		"PanelPxlClkDiv", "PanelDirtUpdtSupport", "PanelDsiUptSupport",
		"PanelVsynCtrType", "PanelStepSupport");

		printSectionHeader($PANELH, "Panel Information");
		printStruct($PANELH, \@panelConfigAttrs, $property,
			"panel_info", lc($nameinH) . "_panel_info");
		print $PANELH "\n";
	}

	print $PANELH "\n";

	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{
		printSectionHeader($PANELH, "Ldi Information" );
		my @panelConfigAttrs = ("LdiHBackPorch", "LdiHFrontPorch",
		"LdiHPulseWidth", "LdiVBackPorch",
		"LdiVFrontPorch", "LdiVPulseWidth", "LdiHsyncPlr",
		"LdiVsyncPlr", "LdiPixelClkPlr", "LdiDataEnPlr", 
		"LdiDpi0OverlapSize", "LdiDpi1OverlapSize");

		printStruct($PANELH, \@panelConfigAttrs, $property,
			"panel_ldi", lc($nameinH) . "_panel_ldi");
		print $PANELH "\n";
	}

	print $PANELH "\n";
	
	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{
		printSectionHeader($PANELH, "Sbl Information" );
		my @panelConfigAttrs = ("SblStrenLimit", "SblCalA",
		"SblCalB", "SblCalC", "SblCalD",
		"SblTfCtl", "SblBlmin", "SblBlmax",
		"SblBlScale", "SblAmLightMin", "SblFilterA",
		"SblFilterB", "SblLogoLeft", "SblLogoTop");

		printStruct($PANELH, \@panelConfigAttrs, $property,
			"panel_smart_bl", lc($nameinH) . "_panel_smart_bl");
		print $PANELH "\n";
	}	
	
	print $PANELH "\n";
	
	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{
		printSectionHeader($PANELH, "Mipi Information" );
		my @panelConfigAttrs = ("MipiVc", "MipiLaneNums",
		"MipiColorMode", "MipiDsiBitClk", "MipiBurstMode",
		"MipiMaxEscClk", "MipiDsiBitClkVal1", "MipiDsiBitClkVal2",
		"MipiDsiBitClkVal3", "MipiDsiBitClkVal4", "MipiDsiBitClkVal5",
		"MipiDsiBitClkUpt", "MipiNonContinueEnable", "MipiClkPostAdjust");

		printStruct($PANELH, \@panelConfigAttrs, $property,
			"panel_mipi", lc($nameinH) . "_panel_mipi");
		print $PANELH "\n";
	}

	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{
		printSectionHeader($PANELH, "Dirty region Information" );
		my @panelConfigAttrs = ("DirtLeftAlign", "DirtRightAlign",
		"DirtTopAlign", "DirtBottAlign", "DirtWidthAlign",
		"DirtHeightAlign", "DirtWidthMin", "DirtHeightMin",
		"DirtTopStart", "DirtBottStart");

		printStruct($PANELH, \@panelConfigAttrs, $property,
			"panel_dirty_region", lc($nameinH) . "_panel_dirty_region");
		print $PANELH "\n";
	}

	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{
		printSectionHeader($PANELH, "platform Config" );
		my @panelConfigAttrs = ("GpioReset", "GpioTe", "LcdanalogVcc",
		"LcdioVcc", "LcdBias", "LcdVsp",
		"LcdVsn", "LcdRstFirstHigh", "LcdRstLow",
		"LcdRstSecondHight");

		printStruct($PANELH, \@panelConfigAttrs, $property,
			"platform_config", lc($nameinH) . "_panel_platform_config");
		print $PANELH "\n";
	}

	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{
		printSectionHeader($PANELH, "misc Information" );
		my @panelConfigAttrs = ("IovccOffIsNeedDelay", "IovccOnIsNeedReset",
		"LcdCtrlTpPower", "LockCmdSupport", "ReadPowerStatus");

		printStruct($PANELH, \@panelConfigAttrs, $property,
			"misc_info", lc($nameinH) . "_panel_misc_info");
		print $PANELH "\n";
	}

	print $PANELH "\n";
	printSectionHeader($PANELH, "Panel on/off command information" );

	for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/OnCommand'))
	{
		printOnCommand($PANELH, $property, lc($nameinH) .
				"_on_cmds", lc($nameinH) . "_on_cmds");
		print $PANELH "\n";
	}
	for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/OffCommand'))
	{
		printOnCommand($PANELH, $property, lc($nameinH) .
			"_off_cmds", lc($nameinH) . "_off_cmds");
		print $PANELH "\n\n";
	}
	
	for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/PanelRotation'))
	{
		printSectionHeader($PANELH, "Panel rotation");
		printOnCommand($PANELH, $property, lc($nameinH) .
				"_rotation", lc($nameinH) . "_rotation_cmd");
		print $PANELH "\n\n";
	}

	for my $tmpProperty($xmldoc->findnodes('/GCDB/PanelEntry/ResetSequence'))
	{
		printSectionHeader($PANELH, "Panel reset sequence");
		print $PANELH "static struct panel_reset_sequence " .
				lc($nameinH) . "_reset_seq = {\n\t";

		printResetSeqinH($PANELH, $tmpProperty);
		print $PANELH "\n"
	}

	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{

		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/DelaytimeBeforeBL'))
		{
			printSectionHeader($PANELH, " delay time before turn on backlight");
			(my $element) = $property->textContent();
			print $PANELH "int ". lc($nameinH) ."_delaytime_before_bl = " . $element . ";\n";
		}
	}
	print $PANELH "\n#endif /*_PANEL_" . uc($nameinH) . "_H_*/\n";
	close ($PANELH);
}
elsif(uc($ARGV[1]) eq "PLATFORM")
{
	for my $property($xmldoc->findnodes('/GCDB/Version'))
	{
		$Version = $property->textContent();
	}

	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/PlatformId')){
		($name) = $property->textContent() =~ /"([^"]*)"/;
	}

	open (my $PLATFORMDTSI, '>platform-' . $name . '.dtsi');
	open (my $PLATFORMH, '>platform_' . $name . '.h');
	print $PLATFORMDTSI "/*\n " . $name . " target DTSI file.\n*/\n{\n";
	print $PLATFORMDTSI "\tqcom,platform = \"" . $name . "\";\n";

	printheader($PLATFORMH);
	print $PLATFORMH "\n#ifdef _PLATFORM_" . uc($name) . "_H_\n";

	printSectionHeader($PLATFORMH, "HEADER files");
	print $PLATFORMH "#include <display_resource.h>\n\n";
	printSectionHeader($PLATFORMH, "GPIO configuration");

	my @gpioConfAttrs = ("PinSource", "PinId", "PinStrength",
				"PinDirection",	"Pull", "PinState");

	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/ResetGPIO'))
	{
		printStruct($PLATFORMH, \@gpioConfAttrs, $property, "gpio_pin",
								"reset_gpio");
		print $PLATFORMH "\n\n";

		printGPIO($PLATFORMDTSI, $property, "hisilicon,platform-reset-gpio");
	}
	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/EnableGPIO'))
	{
		printStruct($PLATFORMH, \@gpioConfAttrs, $property, "gpio_pin",
								"enable_gpio");
		print $PLATFORMH "\n\n";

		printGPIO($PLATFORMDTSI, $property, "hisilicon,platform-enable-gpio");
	}
	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/TEGPIO'))
	{
		printStruct($PLATFORMH, \@gpioConfAttrs, $property, "gpio_pin",
								 "te_gpio");
		print $PLATFORMH "\n\n";

		printGPIO($PLATFORMDTSI, $property, "hisilicon,platform-te-gpio");
	}
	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/ModeGPIO'))
	{
		printStruct($PLATFORMH, \@gpioConfAttrs, $property, "gpio_pin",
								 "mode_gpio");
		print $PLATFORMH "\n\n";

		printGPIO($PLATFORMDTSI, $property, "hisilicon,platform-mode-gpio");
	}
	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/BacklightGPIO'))
	{
		printStruct($PLATFORMH, \@gpioConfAttrs, $property,
						"gpio_pin", "bklight_gpio");
		print $PLATFORMH "\n\n";

		printGPIO($PLATFORMDTSI, $property, "hisilicon,platform-bklight-gpio");
	}
	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/PWMGPIO'))
	{
		printStruct($PLATFORMH, \@gpioConfAttrs, $property, "gpio_pin",
								"pwm_gpio");
		print $PLATFORMH "\n\n";

		printGPIO($PLATFORMDTSI, $property, "hisilicon,platform-pwm-gpio");
	}
	printSectionHeader($PLATFORMH, "Supply configuration");
	print $PLATFORMH "static struct ldo_entry ldo_entry_array[] = {\n  ";
	my @ldoEntryAttrs = ("SupplyName", "SupplyMinVoltage", "SupplyMaxVoltage",
			"SupplyEnableLoad", "SupplyDisableLoad", "SupplyPreOnSleep",
			"SupplyPostOnSleep", "SupplyPreOffSleep", "SupplyPostOffSleep");
	my @ldoEntryAttrsinH = ("SupplyName", "SupplyId", "SupplyType", "SupplyMaxVoltage",
			"SupplyEnableLoad", "SupplyDisableLoad","SupplyPreOnSleep",
			"SupplyPostOnSleep", "SupplyPreOffSleep", "SupplyPostOffSleep");
	my $ldocounter = 0;

	for (my $i = 1; $i <= 5; $i++)
	{
		for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/SupplyEntry' . $i))
		{
			printSupplyinH($PLATFORMH, \@ldoEntryAttrsinH, $property);
			$ldocounter++;

			printSupplyEntry($PLATFORMDTSI, \@ldoEntryAttrs, $property,
						"hisilicon,platform-supply-entry" . $i);
		}
	}

	print $PLATFORMH "};\n\n";
	print $PLATFORMH "#define TOTAL_LDO_DEFINED " . $ldocounter . "\n\n";

	printSectionHeader($PLATFORMH, "Target Physical configuration");
	print $PLATFORMH "\n";
	print $PLATFORMDTSI "\n";

	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/PanelStrengthCtrl'))
	{
		printTargetPhysical($PLATFORMH, $property, "panel_strength_ctrl", "uint32_t");
		print $PLATFORMH "\n\n";

		printHexArray($PLATFORMDTSI, $property, "hisilicon,platform-strength-ctrl");
	}

	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/PanelBISTCtrl'))
	{
		printTargetPhysical($PLATFORMH, $property, "panel_bist_ctrl", "char");
		print $PLATFORMH "\n\n";

		printHexArray($PLATFORMDTSI, $property, "hisilicon,platform-bist-ctrl");
	}

	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/PanelRegulatorSettings'))
	{
		printTargetPhysical($PLATFORMH, $property, "panel_regulator_settings", "uint32_t");
		print $PLATFORMH "\n\n";

		printHexArray($PLATFORMDTSI, $property, "hisilicon,platform-regulator-settings");
	}

	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/PanelLaneConfig'))
	{
		printTargetPhysical($PLATFORMH, $property, "panel_lane_config", "char");
		print $PLATFORMH "\n\n";

		printHexArray($PLATFORMDTSI, $property, "hisilicon,platform-lane-config");
	}

	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/PanelPhysicalCtrl'))
	{
		printTargetPhysical($PLATFORMH, $property, "panel_physical_ctrl", "uint32_t");
		print $PLATFORMH "\n\n";

		printHexArray($PLATFORMDTSI, $property, "hisilicon,platform-physical-ctrl");
	}

	printSectionHeader($PLATFORMH, "Other Configuration");
	print $PLATFORMH "\n";
	print $PLATFORMDTSI "\n";
	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/ContinuousSplash'))
	{
		my $splash = $property->textContent();
		print $PLATFORMH "#define " . $name . "_CONTINUOUS_SPLASH " . $splash . "\n\n";

		my @attrs = ("ContinuousSplash");
		printArray($PLATFORMDTSI, \@attrs, $xmldoc->findnodes('/GCDB/PlatformEntry'),
					"hisilicon,platform-continuous-splash");
	}
	for my $property ($xmldoc->findnodes('/GCDB/PlatformEntry/DSIFeatureEnable'))
	{
		my $dsi = $property->textContent();
		print $PLATFORMH "#define " . $name . "_DSI_FEATURE_ENABLE " . $dsi . "\n";

		my @attrs = ("DSIFeatureEnable");
		printArray($PLATFORMDTSI, \@attrs, $xmldoc->findnodes('/GCDB/PlatformEntry'),
					"hisilicon,platform-dsi-feature-enable");
	}

	print $PLATFORMH "\n#endif /*_PLATFORM_" . uc($name) . "_H_*/\n";
	print $PLATFORMDTSI "};\n";

	close ($PLATFORMH);
	close ($PLATFORMDTSI);
}


sub printHexArray
{
	my $fh = shift;
	my $property = shift;
	my $name = shift;
	(my $element) = $property->textContent() =~ /"([^"]*)"/;
	$element =~ s/,//g;
#	$element =~ s/0x//g;
	print $fh "\t\t" . $name . " = <\n\t\t\t\t\t" . $element . ">;\n";

}

sub printTargetPhysical
{
	my $fh = shift;
	my $property = shift;
	my $name = shift;
	my $datatype = shift;
	(my $element) = $property->textContent() =~ /"([^"]*)"/;
	print $fh "static const " . $datatype . " " . $name . "[] = {\n\t";
	$element =~ s/\t//g;
	$element =~ s/^//mg;
	print $fh $element . "\n};";
}

#/* delete space when print on command in header file */
sub printOnCommand
{
	my $fh = shift;
	my $property = shift;
	my $name = shift;
	my $cmdname = shift;
	(my $element) = $property->textContent() =~ /"([^"]*)"/;
	my @lines = split /\n/, $element;
	my $toPrint = "";
	my $i = 0;
	foreach my $line (@lines)
	{
		my @sep = split /,/, $line;
		print $fh "static char " . $cmdname . $i . "[] = {\n";
		$toPrint = "";
		$toPrint = "    ";
		if(scalar @sep > 5)
		{
			my $cmdlen = $sep[4];
			my $cmdtype = $sep[0];
			$cmdtype =~ s/ //g;
			$cmdtype =~ s/\t//g;
			$cmdlen =~ s/ //g;
			$cmdlen =~ s/\t//g;

			my $j = 0;
			for(my $i = 5; $i < scalar @sep; $i++)
			{
				my $tmp = $sep[$i];
				$tmp =~ s/ //g;
				$tmp =~ s/\t//g;
				if($tmp ne "")
				{
					if($i == (scalar @sep - 1))
					{
						$toPrint  .= $tmp . ",";
					}
					else
					{
						$toPrint  .= $tmp . ", ";
					}
					$j++;
				}
				if ($i == 5 && $i != (scalar @sep - 1))
				{
					chop($toPrint);
					$toPrint .= "\n";
					$toPrint .= "    ";
				}	
			}
			$toPrint .= "\n};\n"
		}
		$i++;

#		$toPrint .= "\n\n";
		print $fh $toPrint ;
	}

	print $fh "\nstatic struct dsi_cmd_desc " . $name . "[] = {\n";
	my $bool = 0;
	$toPrint = "";
	$i = 0;

	foreach my $line (@lines)
	{
		my @sep = split /,/, $line;
		$toPrint .= "    {\n";
		if(scalar @sep > 4)
		{
			my $cmdtype = $sep[0];
			my $waittype = $sep[3];
			$cmdtype =~ s/ //g;
			$cmdtype =~ s/\t//g;
			$waittype =~ s/ //g;
			$waittype =~ s/\t//g;

			my $cmdsize = 0;
			my $dtype = "";
			my $vc = 0;
			my $delaytype = "";
			my $cmdsleep = $sep[2];			
			$cmdsleep =~ s/ //g;
			$cmdsleep =~ s/\t//g;

			if($cmdtype eq "0x39")
			{
				$dtype = "DTYPE_DCS_LWRITE, ";
			}
			elsif($cmdtype eq "0x29")
			{
				$dtype = "DTYPE_GEN_LWRITE, ";
			}
			elsif($cmdtype eq "0x15")
			{
				$dtype = "DTYPE_DCS_WRITE1, ";
			}
			elsif($cmdtype eq "0x05")
			{
				$dtype = "DTYPE_DCS_WRITE, ";
			}
			else
			{
				$dtype = "DTYPE_GEN_LWRITE, ";
			}
			
			if($waittype eq "0x01")
			{
				$delaytype = "WAIT_TYPE_MS,";
			}
			else
			{
				$delaytype = "WAIT_TYPE_US,";
			}
			$toPrint .= "        ";
			$toPrint .= $dtype;
			$toPrint .= $vc . ", ";
			$toPrint .= $cmdsleep . ", ";
			$toPrint .= $delaytype;
			$toPrint .= "\n";
			$toPrint .= "        sizeof(" . $cmdname . $i . "), " . $cmdname . $i;
			$toPrint .= "\n";
			$toPrint .= "    },\n";
			$i++;
		}
	}
#	chop($toPrint);
#	chop($toPrint);
#	$toPrint .= "\n";
	print $fh $toPrint . "};";


#	print $fh "\n#define " . uc($name) . " " . $i . "\n";
}

sub printLcdEffect
{
	my $fh = shift;
	my $property = shift;
	my $name = shift;
	my $cmdname = shift;
	(my $element) = $property->textContent() =~ /"([^"]*)"/;
	my @lines = split /\n/, $element;
	my $toPrint = "";
	my $i = 0;
	
	print $fh "static u32 " . $cmdname . "[] = {\n";
	$toPrint = "";
	$toPrint = "\t";
	
	foreach my $line (@lines)
	{
		my @sep = split /,/, $line;
		for(my $i = 0; $i < scalar @sep; $i++)
		{
			my $tmp = $sep[$i];
			$tmp =~ s/ //g;
			$tmp =~ s/\t//g;
			if($tmp ne "")
			{
				if($i == (scalar @sep - 1))
				{
					$toPrint .= $tmp . ",";
				}
				else
				{
					$toPrint .= $tmp . ", ";
				}
			}
			if($i == 15)
			{
				chop($toPrint);
				$toPrint .= ",";
				$toPrint .= "\n";
				$toPrint .= "\t";
			}
		}
	}
	chop($toPrint);
	$toPrint .= "};\n";
	print $fh $toPrint ;
}

sub printLcdEffect3x3Array
{
	my $fh = shift;
	my $property = shift;
	my $name = shift;
	my $cmdname = shift;
	(my $element) = $property->textContent() =~ /"([^"]*)"/;
	my @lines = split /\n/, $element;
	my $toPrint = "";
	my $i = 0;
	my $row = 0;
	
	print $fh "static u32 " . $cmdname . "[9][9][9] = {\n";
	$toPrint = "";

	foreach my $line (@lines)
	{
		my @sep = split /,/, $line;
		
		if(($row % 9) == 0)
		{
			$toPrint .= "\t{";
			$toPrint .= "\n";
			$toPrint .= "\t\t{";
		}
		else
		{
			$toPrint .= "\t\t{";
		}

		for(my $i = 0; $i < scalar @sep; $i++)
		{
			my $tmp = $sep[$i];
			$tmp =~ s/ //g;
			$tmp =~ s/\t//g;

			if($tmp ne "")
			{
				if($i == (scalar @sep - 1))
				{
					$toPrint .= $tmp . ",";
				}
				else
				{
					$toPrint .= $tmp . ", ";
				}
			}	
			if($i == 8)
			{
				$toPrint .= "},";
				$toPrint .= "\n";
			}				
		}
		$row++;		
		if(($row % 9) == 0)
		{
			$toPrint .= "\t";
			$toPrint .= "},";
			$toPrint .= "\n";
		}		
	}
	#chop($toPrint);
	$toPrint .= "};\n";
	print $fh $toPrint ;
}

sub printLcdEffect1x1Array
{
	my $fh = shift;
	my $property = shift;
	my $name = shift;
	my $cmdname = shift;
	(my $element) = $property->textContent() =~ /"([^"]*)"/;
	my @lines = split /\n/, $element;
	my $toPrint = "";
	my $i = 0;
	my $row = 0;
	
	print $fh "static u32 " . $cmdname . "[] = {";
	$toPrint = "";

	foreach my $line (@lines)
	{
		my @sep = split /,/, $line;
		
		for(my $i = 0; $i < scalar @sep; $i++)
		{
			my $tmp = $sep[$i];
			$tmp =~ s/ //g;
			$tmp =~ s/\t//g;

			if($tmp ne "")
			{
				if($i == (scalar @sep - 1))
				{
					$toPrint .= $tmp . ",";
				}
				else
				{
					$toPrint .= $tmp . ", ";
				}
			}				
		}
	}
	#chop($toPrint);
	$toPrint .= "};\n";
	print $fh $toPrint ;
}

sub printSupplyPower
{
	my $fh = shift;
	my $property = shift;
	my $toPrint = "";
	$toPrint .= "{ ";
	for (my $i = 1; $i <=5; $i++)
	{
		for my $element ($property->findnodes("SupplyEntryId" . $i))
		{
			$toPrint .= $element->textContent() . ", ";
		}
	}
	$toPrint .= "}, { ";
	for (my $i = 1; $i <=5; $i++)
	{
		for my $element ($property->findnodes("Sleep" . $i))
		{
			$toPrint .= $element->textContent() . ", ";
		}
	}
	$toPrint .= "}\n};";
	print $fh $toPrint;
}

#/* modift seq format */
sub printResetSeqinH
{
	my $fh = shift;
	my $property = shift;
	print $fh "{ ";
	for (my $i = 1; $i <=10; $i++)
	{
		for my $element ($property->findnodes("PinState" . $i))
		{
			print $fh $element->textContent() . ", ";
		}
	}
	print $fh "}, { ";
	for (my $i = 1; $i <=10; $i++)
	{
		for my $element ($property->findnodes("PulseWidth" . $i))
		{
			print $fh $element->textContent() . ", ";
		}
	}
	print $fh "}, ";
	for my $element ($property->findnodes("EnableBit"))
	{
		print $fh $element->textContent();
		print $fh "\n};\n";
	}
}

sub printResetSeq
{
	my $fh = shift;
	my $property = shift;
	my $name = shift;
	print $fh "\t\t" . $name . " = <";
	my $first = 1;
	for (my $i = 1; $i <=10; $i++)
	{
		for my $element ($property->findnodes("./PinState" . $i))
		{
			if($first == 1)
			{
				$first = 0;
			}
			else
			{
				print $fh ">, <";
			}
			print $fh $element->textContent();
		}
		for my $element ($property->findnodes("./PulseWidth" . $i))
		{
			print $fh " ";
			print $fh $element->textContent();
		}
	}
	print $fh ">;\n";
}

sub printSupplyinH
{
	my $fh = shift;
	my $attrs = shift;
	my @attrs = @$attrs;
	my $property = shift;
	my $flag = 0;
	print $fh "{ ";
	foreach (@attrs) {
		my $node = "./" . $_;
		my $found = 0;
		for my $element ($property->findnodes($node))
		{
			$found = 1;
			if($flag == 1)
			{
				print $fh ", ";
			}
			else
			{
				$flag = 1;
			}
			print $fh $element->textContent();
		}
		if($found == 0)
		{
			if($flag == 1)
			{
				print $fh ", ";
			}
			else
			{
				$flag = 1;
			}
			print $fh 0;
		}
	}
	print $fh "},\n";
}

sub convertLower
{
	my $input = shift;
	for (my $i = 1; $i < length($input); $i++) {
		if (ord(substr($input, $i, 1)) <= ord('Z'))
		{
			substr($input, $i, 1) = lc(substr($input, $i, 1));
			$input = substr($input, 0, $i) . '-' . substr($input, $i, length($input));
		}
	}
	return lc($input);
}

sub convertLowerPlus
{
	my $input = shift;
	for (my $i = 1; $i < length($input); $i++) {
		if (ord(substr($input, $i, 1)) <= ord('Z'))
		{
			substr($input, $i, 1) = lc(substr($input, $i, 1));
			$input = substr($input, 0, $i) . '_' . substr($input, $i, length($input));
		}
	}
	return lc($input);
}

sub printSupplyEntry
{
	my $fh = shift;
	my $attrs = shift;
	my @attrs = @$attrs;
	my $property = shift;
	my $name = shift;
	print $fh "\t" . $name . " {\n";
	foreach(@attrs)
	{
		for my $element ($property->findnodes("./" . $_))
		{
			if ($element->textContent() =~ /\D/)
			{
				print $fh "\t\tqcom," . convertLower($_) . " = " . $element->textContent() . ";\n";
			}
			else
			{
				print $fh "\t\tqcom," . convertLower($_) . " = <" . $element->textContent() . ">;\n";
			}
		}
	}
	print $fh "\t};\n\n";
}

sub printArray
{
	my $fh = shift;
	my $attrs = shift;
	my @attrs = @$attrs;
	my $property = shift;
	my $name = shift;
	my $first = 1;
	foreach(@attrs)
	{
		for my $element ($property->findnodes("./" . $_))
		{
			print $fh "\t\t" . $name . " = <";
			if($first == 1)
			{
				$first = 0;
			}
			else
			{
				print $fh " ";
			}
			print $fh $element->textContent() . ">;\n";
		}
	}
}

sub printArrayChar
{
	my $fh = shift;
	my $attrs = shift;
	my @attrs = @$attrs;
	my $property = shift;
	my $name = shift;
	my $first = 1;
	foreach(@attrs)
	{
		for my $element ($property->findnodes("./" . $_))
		{
			print $fh "<&";
			if($first == 1)
			{
				$first = 0;
			}
			else
			{
				print $fh " ";
			}
			print $fh $element->textContent() . ">";
		}
	}
}

sub printControlType
{
	my $fh = shift;
	my $attrs = shift;
	my @attrs = @$attrs;
	my $property = shift;
	my $name = shift;
	my $first = 1;
	foreach(@attrs)
	{
		for my $element ($property->findnodes("./" . $_))
		{
			print $fh "\t\t" . $name . " = \"";
			if($element->textContent() eq "0")
			{
				print $fh "bl_ctrl_pwm";
			}
			elsif($element->textContent() eq "1")
			{
				print $fh "bl_ctrl_wled";
			}
			elsif($element->textContent() eq "2")
			{
				print $fh "bl_ctrl_dcs";
			}
			print $fh "\";\n";
		}
	}
}

sub printCommandState
{
	my $fh = shift;
	my $attrs = shift;
	my @attrs = @$attrs;
	my $property = shift;
	my $name = shift;
	my $first = 1;
	foreach(@attrs)
	{
		for my $element ($property->findnodes("./" . $_))
		{
			print $fh "\t\t" . $name . " = \"";
			if($element->textContent() eq "0")
			{
				print $fh "dsi_lp_mode";
			}
			else
			{
				print $fh "dsi_hs_mode";
			}
			print $fh "\";\n";
		}
	}
}

sub printPanelType
{
	my $fh = shift;
	my $attrs = shift;
	my @attrs = @$attrs;
	my $property = shift;
	my $name = shift;
	my $first = 1;
	foreach(@attrs)
	{
		for my $element ($property->findnodes("./" . $_))
		{
			print $fh "\t\t" . $name . " = \"";
			if($element->textContent() eq "0")
			{
				print $fh "dsi_video_mode";
			}
			else
			{
				print $fh "dsi_cmd_mode";
			}
			print $fh "\";\n";
		}
	}
}

sub printBoolean
{
	my $fh = shift;
	my $attrs = shift;
	my @attrs = @$attrs;
	my $property = shift;
	my $name = shift;
	my $first = 1;
	foreach(@attrs)
	{
		for my $element ($property->findnodes("./" . $_))
		{
			if($element->textContent() eq "1")
			{
				print $fh "\t\t" . $name ;
				print $fh ";\n";
			}
		}
	}
}

sub printGPIO
{
	my $fh = shift;
	my $property = shift;
	my $name = shift;
	print $fh "\t" . $name . " = <";
	for my $element ($property->findnodes("./PinSource"))
	{
		print $fh "&";
		print $fh $element->textContent() =~ /"([^"]*)"/;
		print $fh " ";
	}
	for my $element ($property->findnodes("./PinId"))
	{
		print $fh $element->textContent() . " ";
	}
	for my $element ($property->findnodes("./PinState"))
	{
		print $fh $element->textContent();
	}
	print $fh ">;\n";
}


sub printStruct
{
	my $fh = shift;
	my $attrs = shift;
	my @attrs = @$attrs;
	my $property = shift;
	my $structName = shift;
	my $name = shift;
	print $fh "static struct " . $structName . " " . $name . " = {\n  ";
	my $flag = 0;
	my $value = "";
	my $targetValue = "";
	foreach (@attrs) {
		my $node = "./" . $_;
		my $found = 0;		
	
		for my $element ($property->findnodes($node))
		{
			$found = 1;
			if($flag == 1)
			{
				print $fh ", ";
			}
			else
			{
				$flag = 1;
			}

			$value = $element->textContent();
			$targetValue = $value;
			for my $i ( 0 .. $#structDataMap ) {
				if ($value eq $structDataMap[$i][0]) {
					$targetValue = $structDataMap[$i][1];
					last;
				}
			}

			print $fh $targetValue;
			if($_ eq "PanelIfbcType")
			{
				for my $property($xmldoc->findnodes('/GCDB/PanelH'))
				{
					my $nameinH = $property->textContent();
				}
				print $fh ", \"/" . $nameinH . "\"";
			}
		}
		if($found == 0)
		{
			if($flag == 1)
			{
				print $fh ", ";
			}
			else
			{
				$flag = 1;
			}
			print $fh 0;
		}
	}
	print $fh "\n};"
}

sub printDataStruct
{
	my $fh = shift;
	my $attrs = shift;
	my @attrs = @$attrs;
	my $property = shift;
	my $structName = shift;
	my $name = shift;
	my $nameinDTS = shift;
	print $fh "static struct " . $structName . " " . $name . " = {\n\t";
	my $flag = 0;
	my $firsttime = 1;
	print $fh "\"" . $nameinDTS . "\", ";
	for my $element ($property->findnodes("./PanelController"))
	{
		my $controller = $element->textContent();
		if ($controller eq "\"dss_dsi1\"")
		{
			print $fh "\"dsi:1:\", ";
		}
		else
		{
			print $fh "\"dsi:0:\", ";
		}
	}
	shift(@attrs);
	foreach (@attrs) {
		my $node = "./" . $_;
		my $found = 0;
		for my $element ($property->findnodes($node))
		{
			$found = 1;
			if($flag == 1)
			{
				print $fh ", ";
			}
			else
			{
				$flag = 1;
			}
			print $fh $element->textContent();
		}
		if($found == 0)
		{
			if($flag == 1)
			{
				print $fh ", ";
			}
			else
			{
				$flag = 1;
			}
			print $fh 0;
		}
		#if ($firsttime == 1)
		#{
		#	print $fh ",\n\t";
		#	$flag = 0;
		#}
		$firsttime = 0;
	}
	print $fh "\n};"
}

sub printSectionHeader
{
	my $fh = shift;
	my $section = shift;
	print $fh "/*---------------------------------------------------------------------------*/\n";
	print $fh "/* " . $section;
	for (my $i = length($section); $i <= 73; $i++) {
		print $fh " ";
	}
	print $fh "*/\n";
	print $fh "/*---------------------------------------------------------------------------*/\n";
}

sub printheader
{
	my $fh = shift;
	print $fh "/* Copyright (c) 2013, The Linux Foundation. All rights reserved.\n";
	print $fh " *\n";
	print $fh " * Redistribution and use in source and binary forms, with or without\n";
	print $fh " * modification, are permitted provided that the following conditions\n";
	print $fh " * are met:\n";
	print $fh " *  * Redistributions of source code must retain the above copyright\n";
	print $fh " *    notice, this list of conditions and the following disclaimer.\n";
	print $fh " *  * Redistributions in binary form must reproduce the above copyright\n";
	print $fh " *    notice, this list of conditions and the following disclaimer in\n";
	print $fh " *    the documentation and/or other materials provided with the\n";
	print $fh " *    distribution.\n";
	print $fh " *  * Neither the name of The Linux Foundation nor the names of its\n";
	print $fh " *    contributors may be used to endorse or promote products derived\n";
	print $fh " *    from this software without specific prior written permission.\n";
	print $fh " *\n";
	print $fh " * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS\n";
	print $fh " * \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT\n";
	print $fh " * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS\n";
	print $fh " * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE\n";
	print $fh " * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,\n";
	print $fh " * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,\n";
	print $fh " * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS\n";
	print $fh " * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED\n";
	print $fh " * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,\n";
	print $fh " * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT\n";
	print $fh " * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF\n";
	print $fh " * SUCH DAMAGE.\n";
	print $fh " */\n";
	print $fh "\n";
	print $fh "/*---------------------------------------------------------------------------\n";
	print $fh " * This file is autogenerated file using gcdb parser. Please do not edit it.\n";
	print $fh " * Update input XML file to add a new entry or update variable in this file\n";
	print $fh " * VERSION = " . $Version . "\n";
	print $fh " *---------------------------------------------------------------------------*/\n";
}

sub printdtsheader
{
	my $fh = shift;
	my $name = shift;

	print $fh "/* Copyright (c) 2013, The Linux Foundation. All rights reserved.\n";
	print $fh " *\n";
	print $fh " * This program is free software; you can redistribute it and/or modify\n";
	print $fh " * it under the terms of the GNU General Public License version 2 and\n";
	print $fh " * only version 2 as published by the Free Software Foundation.\n";
	print $fh " *\n";
	print $fh " * This program is distributed in the hope that it will be useful,\n";
	print $fh " * but WITHOUT ANY WARRANTY; without even the implied warranty of\n";
	print $fh " * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n";
	print $fh " * GNU General Public License for more details.\n";
	print $fh " */\n\n";
	print $fh "/*---------------------------------------------------------------------------\n";
	print $fh " * This file is autogenerated file using gcdb parser. Please do not edit it.\n";
	print $fh " * Update input XML file to add a new entry or update variable in this file\n";
	print $fh " * VERSION = " . $Version . "\n";
	print $fh " *---------------------------------------------------------------------------*/\n";

	print $fh "/{\n";
	print $fh "\tdss_dsi_" . lc($name) . ":" . lc($name) . " {\n";
}
sub printClocks
{	
	my $fn = shift;
	my $property = shift;
	my $name = shift;
	(my $element) = $property->textContent() =~ /"([^"]*)"/;
	my @lines = split /""/, $element;
	my $i = 0;
	
	print $fn "\t\t" . $name;
	foreach my $line (@lines)
	{
		my @sep = split /,/,$line;

		for(my $i = 0; $i < scalar @sep; $i++)
		{
			if($i == (scalar @sep - 1))
			{
				print $fn $sep[$i] . ">;\n";
			}
			else
			{
				print $fn $sep[$i] . ">,<&";
			}
		}		
	}
}
sub printNames
{	
	my $fn = shift;
	my $property = shift;
	my $name = shift;
	(my $element) = $property->textContent() =~ /"([^"]*)"/;
	my @lines = split /""/, $element;
	my $i = 0;
	
	print $fn "\t\t" . $name;
	foreach my $line (@lines)
	{
		my @sep = split /,/,$line;

		for(my $i = 0; $i < scalar @sep; $i++)
		{
#			(my $element) = $property->textContent() =~ /"([^"]*)"/;
#			$element =~ s/,//g;
#			$element =~ s/0x//g;
			if($i == (scalar @sep - 1))
			{
				print $fn $sep[$i] . "\";\n";
			}
			else
			{
				print $fn $sep[$i] . "\",\"";
			}
		}		
	}
}

sub printPinMux
{	
	my $fn = shift;
	my $property = shift;
	my $name = shift;
	(my $element) = $property->textContent() =~ /"([^"]*)"/;
	my @lines = split /""/, $element;
	my $i = 0;
	
	print $fn "\t\t" . $name;
	foreach my $line (@lines)
	{
		my @sep = split /,/,$line;

		for(my $i = 0; $i < scalar @sep; $i++)
		{
			if($i == (scalar @sep - 1))
			{
				print $fn $sep[$i] . ">;\n";
			}
			else
			{
				print $fn $sep[$i] . " &";
			}
		}		
	}
}
