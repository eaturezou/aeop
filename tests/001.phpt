--TEST--
Check if aeop is loaded
--SKIPIF--
<?php
if (!extension_loaded('aeop')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "aeop" is available';
?>
--EXPECT--
The extension "aeop" is available
