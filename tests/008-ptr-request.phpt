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
$rdns->addRequest('34.18.76.144.in-addr.arpa', RDNS_PTR);
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
    [2] => target
    [3] => ttl
    [4] => type
)
string(25) "34.18.76.144.in-addr.arpa"
string(3) "PTR"
string(2) "IN"
