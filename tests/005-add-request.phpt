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

$rdns->addRequest('_xmpp-client._tcp.jabberafrica.org', RDNS_SRV, 1.2);
$rdns->addRequest('php.net', RDNS_A);
$rdns->addRequest('google.com', RDNS_TXT);
var_dump(count($rdns->getReplies()));

$rdns->addRequest('google.com', RDNS_TXT);
var_dump(count($rdns->getReplies()));
?>
--EXPECT--
int(3)
int(1)
