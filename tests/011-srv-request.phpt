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
$rdns->addRequest('_xmpp-client._tcp.jabberafrica.org', RDNS_SRV);
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
    [2] => port
    [3] => pri
    [4] => target
    [5] => ttl
    [6] => type
    [7] => weight
)
string(34) "_xmpp-client._tcp.jabberafrica.org"
string(3) "SRV"
string(2) "IN"
