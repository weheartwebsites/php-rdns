--TEST--
Check if RDNS class can be instantiated
--SKIPIF--
<?php if (!extension_loaded("rdns")) print "skip"; ?>
--FILE--
<?php
var_dump(new RDNS);
?>
--EXPECT--
object(RDNS)#1 (0) {
}
