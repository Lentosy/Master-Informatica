 use Win32::OLE;
 my $shell=Win32::OLE->new("WScript.Shell");
 $shell->LogEvent(2,"Schrijf message in logboek");