--TEST--
Calls to curl_exec are logged
--SKIPIF--
<?php if (!extension_loaded("scoutapm")) die("skip scoutapm extension required."); ?>
<?php if (!extension_loaded("curl")) die("skip curl extension required."); ?>
<?php if (!in_array("curl_exec", scoutapm_list_instrumented_functions())) die("skip scout was not compiled with curl");
--FILE--
<?php
$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, "file://" . __FILE__);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_exec($ch);

$call = scoutapm_get_calls()[0];

var_dump($call['function']);
var_dump($call['entered']);
var_dump($call['exited']);
var_dump($call['time_taken']);
var_dump($call['exited'] > $call['entered']);
var_dump($call['argv']);
?>
--EXPECTF--
string(9) "curl_exec"
float(%f)
float(%f)
float(%f)
bool(true)
array(1) {
  [0]=>
  string(%d) "file://%s/tests/009-curl_exec.php"
}
