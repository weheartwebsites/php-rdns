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
# Check that keys are sorted.
# XXX: hack to workaround the bug with ksort.
$reply = $rdns->getReplies();
ksort($reply);
var_dump(array_keys($reply));

$rdns->addRequest('google.com', RDNS_TXT);
$rdns->addRequest('gmail.com', RDNS_MX);
var_dump(count($rdns->getReplies()));
?>
--EXPECT--
array(3) {
  [0]=>
  int(0)
  [1]=>
  int(1)
  [2]=>
  int(2)
}
int(2)
