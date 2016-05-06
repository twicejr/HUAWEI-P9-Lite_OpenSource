#!/usr/bin/perl -w
#use packages
use FindBin qw($Bin);
use lib "$Bin/lib";
use lib "$Bin/share";
use XML::LibXML;
use IO::Handle;
use warnings;
use strict;
use File::Spec;
use File::Basename;

# initialize the parser
my $parser = new XML::LibXML;

# open a filehandle and parse
my $fh = new IO::Handle;

my $name = "";
my $nameinH = "";
my $productN = "";
my @Headers;
my @DTSI;
my @LCDEnum;
my @LCDMap;

my @EFFECTHeaders;
my @EFFECT;
my @EFFECTEnum;
my @EFFECTMap;
my @EFFECLcdname;

my $fail_error_hdr = "make[0]: *** FATAL ERROR: ";

my $print_default_dtsi = 0;
my $kernel_default_dtsi = "default_lcd.dtsi";
my $kernel_lcd_dtsi = "huawei-lcd.dtsi";
my $kernel_dts_folder = $ARGV[0] . "/" . $ARGV[1];
my $panel_xml_file = "../panel";


#Execution start time
my $start_time = time;

# get the abs path for tools folder so that we can copy the 
# files with the relative path, the tool will execute in this
# folder
my $abs_path = File::Spec->rel2abs($0);
$abs_path = dirname($abs_path);
chdir $abs_path;

#get list of all xml files
my @files = glob("$panel_xml_file/*.xml");

foreach my $file (@files) {
	my $xmldoc = $parser->parse_file($file);
	for my $property($xmldoc->findnodes('/GCDB/ProductList/Product/Name')) {
		$productN = $property->textContent();
	}

	mkdir $kernel_dts_folder . "/" . $productN;
}
create_dtsi_hdr();

foreach my $file (@files) {
	print "parsing $file\n";
	system("./localperl/bin/perl parser_dts.pl ".$file." panel");

	if ($?) {
		die "$fail_error_hdr Failed to parse file: $file!\n";
	}

	my $xmldoc = $parser->parse_file($file);

	for my $property($xmldoc->findnodes('/GCDB/PanelId')) {
		$name = $property->textContent();
	}

	my $dtsi = "hw-panel-".$name.".dtsi";
	#print $dtsi."\n";

	#save vars to process it later
	push(@DTSI, $dtsi);
	
	for my $dest($xmldoc->findnodes('/GCDB/ProductList/Product')) {
		my $productname = "None";
		my $boardid = 0xFFFF;
		my $gpioid = 0xFF;

		for my $prop($dest->findnodes('./Name')) {
			$productname = $prop->textContent();
		}
		
		for my $prop($dest->findnodes('./BoardID')) {
			$boardid = $prop->textContent();
		}

		for my $prop($dest->findnodes('./GpioID')) {
			$gpioid = $prop->textContent();
		}

		#include dtsi to the huawei-lcd.dtsi
		include_module_dtsis($dtsi, $productname);
	}
}

#@temp = glob "*.h";
#for (@temp) {
#	unlink $_;
#}

my @temp = glob "*.dtsi";
for (@temp) {
	unlink $_;
}

remove_dtsi_hdr();

exit 0;

# this will include the default panel for dts
sub print_dtsi_hdr_templ
{
	my $fh = shift;
	if ($print_default_dtsi) {
		print $fh "\n#include \"$kernel_default_dtsi\"\n\n";
	}
}

sub remove_dtsi_hdr
{
	my $dir = "$kernel_dts_folder";

	opendir(DIR, $dir) or die $!;

	while (my $cur_dir = readdir(DIR)) {
		next unless (-d "$dir/$cur_dir");
		next unless ($cur_dir =~ m/^huawei/);
		my $hdr_file_path = "$dir/$cur_dir/$kernel_lcd_dtsi";

		open( FILE, "<$hdr_file_path" );
		my @LINES = <FILE>;
		close( FILE );
		open( FILE, ">$hdr_file_path" );
		foreach my $LINE ( @LINES ) {
			print FILE $LINE unless ( $LINE =~ m/\#include \"no-lcd-found.dtsi\"/);
		}
		close( FILE );
	}

	closedir(DIR);
}

sub create_dtsi_hdr
{
	my $dir = "$kernel_dts_folder";

	opendir(DIR, $dir) or die $!;
	while (my $cur_dir = readdir(DIR)) {
		next unless (-d "$dir/$cur_dir");
		next unless ($cur_dir =~ m/^huawei/);
		my @temp = glob("$dir/$cur_dir/hw-panel-*.dtsi");
		for (@temp) {
			unlink $_;
		}

		#truncate and recreate the lcd dtsi
		open(my $fDTSI_include, ">", "$dir/$cur_dir/$kernel_lcd_dtsi") 
			or die "$fail_error_hdr cannot open > $dir/$cur_dir/$kernel_lcd_dtsi: $!";

		printheader($fDTSI_include);
		print $fDTSI_include "\n#include \"no-lcd-found.dtsi\"\n";
		print_dtsi_hdr_templ($fDTSI_include);

		close($fDTSI_include);
	}

	closedir(DIR);
}

#Function to truncate and recreate the dtsi file if not recent
sub recreate_dtsi_hdr
{
	my $dtsi_file = shift;
	#open dtsi file for stat 
	open(my $sfh, "<", "$dtsi_file") or die "$fail_error_hdr cannot open < $dtsi_file: $!";

	my $last_modified = (stat($sfh))[9];

	close ($sfh);

	#print "$last_modified $start_time\n";
	if ($last_modified >= $start_time) {
		#print "No need to recreate the file. just append \n";
		return;
	}

	#truncate and recreate the file
	open(my $fDTSI_include, ">", "$dtsi_file") or die "$fail_error_hdr cannot open > $dtsi_file: $!";

	printheader($fDTSI_include);
	print $fDTSI_include "\n#include \"no-lcd-found.dtsi\"\n";
	print_dtsi_hdr_templ($fDTSI_include);

	close($fDTSI_include);
}

sub include_module_dtsis
{
	my $dtsi_file = shift;
	my $fdr = shift;
	my $hdr_file_path="$kernel_dts_folder/$fdr/$kernel_lcd_dtsi";

	my $line = ();
	my @lines = ();

	#truncate the file if required.
	recreate_dtsi_hdr($hdr_file_path);

	#Read the content of file into an array.
	open (HDR_FILE, "<$hdr_file_path") or die "$fail_error_hdr Could not open file '$hdr_file_path' $!";
	@lines=<HDR_FILE>;
	close (HDR_FILE);

	# Check if the panel is already included
	foreach $line(@lines) {
		if ($line =~ /\/include\/ \"$dtsi_file\"/) {
			#print ("\nFound the entry, continuing with next entry..\n");
			return;
		}
	}

	open (HDR_FILE, ">$hdr_file_path") or die "$fail_error_hdr Could not open file '$hdr_file_path' $!";
	if ($print_default_dtsi) {
	#scan through the file and include the panel dtsi
	foreach $line(@lines) {
		#print $line."\n";
		if ($line =~ /\/include\/ "$kernel_default_dtsi"/) {
			$line =~ s/\/include\/ "$kernel_default_dtsi"/\/include\/ \"$dtsi_file\"\n\/include\/ "$kernel_default_dtsi"/gi;
			#print ("\nIncluding dtsi file..\n");
		}
		print HDR_FILE @lines;
		}
	} else {
		push(@lines, "\/include\/ \"$dtsi_file\"\n");
		print HDR_FILE @lines;
	}
	close (HDR_FILE);

	system("cp ".$dtsi_file." $kernel_dts_folder/$fdr/".$dtsi_file);
}

sub printheader
{
	my $fh = shift;
	print $fh "/*---------------------------------------------------------------------------\n";
	print $fh " * This file is autogenerated file using huawei LCD parser. Please do not edit it.\n";
	print $fh " * Update input XML file to add a new entry or update variable in this file\n";
	print $fh " * Parser location: device/hisilicon/common/display/tools/huawei_lcd_panel \n";
	print $fh " *---------------------------------------------------------------------------*/\n\n";
}

sub printlcdenum
{
	my $fh = shift;
	my $list = shift;
	my $lcdenum;
	print $fh "\n/*---------------------------------------------------------------------------*/\n";
	print $fh "/* static panel selection variable                                           */\n";
	print $fh "/*---------------------------------------------------------------------------*/\n";
	print $fh "enum {\n";

	foreach $lcdenum (@$list) {
		print $fh $lcdenum."_PANEL,\n";
	}

#	print $fh $lk_default_panel."_PANEL,\n";
	print $fh "};\n\n";
}

sub printlcdeffectenum
{
	my $fh = shift;
	my $list = shift;
	my $lcdenum;
	print $fh "\n/*---------------------------------------------------------------------------*/\n";
	print $fh "/* static lcd effect selection variable                                           */\n";
	print $fh "/*---------------------------------------------------------------------------*/\n";
	print $fh "enum {\n";

	foreach $lcdenum (@$list) {
		print $fh $lcdenum."_PANEL,\n";
	}

#	print $fh $lk_default_panel."_PANEL,\n";
	print $fh "};\n\n";
}

sub printstructure
{
	my $fh = shift;
	my $list = shift;
	my $lcdmap;
	print $fh "\n/*---------------------------------------------------------------------------*/\n";
	print $fh "/* static panel board mapping variable                                           */\n";
	print $fh "/*---------------------------------------------------------------------------*/\n";
	print $fh "struct hw_lcd_board_map {\n";
	print $fh "\tuint8_t lcd_id;\n";
	print $fh "\tuint8_t gpio_id;\n";
	print $fh "\tuint16_t board_id;\n";
	print $fh "};\n\n";

	print $fh "static struct hw_lcd_board_map lcd_map[] = {\n";

	foreach $lcdmap (@$list) {
		print $fh "\t{".$lcdmap."},\n";
	}

	print $fh "};\n\n";
}

sub printeffectstructure
{
	my $fh = shift;
	my $list = shift;
	my $lcdmap;
	print $fh "\n/*---------------------------------------------------------------------------*/\n";
	print $fh "/* static lcd effect mapping variable                                           */\n";
	print $fh "/*---------------------------------------------------------------------------*/\n";
	print $fh "struct hw_lcd_effect_map {\n";
	print $fh "\tu32 lcd_id;\n";
	print $fh "\tchar* panel_name;\n";
	print $fh "};\n\n";

	print $fh "static struct hw_lcd_effect_map lcd_effect_map[] = {\n";

	foreach $lcdmap (@$list) {
		print $fh "\t{".$lcdmap."},\n";
	}

	print $fh "};\n\n";
}

sub printlcdselectionfunc
{
	my $fh = shift;
	my $enum = shift;
	my $i;

	print $fh "static bool hw_init_panel_data(struct panel_data *paneldata,\n";
	print $fh "			struct dsi_panel_cmd *on_cmds,\n";
	print $fh "			struct dsi_panel_cmd *off_cmds,\n";
	print $fh "			uint8_t panel_id)\n";
	print $fh "{\n";
	print $fh "\tswitch (panel_id) {\n";

	for $i ( 0 ..  scalar(@$enum)-1 ) {
		print $fh "\tcase ".@$enum[$i]."_PANEL:\n";
		printlcdconfig($fh, @$enum[$i]);
	}

#	print $fh "\tcase ".$lk_default_panel."_PANEL:\n";
#	printlcdconfig($fh, $lk_default_panel);

	print $fh "\tdefault:\n";
	print $fh "\t\t".'PRINT_INFO("Panel ID not detected %d\n", panel_id);'."\n";
	print $fh "\t\treturn FALSE;\n";
	print $fh "\t}\n\n";
	print $fh "\treturn TRUE;\n";
	print $fh "}\n\n";
}

sub printlcdeffectselectfunc
{
	my $fh = shift;
	my $enum = shift;
	my $i;

	print $fh "static void hw_lcd_effect_get_data(u32 panel_id, struct hisi_panel_info* pinfo)\n";
	print $fh "{\n";
	print $fh "\tswitch (panel_id) {\n";

	for $i ( 0 ..  scalar(@$enum)-1 ) {
		print $fh "\tcase ".@$enum[$i]."_PANEL:\n";
		printlcdeffectconfig($fh, @$enum[$i]);
	}

#	print $fh "\tcase ".$lk_default_panel."_PANEL:\n";
#	printlcdconfig($fh, $lk_default_panel);

	print $fh "\tdefault:\n";
	print $fh "\t\t".'HISI_FB_INFO("Panel ID not detected %d\n", panel_id);'."\n";
	print $fh "\t\tbreak;\n";
	print $fh "\t}\n";
	print $fh "}\n\n";
}

sub printlcdconfig
{
	my $fh = shift;
	my $name = shift;
	print $fh "\t\tpaneldata->panel     = &".lc($name)."_panel_info;\n";
	print $fh "\t\tpaneldata->ldi        = &".lc($name)."_ldi_panel_info;\n";
	print $fh "\t\tpaneldata->smart_bl   = &".lc($name)."_sbl_panel_info;\n";
	print $fh "\t\tpaneldata->mipi = &".lc($name)."_mipi_panel_info;\n";
#	print $fh "\t\tpaneldata->dirty_region_info = &".lc($name)."_dirty_region_info;\n";
#	print $fh "\t\tpanelstruct->state        = &".lc($name)."_state;\n";
#	print $fh "\t\tpanelstruct->laneconfig   = &".lc($name)."_lane_config;\n";
#	print $fh "\t\tpanelstruct->paneltiminginfo	= &".lc($name)."_timing_info;\n";
#	print $fh "\t\tpanelstruct->panelresetseq = &".lc($name)."_reset_seq;\n";
#	print $fh "\t\tpanelstruct->backlight = &".lc($name)."_backlight;\n";
	print $fh "\t\ton_cmds->panel_cmds	 = ".lc($name)."_on_cmds;\n";
	print $fh "\t\ton_cmds->cmd_cnt = ARRAY_SIZE(".lc($name)."_on_cmds);\n";
	print $fh "\t\toff_cmds->panel_cmds	 = ".lc($name)."_off_cmds;\n";
	print $fh "\t\toff_cmds->cmd_cnt = ARRAY_SIZE(".lc($name)."_off_cmds);\n";
#	print $fh "\t\tmemcpy(phy_db->timing, ".lc($name)."_timings, TIMING_SIZE);\n";
	print $fh "\t\tbreak;\n\n"
}

sub printlcdeffectconfig
{
	my $fh = shift;
	my $name = shift;
	print $fh "\t\tif (pinfo->acm_support == 1)\n";
	print $fh "\t\t{\n";
	print $fh "\t\t\tpinfo->acm_lut_hue_table = " . lc($name) . "_acm_lut_hue_table;\n";
	print $fh "\t\t\tpinfo->acm_lut_hue_table_len = ARRAY_SIZE(" . lc($name) . "_acm_lut_hue_table);\n";
	print $fh "\t\t\tpinfo->acm_lut_sata_table = " . lc($name) . "_acm_lut_sata_table;\n";
	print $fh "\t\t\tpinfo->acm_lut_sata_table_len = ARRAY_SIZE(" . lc($name) . "_acm_lut_sata_table);\n";
	print $fh "\t\t\tpinfo->acm_lut_satr_table = " . lc($name) . "_acm_lut_satr_table;\n";
	print $fh "\t\t\tpinfo->acm_lut_satr_table_len = ARRAY_SIZE(" . lc($name) . "_acm_lut_satr_table);\n";
	print $fh "\t\t\tpinfo->acm_valid_num = 7;\n";
	print $fh "\t\t\tpinfo->r0_hh = 0x7f;\n";
	print $fh "\t\t\tpinfo->r0_lh = 0x0;\n";
	print $fh "\t\t\tpinfo->r1_hh = 0xff;\n";
	print $fh "\t\t\tpinfo->r1_lh = 0x80;\n";
	print $fh "\t\t\tpinfo->r2_hh = 0x17f;\n";
	print $fh "\t\t\tpinfo->r2_lh = 0x100;\n";
	print $fh "\t\t\tpinfo->r3_hh = 0x1ff;\n";
	print $fh "\t\t\tpinfo->r3_lh = 0x180;\n";
	print $fh "\t\t\tpinfo->r4_hh = 0x27f;\n";
	print $fh "\t\t\tpinfo->r4_lh = 0x200;\n";
	print $fh "\t\t\tpinfo->r5_hh = 0x2ff;\n";
	print $fh "\t\t\tpinfo->r5_lh = 0x280;\n";
	print $fh "\t\t\tpinfo->r6_hh = 0x37f;\n";
	print $fh "\t\t\tpinfo->r6_lh = 0x300;\n";
	print $fh "\t\t\tpinfo->acm_ce_support = 1;\n";
	print $fh "\t\t}\n";
	
	print $fh "\t\tif (pinfo->gamma_support == 1)\n";
	print $fh "\t\t{\n";
	print $fh "\t\t\tpinfo->gamma_lut_table_R = " . lc($name) . "_gamma_lut_table_R;\n";
	print $fh "\t\t\tpinfo->gamma_lut_table_G = " . lc($name) . "_gamma_lut_table_G;\n";
	print $fh "\t\t\tpinfo->gamma_lut_table_B = " . lc($name) . "_gamma_lut_table_B;\n";
	print $fh "\t\t\tpinfo->gamma_lut_table_len = ARRAY_SIZE(" . lc($name) . "_gamma_lut_table_R);\n";
	print $fh "\t\t\tpinfo->igm_lut_table_R = " . lc($name) . "_igm_lut_table_R;\n";
	print $fh "\t\t\tpinfo->igm_lut_table_G = " . lc($name) . "_igm_lut_table_G;\n";
	print $fh "\t\t\tpinfo->igm_lut_table_B = " . lc($name) . "_igm_lut_table_B;\n";
	print $fh "\t\t\tpinfo->igm_lut_table_len = ARRAY_SIZE(" . lc($name) . "_igm_lut_table_R);\n";
	print $fh "\t\t\tpinfo->gmp_support = 1;\n";
	print $fh "\t\t\tpinfo->gmp_lut_table_low32bit = &" . lc($name) . "_gmp_lut_table_low32bit[0][0][0];\n";
	print $fh "\t\t\tpinfo->gmp_lut_table_high4bit = &" . lc($name) . "_gmp_lut_table_high4bit[0][0][0];\n";
	print $fh "\t\t\tpinfo->gmp_lut_table_len = ARRAY_SIZE(" . lc($name) . "_gmp_lut_table_low32bit);\n";
	print $fh "\t\t\tpinfo->xcc_support = 1;\n";
	print $fh "\t\t\tpinfo->xcc_table = " . lc($name) . "_xcc_table;\n";
	print $fh "\t\t\tpinfo->xcc_table_len = ARRAY_SIZE(" . lc($name) . "_xcc_table);\n";
	print $fh "\t\t}\n";
	print $fh "\t\tbreak;\n";
}

#/* add panel id cmdline for lcd */
sub printlcdmapfunc
{
	my $fh = shift;
	my $list = shift;
	my $map;
	my $default_panel_id;
	my $len = 0;
	
	$default_panel_id = pop(@LCDMap);
	$len = length ($default_panel_id);
	$default_panel_id = substr($default_panel_id, 0, ($len - 12));
	print $fh "static uint8_t hw_lcd_panel_init(uint16_t hw_id, uint32_t lcd_id)\n";
	print $fh "{\n";
	print $fh "\tuint8_t lcd_panel_id = " . $default_panel_id . ";" . " /*default panel id is the last one*/\n";
#	print $fh "\tuint8_t lcd_hw_id = 0;\n";
	print $fh "\tint i = 0;\n";
#	print $fh "\tlcd_hw_id = which_lcd_module_triple();\n\n";
	print $fh "\t".'PRINT_INFO("lcd_panel_init lcd id = %d\n", lcd_id);'."\n";
#	print $fh "\t".'snprintf(lcd_id,sizeof(lcd_id), " huawei,lcd_panel_id = %X", lcd_hw_id);'."\n";

	print $fh "\tfor (i = 0; i < ARRAY_SIZE(lcd_map); ++i) {\n";
	print $fh "\t\tif ((lcd_map[i].board_id == hw_id) && (lcd_map[i].gpio_id == lcd_id)) {\n";
	print $fh "\t\t\tlcd_panel_id = lcd_map[i].lcd_id;\n";
	print $fh "\t\t\tbreak;\n";
	print $fh "\t\t}\n";
	print $fh "\t}\n\n";
	
	print $fh "\treturn lcd_panel_id;\n";
	print $fh "}\n\n";

}

sub printlcdeffectmapfunc
{
	my $fh = shift;
	my $list = shift;
	my $map;
	my $default_panel_id;
	my $len = 0;
	
	$default_panel_id = pop(@LCDMap);
	$len = length ($default_panel_id);
	$default_panel_id = substr($default_panel_id, 0, ($len - 12));
	print $fh "static u32 hw_lcd_get_panel_id(void)\n";
	print $fh "{\n";
	print $fh "\tuint8_t lcd_panel_id = " . $default_panel_id . ";" . " /*default panel id is the last one*/\n";
	print $fh "\tint i = 0;\n";

	print $fh "\tfor (i = 0; i < ARRAY_SIZE(lcd_effect_map); ++i) {\n";
	print $fh "\t\tif (strncmp(panel_compatible, lcd_effect_map[i].panel_name, strlen(panel_compatible)))";
	print $fh "{\t\t\n";
	print $fh "\t\t\tlcd_panel_id = lcd_effect_map[i].lcd_id;\n";
	print $fh "\t\t\tbreak;\n";
	print $fh "\t\t}\n";
	print $fh "\t}\n\n";
	
	print $fh "\treturn lcd_panel_id;\n";
	print $fh "}\n";
}


