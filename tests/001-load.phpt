--TEST--
Check if module can be loaded
--SKIPIF--
<?php if (!extension_loaded("rdns")) print "skip"; ?>
--FILE--
<?php
echo "rdns extension is available";
?>
--EXPECT--
rdns extension is available
