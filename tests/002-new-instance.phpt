--TEST--
Check if RDNS class can be instantiated
--SKIPIF--
<?php if (!extension_loaded("rdns")) print "skip"; ?>
--FILE--
<?php
$rdns = new RDNS;
var_dump($rdns);
?>
--EXPECT--
object(RDNS)#1 (0) {
}
