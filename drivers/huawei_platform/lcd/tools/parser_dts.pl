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

	open (my $PANELDTSI, '>hw-panel-' . $name . '.dtsi') or die $!;

	for my $property($xmldoc->findnodes('/GCDB/PanelH'))
	{
		$nameinH = $property->textContent();
	}
	
	printdtsheader($PANELDTSI, $nameinH);

	for my $property($xmldoc->findnodes('/GCDB/PanelEntry/PanelCompatible'))
	{
		print $PANELDTSI "\t\tcompatible = "
				. $property->textContent() . ";\n";
	}
	for my $property($xmldoc->findnodes('/GCDB/PanelEntry/PanelName'))
	{
		print $PANELDTSI "\t\thisilicon,dss-panel-name = "
				. $property->textContent() . ";\n";
	}

	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{
		my @attrs = ("PanelXres", "PanelYres",
		"PanelWidth", "PanelHeight", "PanelOrientation",
		"PanelBpp", "PanelBgrfmt", "PanelBlType",
		"PanelBlmin", "PanelBlmax", "PanelBlDef", "PanelType",
		"PanelIfbcType", "PanelLcdType", "PanelBlPwmPreciType",
		"PanelFrcEnable", "PanelEsdEnable",
		"PanelLcdAjustSupport", "PanelPxlClk", "PanelPxlClkDiv",
		"PanelDirtUpdtSupport", "PanelDsiUptSupport", "PanelVsynCtrType",
		"PanelStepSupport", "PanelEsdSkipMipiCheck");

		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $val = $_;
			$val =~ s/DSI//g;
			$val = convertLower($val);

			printArray($PANELDTSI, \@tmp, $property,
				"hisilicon,dss-" . $val);
			
		}
		
		@attrs = ("LdiHBackPorch", "LdiHFrontPorch",
		"LdiHPulseWidth", "LdiVBackPorch",
		"LdiVFrontPorch", "LdiVPulseWidth", "LdiHsyncPlr",
		"LdiVsyncPlr", "LdiPixelClkPlr", "LdiDataEnPlr", 
		"LdiDpiAOverlapSize", "LdiDpiBOverlapSize");

		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $val = $_;
			$val =~ s/DSI//g;
			$val = convertLower($val);
			
			printArray($PANELDTSI, \@tmp, $property,
				"hisilicon,dss-" . $val);
			
		}			

		@attrs = ("SblStrenLimit", "SblCalA",
		"SblCalB", "SblCalC", "SblCalD",
		"SblTfCtl", "SblBlmin", "SblBlmax",
		"SblBlScale", "SblAmLightMin", "SblFilterA",
		"SblFilterB", "SblLogoLeft", "SblLogoTop",
		"SblVarianceIntensitySpace", "SblSlopeMax", "SblSlopeMin");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $val = $_;
			$val =~ s/DSI//g;
			$val = convertLower($val);
			
			printArray($PANELDTSI, \@tmp, $property,
				"hisilicon,dss-" . $val);
			
		}
		
		@attrs = ("MipiVc", "MipiLaneNums",
		"MipiColorMode", "MipiDsiBitClk", "MipiBurstMode",
		"MipiMaxEscClk", "MipiDsiBitClkValA", "MipiDsiBitClkValB",
		"MipiDsiBitClkValC", "MipiDsiBitClkValD", "MipiDsiBitClkValE",
		"MipiDsiBitClkUpt", "MipiRgVcmAdjust", "MipiNonContinueEnable",
		"MipiClkPostAdjust");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $val = $_;
			$val =~ s/DSI//g;
			$val = convertLower($val);

			printArray($PANELDTSI, \@tmp, $property,
				"hisilicon,dss-" . $val);
		}

		@attrs = ("DirtLeftAlign", "DirtRightAlign",
		"DirtTopAlign", "DirtBottAlign", "DirtWidthAlign",
		"DirtHeightAlign", "DirtWidthMin", "DirtHeightMin",
		"DirtTopStart", "DirtBottStart");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $val = $_;
			$val =~ s/DSI//g;
			$val = convertLower($val);

			printArray($PANELDTSI, \@tmp, $property,
				"hisilicon,dss-" . $val);
		}

		@attrs = ("IovccOffIsNeedDelay", "IovccOnIsNeedReset",
		"LcdCtrlTpPower", "LockCmdSupport", "ReadPowerStatus");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $val = $_;
			$val =~ s/DSI//g;
			$val = convertLower($val);
			
			printArray($PANELDTSI, \@tmp, $property,
				$val);
			
		}

		@attrs = ("ColorTempSupport",
		"PrefixCeSupport", "PrefixSharpOneDSupport", "PrefixSharpTwoDSupport",
		"SharpnessSupport", "SblSupport", "GammaSupport", "GmpSupport", "XccSupport");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $val = $_;
			$val =~ s/DSI//g;
			$val = convertLower($val);
			
			printArray($PANELDTSI, \@tmp, $property,
				"hisilicon,dss-" . $val);
		}
	}

	for my $property($xmldoc->findnodes('/GCDB/PanelEntry/acm'))
	{
		my @attrs = ("AcmSupport", "AcmCeSupport", "AcmValidNum");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $val = $_;
			$val =~ s/DSI//g;
			$val = convertLower($val);
			
			printArray($PANELDTSI, \@tmp, $property,
				"hisilicon,dss-" . $val);
		}
		
	}

	for my $tmpProperty ($xmldoc->findnodes('/GCDB/PanelEntry/acm'))
	{
		printeffectacm($PANELDTSI, $tmpProperty,"hisilicon,dss-acm-");
		print $PANELDTSI "\n";
	}

	for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/OnCommand'))
	{
		printHexArray($PANELDTSI, $property, "hisilicon,dss-on-cmds");
	}
	for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/OffCommand'))
	{
		printHexArray($PANELDTSI, $property, "hisilicon,dss-off-cmds");
	}

	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{
		my @attrs = ("HSyncPulse",);

		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $lower = $_;
			$lower =~ s/DSI//g;
			$lower = convertLower($lower);
			printArray($PANELDTSI, \@tmp, $property,
						"hisilicon,dss-" . $lower);
		}
		for my $property($xmldoc->findnodes('/GCDB/PanelEntry/TrafficMode'))
		{
			print $PANELDTSI "\t\thisilicon,dss-traffic-mode = "
					. $property->textContent() . ";\n";
		}
		for my $property($xmldoc->findnodes('/GCDB/PanelEntry/DSILaneMap'))
		{
			print $PANELDTSI "\t\thisilicon,dss-lane-map = "
					. $property->textContent() . ";\n";
		}

		@attrs = ("BLLPEOFPowerMode");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printBoolean($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-bllp-eof-power-mode");
		}

		@attrs = ("BLLPPowerMode");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printBoolean($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-bllp-power-mode");
		}

		@attrs = ("PanelBroadcastMode", "HFPPowerMode", "HBPPowerMode",
		"HSAPowerMode",
		"Lane0State", "Lane1State", "Lane2State", "Lane3State");

		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $lower = $_;
			$lower =~ s/DSI//g;
			if(index($_, "PowerMode") != -1)
			{
				substr($lower, 0, index($_, "PowerMode")) = lc(substr($lower, 0, index($_, "PowerMode")));
			}
			elsif(index($lower, "Lane") != -1)
			{
				$lower = substr($lower, 0, 4) . "-" . substr($lower, 4, 1) . "-" . substr($lower, 5, 5);
				$lower = lc($lower);
			}
			else
			{
				$lower = convertLower($lower);
			}
			printBoolean($PANELDTSI, \@tmp, $property,
				"hisilicon,dss-" . $lower);
		}
	}

	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{
		my @attrs = ("TECheckEnable", "TEPinSelect", "TEUsingTEPin",
		"AutoRefreshEnable", "AutoRefreshFrameNumDiv",
		"TEvSyncRdPtrIrqLine", "TEvSyncContinuesLines",
		"TEvSyncStartLineDivisor", "TEPercentVariance", "TEDCSCommand",
		"DisableEoTAfterHSXfer", "CmdModeIdleTime");


		@attrs = ("TEPinSelect", "AutoRefreshEnable", "AutoRefreshFrameNumDiv",
		"TEvSyncRdPtrIrqLine", "TEvSyncContinuesLines",
		"TEvSyncStartLineDivisor", "TEPercentVariance", "TEDCSCommand",
		"DisableEoTAfterHSXfer", "CmdModeIdleTime");

		foreach(@attrs)
		{
			push(my @tmp, $_);
			if($_ eq "TEPinSelect")
			{
				printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-te-pin-select");
			}
			elsif($_ eq "TEvSyncRdPtrIrqLine")
			{
				printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-te-v-sync-rd-ptr-irq-line");
			}
			elsif($_ eq "TEvSyncContinuesLines")
			{
				printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-te-v-sync-continues-lines");
			}
			elsif($_ eq "TEvSyncStartLineDivisor")
			{
				printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-te-v-sync-start-line-divisor");
			}
			elsif($_ eq "TEPercentVariance")
			{
				printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-te-percent-variance");
			}
			elsif($_ eq "TEDCSCommand")
			{
				printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-te-dcs-command");
			}
			else
			{
				printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-" . convertLower($_));
			}
		}

		@attrs = ("TECheckEnable", "TEUsingTEPin");
		foreach(@attrs)
		{
			if($_ eq "TECheckEnable")
			{
				push(my @tmp, $_);
				printBoolean($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-te-check-enable");
			}
			elsif($_ eq "TEUsingTEPin")
			{
				push(my @tmp, $_);
				printBoolean($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-te-using-te-pin");
			}
		}

	}

	for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/EsdReg'))
	{
		printHexArray($PANELDTSI, $property,
						"hisilicon,dss-esd-reg");
	}
	
	for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/EsdValue'))
	{
		printHexArray($PANELDTSI, $property,
						"hisilicon,dss-esd-value");
	}	
	
	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{
		my @attrs = ("EsdSetBl", "EsdBlEn", "VspVsnPoweronSimu");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $lower = $_;
			$lower = convertLower($lower);
			printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-" . $lower);
		}	
	}
	
	for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/EsdBlUiComand'))
	{
		printHexArray($PANELDTSI, $property, "hisilicon,panel-esd-bl-ui-cmds");
	}	

	for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/EsdBlVidComand'))
	{
		printHexArray($PANELDTSI, $property, "hisilicon,panel-esd-bl-vid-cmds");
	}	
	
	for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/MipiCheckReg'))
	{
		printHexArray($PANELDTSI, $property,
						"hisilicon,dss-mipi-check-reg");
	}
	
	for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/MipiCheckValue'))
	{
		printHexArray($PANELDTSI, $property,
						"hisilicon,dss-mipi-check-value");
	}	
	
	for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/PanelRotation'))
	{
		printHexArray($PANELDTSI, $property,
						"hisilicon,dss-panelrotation");
	}

	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{
		my @attrs = ("TClkPost", "TClkPre");

		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $lower = $_;
			$lower =~ s/DSI//g;
			$lower = convertLower($lower);
			printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-" . $lower);
		}

		@attrs = ("BLMinLevel");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-bl-min-level");
		}
		@attrs = ("BLMaxLevel");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-bl-max-level");
		}
		@attrs = ("BLPMICPWMFrequency");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-bl-pmic-pwm-frequency");
		}
		@attrs = ("BLPMICBankSelect");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-bl-pmic-bank-select");
		}
		for my $property($xmldoc->findnodes('/GCDB/PanelEntry/DSIDMATrigger'))
		{
		print $PANELDTSI "\t\thisilicon,dss-dma-trigger = "
				. $property->textContent() . ";\n";
		}
		for my $property($xmldoc->findnodes('/GCDB/PanelEntry/DSIMDPTrigger'))
		{
		print $PANELDTSI "\t\thisilicon,dss-mdp-trigger = "
				. $property->textContent() . ";\n";
		}

		@attrs = ("BLPMICControlType");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printControlType($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-bl-pmic-control-type");
		}
		@attrs = ("PanPhysicalWidthDimension",
			"PanPhysicalHeightDimension");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $lower = $_;
			$lower = convertLower($lower);
			printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-" . $lower);
		}

		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/InversionModeOff'))
		{
			printHexArray($PANELDTSI, $property, "hisilicon,dss-mipi-tr-off");
		}
		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/InversionModeOn'))
		{
			printHexArray($PANELDTSI, $property, "hisilicon,dss-mipi-tr-on");
		}
		
		my @commandAttrsInversion = ("InverseOnCmdsDsiState", "InverseOffCmdsDsiState");

		foreach(@commandAttrsInversion)
		{
			push(my @tmp, $_);
			my $lower = convertLower($_);
			printCommandState($PANELDTSI, \@tmp, $property,
						"hisilicon," . $lower);
		}

		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/SetTemporaryPwmCommand'))
		{
			printHexArray($PANELDTSI, $property, "hisilicon,panel-SetTemporary-pwm-cmds");
		}
		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/SetNormalPwmCommand'))
		{
			printHexArray($PANELDTSI, $property, "hisilicon,panel-SetNormal-pwm-cmds");
		}
		
		my @commandAttrsSetPwm = ("TemporaryPwmCommandDsiState", "NormalPwmCommandDsiState");

		foreach(@commandAttrsSetPwm)
		{
			push(my @tmp, $_);
			my $lower = convertLower($_);
			printCommandState($PANELDTSI, \@tmp, $property,
						"hisilicon," . $lower);
		}	
		
		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/CabcOffMode'))
		{
			printHexArray($PANELDTSI, $property, "hisilicon,dss-cabc-off-mode");
		}

		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/CabcUiMode'))
		{
			printHexArray($PANELDTSI, $property, "hisilicon,dss-cabc-ui-mode");
		}

		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/CabcStillMode'))
		{
			printHexArray($PANELDTSI, $property, "hisilicon,dss-cabc-still-mode");
		}

		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/CabcMovingMode'))
		{
			printHexArray($PANELDTSI, $property, "hisilicon,dss-cabc-moving-mode");
		}

		#//add column/dot inversion cmds
		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/DotInversionCommand'))
		{
			printHexArray($PANELDTSI, $property, "hisilicon,dss-dot-inversion");
		}
		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/ColumnInversionCommand'))
		{
			printHexArray($PANELDTSI, $property, "hisilicon,dss-column-inversion");
		}
		my @InversionModecommandAttrs = ("DotInversionCmdsDsiState", "ColumnInversionCmdsDsiState");

		foreach(@InversionModecommandAttrs)
		{
			push(my @tmp, $_);
			my $lower = convertLower($_);
			printCommandState($PANELDTSI, \@tmp, $property,
						"hisilicon," . $lower);
		}
		#//add forword/revert scan cmds
		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/ForwordScanCommand'))
		{
			printHexArray($PANELDTSI, $property, "hisilicon,dss-forword-scan");
		}
		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/RevertScanCommand'))
		{
			printHexArray($PANELDTSI, $property, "hisilicon,dss-revert-scan");
		}
		my @ScanModecommandAttrs = ("ForwordScanCmdsDsiState", "RevertScanCmdsDsiState");

		foreach(@ScanModecommandAttrs)
		{
			push(my @tmp, $_);
			my $lower = convertLower($_);
			printCommandState($PANELDTSI, \@tmp, $property,
						"hisilicon," . $lower);
		}

		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/EsdReadCommand'))
		{
			print $PANELDTSI "\t\thisilicon,panel-esd-check-enabled;\n";
			printHexArray($PANELDTSI, $property, "hisilicon,panel-esd-read-commands");
		}

		# /* add init LP11 flag */
		@attrs = ("Lp11InitFlag");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printBoolean($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-lp11-init");
		}

		#/* add panel physical size to calculate dpi */
		@attrs = ("PanelPhysicalWidth");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-pan-physical-width-dimension");
		}
		@attrs = ("PanelPhysicalHeight");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-pan-physical-height-dimension");
		}

		#/* add delay time for panel after reset */
		@attrs = ("PanelInitDelay");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-init-delay-us");
		}

		#/* print delay time before bkl */
		@attrs = ("DelaytimeBeforeBL");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printArray($PANELDTSI, \@tmp, $property,
					"huawei,delaytime-before-bl");
		}
		
		@attrs = ("BiasIcEnable");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $lower = convertLower($_);
			printBoolean($PANELDTSI, \@tmp, $property,
					"huawei,bias-ic-enable");
		}

		@attrs = ("SkipRegReadFlag");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printArray($PANELDTSI, \@tmp, $property,
					"huawei,skip-reg-read-flag");
		}

		@attrs = ("RegLongRead");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printArray($PANELDTSI, \@tmp, $property,
					"huawei,long-read-flag");
		}
		@attrs = ("RegReadExpectValue");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printArray($PANELDTSI, \@tmp, $property,
					"huawei,reg-read-expect-value");
		}
		@attrs = ("RegLongReadCount");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			printArray($PANELDTSI, \@tmp, $property,
					"huawei,reg-long-read-count");
		}

		my @attr = ("FBCbpp", "FBCPacking",
		"FBCBias",
		"FBCHLineBudget", "FBCBlockBudget",
		"FBCLosslessThreshold", "FBCLossyThreshold", "FBCRGBThreshold",
		"FBCLossyModeIdx");

		foreach(@attr)
		{
			push(my @tmp, $_);
			my $lower = convertLower($_);
			printArray($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-" . $lower);
		}

		@attr = ("FBCEnable", "FBCQuantError", "FBCPATMode", "FBCVLCMode",
		"FBCBFLCMode");
		foreach(@attr)
		{
			push(my @tmp, $_);
			my $lower = convertLower($_);
			printBoolean($PANELDTSI, \@tmp, $property,
					"hisilicon,dss-" . $lower);
		}
		for my $tmpProperty ($xmldoc->findnodes('/GCDB/PanelEntry/ResetSequence'))
		{
			printResetSeq($PANELDTSI, $tmpProperty,"hisilicon,dss-reset-sequence");
			print $PANELDTSI "\n";
		}
	}
	
	for my $property($xmldoc->findnodes('/GCDB/PanelEntry'))
	{
		my @attrs = ("AdePixClk", "AdeCoreClk",
		"MedNocClk", "DsiBitclk");
	
		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $val = $_;
#			$val =~ s/DSI//g;
			$val = convertLower($val);
	
			printArray($PANELDTSI, \@tmp, $property,
				"hisilicon,dss-" . $val);

		}
	
		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/ClockName'))
		{
			printClocks($PANELDTSI, $property, "clocks = <&");
		}
		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/ClockName'))
		{
			printNames($PANELDTSI, $property, "clock-names = \"");
		}		
		
		@attrs = ("LcdIdA", "LcdRst", "LcdTe", "LcdIdB");
		print $PANELDTSI "\t\t" . "gpios" . " = ";
		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $val = $_;
			$val =~ s/DSI//g;
			$val = convertLowerPlus($val);
			if($_ eq "Status")
			{
				printArray($PANELDTSI, \@tmp, $property,
					"Status");
			}
			elsif($_ eq "LcdIdB")
			{
				printArrayChar($PANELDTSI, \@tmp, $property,
					$val);
				print $PANELDTSI ";\n";
			}
			else
			{
				printArrayChar($PANELDTSI, \@tmp, $property,
					$val);
				print $PANELDTSI ", ";
			}
		}

		@attrs = ("GpioNums", "LcdanalogVcc", "LcdioVcc",
					"LcdBias", "LcdVsp", "LcdVsn",
					"LcdRstFirstHigh", "LcdRstLow", "LcdRstSecondHight");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $val = $_;
			$val =~ s/DSI//g;
			$val = convertLower($val);
			
			printArray($PANELDTSI, \@tmp, $property,
				$val);
		}

		@attrs = ("LcdIOVcc", "LcdANVcc", "LcdBlSupply", "LcdBiasSupply", "LcdVspSupply", "LcdVsnSupply");
		foreach(@attrs)
		{
			push(my @tmp, $_);
			my $val = $_;
			$val =~ s/DSI//g;
			$val = convertLowerPlus($val);
			if($_ eq "LcdIOVcc")
			{
				print $PANELDTSI "\t\t" . "lcdio-vcc-supply = ";
				printArrayChar($PANELDTSI, \@tmp, $property,
					$val);
				print $PANELDTSI ";\n";			
			}
			elsif($_ eq "LcdANVcc")
			{
				print $PANELDTSI "\t\t" . "lcdanalog-vcc-supply = ";
				printArrayChar($PANELDTSI, \@tmp, $property,
					$val);
				print $PANELDTSI ";\n";			
			}
			elsif($_ eq "LcdBlSupply")
			{
				print $PANELDTSI "\t\t" . "lcd_backlight-supply = ";
				printArrayChar($PANELDTSI, \@tmp, $property,
					$val);
				print $PANELDTSI ";\n";			
			}
			elsif($_ eq "LcdBiasSupply")
			{
				print $PANELDTSI "\t\t" . "vcc_lcdbias-supply = ";
				printArrayChar($PANELDTSI, \@tmp, $property,
					$val);
				print $PANELDTSI ";\n";			
			}
			elsif($_ eq "LcdVspSupply")
			{
				print $PANELDTSI "\t\t" . "lcd_vsp-supply = ";
				printArrayChar($PANELDTSI, \@tmp, $property,
					$val);
				print $PANELDTSI ";\n";			
			}
			elsif($_ eq "LcdVsnSupply")
			{
				print $PANELDTSI "\t\t" . "lcd_vsn-supply = ";
				printArrayChar($PANELDTSI, \@tmp, $property,
					$val);
				print $PANELDTSI ";\n";			
			}			
		}
		
		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/LcdPinNames'))
		{
			printNames($PANELDTSI, $property, "pinctrl-names = \"");
		}		
		
		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/LcdPinMuxA'))
		{
			printPinMux($PANELDTSI, $property, "pinctrl-0 = <&");
		}	
		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/LcdPinMuxB'))
		{
			printPinMux($PANELDTSI, $property, "pinctrl-1 = <&");
		}
		for my $property ($xmldoc->findnodes('/GCDB/PanelEntry/Status'))
		{
			printNames($PANELDTSI, $property, "status = \"");
		}		
	}
	print $PANELDTSI "\t};\n};\n";
	close ($PANELDTSI);
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
			$cmdtype =~ s/ //g;
			$cmdtype =~ s/\t//g;

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
			
			if($i >= (scalar(@lines) - 2))
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
			if($_ eq "PanelLcdType")
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
	print $fh "\tdss_" . lc($name) . ":" . lc($name) . " {\n";
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

sub printeffectacm
{
	my $fh = shift;
	my $property = shift;
	my $name = shift;
	my $first = 1;
	for (my $i = 0; $i <7; $i++)
	{
		print $fh "\t\t" . $name . "r_hh" . $i . " = <";
		for my $element ($property->findnodes("./r_hh" . $i))
		{
			print $fh $element->textContent();
			print $fh ">;\n";
		}
		
		print $fh "\t\t" . $name . "r_lh" . $i . " = <";
		for my $element ($property->findnodes("./r_lh" . $i))
		{
			print $fh $element->textContent();
			print $fh ">;\n";
		}
	}
}
