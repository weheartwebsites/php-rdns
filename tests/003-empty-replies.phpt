--TEST--
Check RDNS::getReplies with no requests
--SKIPIF--
<?php if (!extension_loaded("rdns")) print "skip"; ?>
--FILE--
<?php
$rdns = new RDNS;
var_dump($rdns->getReplies());
?>
--EXPECT--
array(0) {
}
