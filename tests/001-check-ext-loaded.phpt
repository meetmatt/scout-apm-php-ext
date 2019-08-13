--TEST--
Check Scout APM extension is loaded
--FILE--
<?php
ob_start();
phpinfo(INFO_GENERAL);
$phpinfo = ob_get_clean();

foreach (explode("\n", $phpinfo) as $line) {
  if (stripos($line, '    with scoutapm') === 0) {
    var_dump($line);
  }
}

var_dump(extension_loaded('scoutapm'));
?>
--EXPECT--
string(52) "    with scoutapm v0.0, Copyright 2019, by Scout APM"
bool(true)
