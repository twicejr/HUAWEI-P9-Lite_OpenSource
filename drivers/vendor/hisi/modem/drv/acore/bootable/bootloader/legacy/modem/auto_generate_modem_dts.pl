#!/usr/bin/perl -w

use Cwd;

sub my_main()
{
    my $current_dir = getcwd();

    opendir(CUR_DIR, $current_dir) || die "current directory not exist";
    my @file_s = readdir(CUR_DIR);
    my $subdir;
    my $product;
    my $auto_generate = '../../../../kernel/arch/arm/boot/dts/auto-generate';
    my $new_file;

    foreach(@file_s)
    {
		my $found = 0;
		#ignore tools/auto-generate/./.. dir
		if(($_ =~ m/tools/)||($_ =~ m/auto-generate/)||($_ =~ m/\./)||($_ =~ m/\.\./)||($_ =~ m/hi3630_dtsi/))
		{
			next;
		}
		#open sub dir
		$subdir = "$current_dir/$_";
		$product = $_;
		$new_file = "${product}_config";
		opendir(SUB_DIR, $subdir) || next;
		@file_sub = readdir(SUB_DIR);
		foreach(@file_sub)
		{
			#
			# first: 	copy config.dts to kernel/arch/arm/boot/dts/auto-generate/$pruduct_config.dts
			# second: 	call parse_board_dts_inherit.pl to implement inherit mechanism
			# third:	copy father config.dts as dtsi (in order to delete /dts-v1/, or will be compile error), then delete dts version info(/dts-v1)
			#
			if($_ =~ m/config\.dts$/)
			{
				$found = 1;
				system("sed -i \"s\/hisi_3630_modem.dtsi\/hisi_3630_modem_${product}.dtsi\/g\" ${auto_generate}/${new_file}.dts");
				system("sed -i \"s\/hisi_3630_modem.dtsi\/hisi_3630_modem_${product}.dtsi\/g\" ${auto_generate}/${new_file}.dtsi");
			}
		}
		closedir(SUB_DIR);

		if($found == 0)
		{
			die "config.dts not found in $product!!";
		}
    }


    closedir(CUR_DIR);
}

&my_main()


