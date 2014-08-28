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
$rdns->addRequest('gimper.net', RDNS_SOA);
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
    [1] => expire
    [2] => host
    [3] => minimum-ttl
    [4] => mname
    [5] => refresh
    [6] => retry
    [7] => rname
    [8] => serial
    [9] => ttl
    [10] => type
)
string(10) "gimper.net"
string(3) "SOA"
string(2) "IN"
