<?php

$a = range(1, 1E4);

$b = [];
$start = microtime(true);
foreach ($a as $v) {
	// array_unshift($b, $v);
	// array_push($b, $v);
	$b[] = $v;
}
$end = microtime(true);
$take = $end - $start;
echo $take;

array_reverse(array)