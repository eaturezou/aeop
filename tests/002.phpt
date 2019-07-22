--TEST--
aeop_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('aeop')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = aeop_test1();

var_dump($ret);
?>
--EXPECT--
The extension aeop is loaded and working!
NULL
