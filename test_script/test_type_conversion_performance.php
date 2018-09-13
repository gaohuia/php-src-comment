<?php

$start = microtime(true);
$a = '1.aaaa';
$c = 0;
$a = (float)$a;
// var_dump($a);exit;
for ($i = 0; $i < 1E7; $i ++) {
	$c = $a + $i;
}

echo microtime(true) - $start;


