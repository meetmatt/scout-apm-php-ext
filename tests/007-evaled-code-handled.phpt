--TEST--
Running evaled code does not crash
--SKIPIF--
<?php if (!extension_loaded("scoutapm")) die("skip scoutapm extension required."); ?>
--FILE--
<?php
eval('echo "Evaled code called.\n";');
echo "End.\n";
?>
--EXPECTF--
Evaled code called.
End.
