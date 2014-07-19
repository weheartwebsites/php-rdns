--TEST--
Check for rdns presence
--SKIPIF--
<?php if (!extension_loaded("rdns")) print "skip"; ?>
--FILE--
<?php
echo "rdns extension is available";
?>
--EXPECT--
rdns extension is available
