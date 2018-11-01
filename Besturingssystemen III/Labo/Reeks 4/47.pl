use Win32::OLE 'in';

my $server = ".";
my $namespace = "root/cimv2";
my $privileges = "{(Debug)}!";

my $wbemService = Win32::OLE->GetObject("winmgmts:$privileges//$server/$namespace");
my $name = "notepad.exe";

for (in $wbemService->ExecQuery("Select * from Win32_Process where Name='$name'")){
    $_->Terminate;
}