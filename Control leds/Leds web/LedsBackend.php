<?php
header('Location: /misphp/led.html');
print "<pre>";
print_r($_REQUEST);

print "</pre>\n";

$status1 = $_REQUEST['1'];
if ($status1 == 1)
{
    $status1 = 1;
}

else
{
    $status1 = 0;
}

$status2 = $_REQUEST['2'];
if ($status2 == 1)
{
    $status2 = 1;
}

else
{
    $status2 = 0;
}

$status3 = $_REQUEST['3'];
if ($status3 == 1)
{
    $status3 = 1;
}

else
{
    $status3 = 0;
}

$status4 = $_REQUEST['4'];
if ($status4 == 1)
{
    $status4 = 1;
}

else
{
    $status4 = 0;
}

$Fichero = fopen("Status.info","w");

$arrayLeds = array ($status1, $status2,$status3, $status4);

$texto = <<<_END
$arrayLeds[0]$arrayLeds[1]$arrayLeds[2]$arrayLeds[3]
_END;

fputs ($Fichero, $texto);
fclose ($Fichero);

?>
