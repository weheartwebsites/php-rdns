--TEST--
Check RDNS::addRequest
--SKIPIF--
<?php
if (!extension_loaded("rdns") ||
    !@fsockopen('php.net', 80))
    print "skip";
?>
--FILE--
<?php
$rdns = new RDNS;
$rdns->addServer('8.8.8.8');
$rdns->addRequest('gmail.com', RDNS_MX);
$reply = $rdns->getReplies();
$r0 = $reply[0][0];
ksort($r0);
print_r(array_keys($r0));
var_dump($r0['host']);
var_dump($r0['type']);
var_dump($r0['class']);
?>
--EXPECT--
Array
(
    [0] => class
    [1] => host
    [2] => pri
    [3] => target
    [4] => ttl
    [5] => type
)
string(9) "gmail.com"
string(2) "MX"
string(2) "IN"
