#!/usr/bin/perl
####################################################################################
# Description: X3��ܲ�������ű�
# Usage:          
# Creator:     Huangye
# Date:        2010.10.13 
#
# ChangeList:  1. ���Ľӿ��ļ����滻GUID, ��ɽű��Ļ������ܡ�  [Huangye 10/10/19]
#              2. �����˶������ļ�(config.h)��֧�֡�            [Huangye 10/10/21]
#              3. ������Դ�ļ��汾��Ϣ                          [Huangye 10/11/15]
####################################################################################
use strict;
use warnings;

# ���ڿ���Ŀ¼: dircopy
# CPAN  http://search.cpan.org/~dmuey/File-Copy-Recursive-0.38/Recursive.pm
use File::Copy::Recursive qw(fcopy rcopy dircopy fmove rmove dirmove);

# ���ڿ����ļ�
use File::Copy;

# ���ڶ�λĿ¼
use Cwd;

# ��������GUID: Data::GUID->new
# http://search.cpan.org/~rjbs/Data-GUID-0.045/lib/Data/GUID.pm
use Data::GUID;


######################################################
# ���������ļ�(makePlugin.xml)
# http://search.cpan.org/~wadg/Config-IniFiles-2.38/IniFiles.pm
use Config::IniFiles;


my $cfg = new Config::IniFiles( -file => "config.ini",  
                                -allowcontinue => 1,        
                                -reloadwarn => 1,           
                                -nocase  => 1,);           

my $tmpPrjName = $cfg->val('exampleplugin','project'); 
my $tmpPluginName = $cfg->val('exampleplugin','name');

my $prjName = $cfg->val('newplugin','project');
my $pluginName = $cfg->val('newplugin','name'); 

my $FileDescription = $cfg->val('newplugin','FileDescription');
my $InternalName = $cfg->val('newplugin','InternalName');
my $OriginalFilename = $cfg->val('newplugin','OriginalFilename');
my $ProductName = $cfg->val('newplugin','ProductName');

chomp($prjName);
chomp($pluginName);
chomp($FileDescription);
chomp($InternalName);
chomp($OriginalFilename);
chomp($ProductName);

# Step1: �������Ŀ¼
######################################################
my $orig = $cfg->val('exampleplugin','plugindir');
my $interfaceDir = $cfg->val('exampleplugin','interfacedir');
chomp($orig);

dircopy($orig,$pluginName) or die "����Ŀ¼��$orig��$pluginNameʧ��";

# Step2: �����ļ������ļ�����
######################################################
my $curdir = getcwd;
chdir($pluginName); # ��λ�����Ŀ¼
# ����Module
foreach my $file (glob "*")  { # ���ҵ�ǰĿ¼�������ļ�
    print "$file\n";

    # ��ȡ��չ�� 
    my $extName = ($file =~ m/([^.]+)$/)[0];

    # ����Դ�����빤���ļ�
    if ($extName =~ /vcproj|dsp|c|cxx|cpp|h|hpp|rc/i) { 
        open(FILE, $file)
            or warn "���ļ�$fileʧ��!\n";

        my @lines = <FILE>;
        close FILE;

        open(OUT, "> $file")
            or warn "���ļ�$fileʧ��!\n";

        foreach my $line (@lines) {
            # �滻������빤����
            $line =~ s/$tmpPrjName/$prjName/g;
            $line =~ s/$tmpPluginName/$pluginName/g;
            print OUT $line; # д�ص�ԭ�ļ�
        }


        close OUT;
    }

    my $newFile = $file;
    if ($file =~ /$tmpPrjName/g) # �滻������
    {
        $newFile =~ s/$tmpPrjName/$prjName/g; 
        rename $file, $newFile 
    }
    else {
        if ($file =~ /$tmpPluginName/g) # �滻�����
        {
            $newFile =~ s/$tmpPluginName/$pluginName/g; 
            rename $file, $newFile 
        }
    }

}
######################################################


# STEP3 ����Interface
######################################################
my $data = Data::GUID->new;
my $guid = $data->as_string;

# �ȶ�λ��ԭʼĿ¼
chdir($curdir);

# �ٶ�λ���ӿ�Ŀ¼
chdir($interfaceDir)
    or die "��λĿ¼$interfaceDir����!"; # ��λ�����Ŀ¼

my $IDFile= "ClsID_".$tmpPluginName.".h";
my $newIDFile= "ClsID_".$pluginName.".h";

my $IxFile= "Ix_".$tmpPluginName.".h";
my $newIxFile= "Ix_".$pluginName.".h";

copy $IDFile, $newIDFile
    or warn "��$IDFile������$newIDFile����\n";

copy $IxFile, $newIxFile
    or warn "��$IxFile������$newIxFile����\n";

# �滻�ӿ��ļ�����(����GUID)
my @files = ($newIDFile, $newIxFile);
foreach my $file  (@files)  { # ���ҵ�ǰĿ¼�������ļ�
    print "$file\n";

    open(FILE, $file)
        or warn "���ļ�$fileʧ��!\n";
    my @lines = <FILE>;
    close FILE;

    open(OUT, "> $file")
        or warn "���ļ�$fileʧ��!\n";

    foreach my $line (@lines) {
        # �滻�����
        $line =~ s/$tmpPluginName/$pluginName/g;

        # �滻GUID
        $line =~ s/(CLSID_.*\(\")(.*)(\"\);)/$1$guid$3/g;
        print OUT $line; # д�ص�ԭ�ļ�
    }
    close OUT;
}

# STEP4 �滻�汾��Ϣ
######################################################

# �ȶ�λ��ԭʼĿ¼
chdir($curdir."\/".$pluginName);

my $rcfile = $pluginName . ".rc";

open(FILE, $rcfile)
    or die "���ļ�$rcfileʧ��!\n";

# ��ȡģ���ļ�  
my $content = do { local $/; <FILE>; };
close FILE;

$content =~ s/(VALUE\s*\"FileDescription\",\s*)\".*?\"/$1\"$FileDescription\"/g;
$content =~ s/(VALUE\s*\"InternalName\",\s*)\".*?\"/$1\"$InternalName\"/g;
$content =~ s/(VALUE\s*\"OriginalFilename\",\s*)\".*?\"/$1\"$OriginalFilename\"/g;
$content =~ s/(VALUE\s*\"ProductName\",\s*)\".*?\"/$1 \"$ProductName\"/g;


open(OUT, "> $rcfile")
    or die "���ļ�$rcfileʧ��!\n";
print OUT $content; # д�ص�ԭ�ļ�
close OUT;


 
